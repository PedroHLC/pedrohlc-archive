package com.pedrohlc.android.wirelessout;

public interface IStream {
	public boolean isWorking();
	public boolean setServerAddr(String host, int port, int bufferSize);
	public boolean connect();
	public void disconnect();
	public byte[] listen();
	public boolean prepare();
	public String name();
}
