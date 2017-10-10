package com.pedrohlc.android.wirelessout;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;

public class TCPStream implements IStream {

	private int bufferSize;
	private Socket sock;
	private DataInputStream in;
	private String host = null;
	private int port;

	@Override
	public boolean setServerAddr(String host, int port, int bufferSize) {
		if(port > 0 && host.length() > 0){
			this.bufferSize = bufferSize;
			this.host = host;
			this.port = port;
			return true;
		}else
			return false;
	}
	
	@Override
	public void disconnect() {
		try {
			sock.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public boolean connect() {
		try {
			sock = new Socket(this.host, this.port);
			sock.setTcpNoDelay(true);
			in = new DataInputStream(this.sock.getInputStream());
			return true;
		} catch (Exception e) {
			Service.lastError = e.getMessage();
			e.printStackTrace();
			return false;
		}
	}

	@Override
	public byte[] listen() {
		byte[] buffer = new byte[bufferSize];
		try {
			in.read(buffer, 0, bufferSize);
			return buffer;
		} catch (IOException e) {
			disconnect();
			return null;
		}
	}

	@Override
	public boolean isWorking() {
		return (sock.isConnected());
	}

	@Override
	public boolean prepare() {
		return true;
	}

	@Override
	public String name() {
		return "TCP:RAWAUDIO";
	}

}
