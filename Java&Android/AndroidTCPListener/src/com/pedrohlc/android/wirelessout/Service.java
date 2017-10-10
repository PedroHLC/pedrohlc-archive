package com.pedrohlc.android.wirelessout;
import android.media.AudioFormat;
import android.media.AudioTrack;
import android.media.AudioManager;

public class Service implements Runnable {
	
	private AudioTrack audT = null;
	private IStream stream;
	private Thread t;
	private int bufferSize, minBufferSize;
	public static String lastError;
	
	public boolean start(IStream stream, String host, int port, int bufferSize, int sampleRate, boolean stereo, boolean b16){
		System.out.println("Trying to start stream: "+stream.name()+'('+host+','+port+','+bufferSize+','+sampleRate+','+stereo+','+b16+')');
		if(this.stream != null)
			this.stream.disconnect();
		this.stream = stream;
		if(this.t != null)
			this.t.interrupt();
		this.t = new Thread(this);
		if(this.audT != null)
			this.audT.stop();
		if(port <= 0){
			Service.lastError = "'¬¬ Port can't be choosed automatically.\nPlease, choose one for me *-*!";
			return false;
		}
		if(host.length() <= 0){
			Service.lastError = "'¬¬ Hey what happened to your host? I know sometimes it's useless, and that some person can't understand what to fill there, but please, fill it with something *-*!";
			return false;
		}
		int channelMode = (stereo ? AudioFormat.CHANNEL_OUT_STEREO : AudioFormat.CHANNEL_OUT_MONO);
		int encodingMode = (b16 ? AudioFormat.ENCODING_PCM_16BIT : AudioFormat.ENCODING_PCM_8BIT);
		minBufferSize = AudioTrack.getMinBufferSize(sampleRate, channelMode, encodingMode);
		if(bufferSize < minBufferSize){
			lastError = "[Too small buffer]\nFor your configuration, android is requiring "+minBufferSize+"b at least.\nThis will variate with your configuration.";
			return false;
		}else
			this.bufferSize = bufferSize;
		this.audT = new AudioTrack(AudioManager.STREAM_MUSIC, sampleRate,
				channelMode, encodingMode,
				this.bufferSize, AudioTrack.MODE_STREAM);
		if(!(this.stream.setServerAddr(host, port, this.bufferSize)
				&& this.stream.connect()))
			return false;
		this.t.start();
		return true;
	}
	
	public int getBufferSize(){
		return bufferSize;
	}
	
	public int getMinBufferSize(){
		return minBufferSize;
	}
	
	public void stop(){
		if(this.t != null)
			this.t.interrupt();
		if(this.stream != null)
			this.stream.disconnect();
		if(this.audT != null)
			this.audT.stop();
		this.stream = null;
		this.t = null;
		this.audT = null;
	}
	
	@Override
	public void run() {
		try{
			if(!this.stream.prepare())
				return;
			System.out.println("Finished Starting Service");
			this.audT.play();
			byte[] buffer = null;
			do{
				if((buffer = this.stream.listen()) != null){
					receivedAudioData(buffer);
				}
				else break;
			}while(this.stream.isWorking());// && Manager.getService() == this);
			stop();
		}catch (Exception e){
			e.printStackTrace();
			lastError = e.getMessage();
		}
	}
	
	public void receivedAudioData(byte[] data){
		this.audT.write(data, 0, data.length);
	}

	public String getLastError() {
		return lastError;
	}

	public boolean isWorking() {
		if(this.t != null) if(this.t.isAlive() && stream != null) if(stream.isWorking())
			return true;
		return false;
	}

	public void destroy() {
		this.t.destroy();
	}
}