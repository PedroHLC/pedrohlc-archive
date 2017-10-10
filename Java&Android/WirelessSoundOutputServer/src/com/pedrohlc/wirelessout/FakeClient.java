package com.pedrohlc.wirelessout;

import javax.sound.sampled.LineUnavailableException;

public class FakeClient implements Client{
	private LocalOutput out;
	
	public FakeClient(){
		try {
			out = new LocalOutput();
		} catch (LineUnavailableException e) {
			e.printStackTrace();
		}
	}
	
	public boolean doConnections(){
		return true;
	}
	public boolean send(byte[] data){
		try {
			out.write(data);
			return true;
		} catch (Exception e) {
			return false;
		}
	}
}