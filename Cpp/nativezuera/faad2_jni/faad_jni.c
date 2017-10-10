#include "neaacdec.h"
#include "faad_jni.h"

static int aac_probe (char * buf, int len)
{
	int i;
	for (i = 0; i <= len - 4; i ++) {
	if ((buf[i] == 0xff && (buf[i + 1] & 0xf6) == 0xf0) || ! strncmp
			((char *) buf + i, "ADIF", 4))
		return i;
	}

	return len;
}

faacDecHandle aacdec;
unsigned long faac_samplerate;
unsigned char faac_channels;
unsigned char ready;
jint error;

JNIEXPORT jstring JNICALL Java_faad2_EasyDecoder_decode
(JNIEnv *env, jobject obj, jstring input) {
	int input_len = (*env)->GetStringLength(env, input);
	char *input_str = (*env)->GetStringChars(env, input, 0);
	
	if (input_len == 0 || input_str == 0) return 0;
	
	int header_size = aac_probe (input_str, input_len);
	if (header_size==input_len) {
		header_size = 0;
	}
	
	void *now_data=input_str+header_size;
	unsigned long remaining=input_len-header_size;
	faacDecFrameInfo frame_inf;
	char *result_str = 0;
	
	if (ready == 0) {
		long res = NeAACDecInit (aacdec, now_data, remaining, &faac_samplerate, &faac_channels);
		if (res != 0) {
			error = 3;
			return 0;
		} else
			ready = 1;
	}
	
	if (ready == 1) {
		result_str = faacDecDecode (aacdec,
			&frame_inf,
			now_data,
			remaining);
	
		if (frame_inf.error != 0) {
			error = 4;
			ready = 0;
			return 0;
		}
		
		if (frame_inf.samples <= 0) {
			error = 5;
			return 0;
		}
	}
	
	(*env)->ReleaseStringChars(env, input, input_str);
	if (result_str != 0)
		return (*env)->NewString(env, result_str, frame_inf.samples*2);
	else {
		error = 5;
		return 0;
	}
}

JNIEXPORT jboolean JNICALL Java_faad2_EasyDecoder_init
(JNIEnv *env, jobject obj) {
	aacdec = faacDecOpen ();
	
	error = 1;
	if (!aacdec) return JNI_FALSE;
	
	faacDecConfigurationPtr aaccfg = faacDecGetCurrentConfiguration (aacdec);
	aaccfg->outputFormat = FAAD_FMT_16BIT;
	aaccfg->defSampleRate = faac_samplerate = 44100;
	
	error = 2;
	if(!faacDecSetConfiguration (aacdec, aaccfg)) return JNI_FALSE;
	
	faac_channels = 2;
	ready = 0;	
	
	error = 0;
	return JNI_TRUE;
 }
 
JNIEXPORT jint JNICALL Java_faad2_EasyDecoder_getError
(JNIEnv *env, jobject obj) {
	return error;
  }