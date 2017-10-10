package com.pedrohlc.wirelessout;

public interface Client {
	public boolean doConnections();
	public boolean send(byte[] data);
	//public boolean getch(byte[] buffer);
}
