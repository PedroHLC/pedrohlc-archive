package com.pedrohlc.wirelessout;

public interface Server{
	public void kill();
	public void sendMessageToAll(byte[] data);
	public void start();

}