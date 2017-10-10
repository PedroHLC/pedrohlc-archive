package com.pedrohlc.wirelessout;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.SourceDataLine;

public class LocalOutput {
	private AudioFormat format;
	private DataLine.Info info;
	private SourceDataLine line;
	
	public LocalOutput() throws LineUnavailableException{
		format =  new AudioFormat(Global.sampleRate, Global.sampleBitsNum, Global.channelsNum, true, LocalInput.bigEndian);
		info = new DataLine.Info(
				SourceDataLine.class, format);
		line = (SourceDataLine)
				AudioSystem.getLine(info);
		line.open(format);
		line.start();
		
	}
	
	public void write(byte[] data){
		line.write(data, 0, data.length);
	}
}
