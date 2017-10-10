package com.pedrohlc.wirelessout;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.Mixer;
import javax.sound.sampled.TargetDataLine;

public class LocalInput implements Input {
	private AudioFormat format;
	private DataLine.Info info;
	private TargetDataLine line;
	private int bufferSize;
	protected static final boolean bigEndian = false;
	
	private void continueInit() throws LineUnavailableException{
		line.open(format);
		line.start();
		int recommendedBufferSize = ((int)format.getSampleRate() * format.getFrameSize());
		if(Global.bufferSize <= 0)
			bufferSize = recommendedBufferSize;
		else{
			System.out.println("DEBUG: Recommended Cache Size => " + recommendedBufferSize);
			bufferSize = Global.bufferSize;
		}
		System.out.println("DEBUG: Original Cache Size => " + line.getBufferSize());
	}
	
	public LocalInput() throws LineUnavailableException{
		format =  new AudioFormat(Global.sampleRate, Global.sampleBitsNum, Global.channelsNum, true, bigEndian);
		info = new DataLine.Info(
				TargetDataLine.class, format);
		line = (TargetDataLine)
				AudioSystem.getLine(info);
		continueInit();		
	}
	
	public LocalInput(TargetDataLine line) throws LineUnavailableException{
		format =  new AudioFormat(Global.sampleRate, Global.sampleBitsNum, Global.channelsNum, true, bigEndian);
		this.info = (DataLine.Info) line.getLineInfo();
		this.line = line;
		continueInit();
		
	}
	
	public LocalInput(Mixer mixer) throws LineUnavailableException {
		format =  new AudioFormat(Global.sampleRate, Global.sampleBitsNum, Global.channelsNum, true, bigEndian);
		info = new DataLine.Info(
				TargetDataLine.class, format);
		line = (TargetDataLine)
				mixer.getLine(info);
		continueInit();		
	}

	public byte[] getch(){
		byte buffer[] = new byte[bufferSize];
		if(line.read(buffer, 0, bufferSize) != bufferSize)
			return null;
		return buffer;
	}

	@Override
	public void disconnect() {
		line.stop();
		line.close();
	}
	
	public String dump(){
		return line.getFormat().toString();
	}
}
