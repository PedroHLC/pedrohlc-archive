#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <neaacdec.h>
#include <AL/al.h>
#include <AL/alc.h>
//aplay -f S16_LE -r 44100 -c 2 -t raw

faacDecHandle aacdec;
	
unsigned long faac_samplerate;
unsigned char faac_channels;
unsigned char ready;
ALCdevice *al_dev;
ALCcontext *al_ctx;
ALuint al_source, al_buffer, al_frequency;
#define al_format AL_FORMAT_STEREO16

#define TEST_ERROR(_msg)                \
        error = alGetError();                \
        if (error != AL_NO_ERROR) {        \
                fprintf(stderr, _msg "\n");        \
        }

static int aac_probe (unsigned char * buf, int len)
{
	int i;
    for (i = 0; i <= len - 4; i ++)
    {
        if ((buf[i] == 0xff && (buf[i + 1] & 0xf6) == 0xf0) || ! strncmp
         ((char *) buf + i, "ADIF", 4))
            return i;
    }

    return len;
}


void decode (void *data, size_t len) {
	if (len == 0 || data == 0) return;
	
	int header_size = aac_probe (data, len);
	if (header_size==len) {
		fprintf (stderr, "fail [aac] Header not founded\n");
		header_size = 0;
	}
	
	void *now_data=data+header_size;
	unsigned long remaining=len-header_size;
	faacDecFrameInfo frame_inf;
	void *audio;
	
	if (ready == 0) {
		long res = NeAACDecInit (aacdec, now_data, remaining, &faac_samplerate, &faac_channels);
		if (res != 0) {
			fprintf (stderr, "critical [aac] %d\n", res);
		} else{
			ready = 1;
			fprintf (stderr, "info: %d, %d, %d\n", faac_samplerate, faac_channels, res);
			al_frequency = faac_samplerate;
		}
	}
	
	if (ready == 1) {
		audio = faacDecDecode (aacdec,
			&frame_inf,
			now_data,
			remaining);
	
		if (frame_inf.error != 0 || frame_inf.samples <= 0) {
			fprintf (stderr, "failed %d: %s\n", frame_inf.error, NeAACDecGetErrorMessage (frame_inf.error));
			//if (frame_inf.error  == 6)
				ready = 0;
		} else {
			//2 = 16 BIT / BYTE
			fwrite(audio, 2, frame_inf.samples, stdout);
			/*alBufferData(al_buffer, al_format, audio, frame_inf.samples*2, al_frequency);
			ALint value;
			alGetSourcei(al_source,AL_SOURCE_STATE,&value);
			if (value != AL_PLAYING) alSourcePlay(al_source);
			
			ALenum error = alGetError();
			if (error == AL_INVALID_NAME) fprintf (stderr, "critical [oal] 1\n");
			else if (error == AL_INVALID_ENUM) fprintf (stderr, "critical [oal] 2\n");
			else if (error == AL_INVALID_VALUE) fprintf (stderr, "critical [oal] 3\n");
			else if (error == AL_INVALID_OPERATION) fprintf (stderr, "critical [oal] 4\n");
			else if (error == AL_OUT_OF_MEMORY) fprintf (stderr, "critical [oal] 5\n");
			else if (error != AL_NO_ERROR)  fprintf (stderr, "critical [oal] 0\n");*/
			
			//fprintf (stderr, "worked [aac] %d %d %d %d %d\n", frame_inf.samples*2, frame_inf.samplerate,  frame_inf.channels, frame_inf.object_type, (int)frame_inf.header_type);
		}
	}
}

size_t on_data_recevice (void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	if (memcmp (contents, "ICY", 3) == 0) {
		// TODO - RESULT
	} else if (memcmp (contents, "icy", 3) == 0) {
		// TODO - METADATA
	} else {
		decode (contents, realsize);
	}
	return (realsize);
}

void start_curl () {
	CURL *curl;
	CURLcode res;

	char webaddr[] = "198.100.145.144:9894";
	
	struct curl_slist *headers=NULL;
	
	headers = curl_slist_append (headers, "Icy-MetaData:0"); 

	curl = curl_easy_init();
	
	if (curl) {
		curl_easy_setopt (curl, CURLOPT_URL, webaddr);

		curl_easy_setopt (curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, on_data_recevice);
		curl_easy_setopt (curl, CURLOPT_HEADER, 0);
		curl_easy_setopt (curl, CURLOPT_VERBOSE, 0);
		
		res = curl_easy_perform (curl);

		if (res != CURLE_OK)
			fprintf (stderr,
				"curl_easy_perform failed: %s\n",
				curl_easy_strerror (res));
		
		curl_slist_free_all (headers);

		curl_easy_cleanup (curl);
	}
}

void init () {
	ALenum error;
	
	al_dev = alcOpenDevice(NULL);
	if (!al_dev)  fprintf (stderr, "critical [oal] -1\n");
	al_ctx = alcCreateContext(al_dev, NULL);
	//alcMakeContextCurrent(al_ctx);
	if (!alcMakeContextCurrent(al_ctx))  fprintf (stderr, "critical [oal] -2\n");
	
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, (ALfloat[]){0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f });
	TEST_ERROR("listener settings")
	
	alGenBuffers(1, &al_buffer);
	alGenSources(1, &al_source);
	TEST_ERROR("gen")
	
	alSourcef(al_source, AL_PITCH, 1);
	alSourcef(al_source, AL_GAIN, 1);
	alSourcef (al_source, AL_ROLLOFF_FACTOR,  0.0);
	alSourcei (al_source, AL_SOURCE_RELATIVE, AL_TRUE);
	alSource3f(al_source, AL_POSITION, 0, 0, 0);
	alSource3f(al_source, AL_VELOCITY, 0, 0, 0);
	alSourcei(al_source, AL_LOOPING, AL_FALSE);
	TEST_ERROR("source settings")
	
	alSourcei(al_source, AL_BUFFER, al_buffer);
	TEST_ERROR("end")
	
	aacdec = faacDecOpen ();
	
	faacDecConfigurationPtr aaccfg = faacDecGetCurrentConfiguration (aacdec);
	aaccfg->outputFormat = FAAD_FMT_16BIT;
	al_frequency = faac_samplerate = 44100;
	aaccfg->defSampleRate = al_frequency;
	faacDecSetConfiguration (aacdec, aaccfg);
	
	faac_channels = 2;
	ready = 0;	
}


void close () {
	//faacDecClose (aacdec);
	
	alDeleteSources(1, &al_source);
	alDeleteBuffers(1, &al_buffer);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(al_ctx);
	alcCloseDevice(al_dev);
}

int main (int argc, char* argv[]) {
	init ();
	start_curl ();
	close ();

	return 0;
}