package com.pedrohlc.android.wirelessout;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketException;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class UDPStream extends Thread implements IStream {
	protected InetAddress hostAddr;
	protected int port, packetBufferSize;
	protected DatagramSocket sock;
	private BlockingQueue<byte[]> queue;
	
	@Override
	public boolean isWorking() {
		return !sock.isClosed();
	}

	@Override
	public boolean setServerAddr(String host, int port, int bufferSize) {
		try{
			if(this.sock != null)
				this.sock.close();
			this.hostAddr = InetAddress.getByName(host);
			this.port = port;
			this.packetBufferSize = bufferSize;
			return true;
		}catch(Exception e){
			Service.lastError = e.getMessage();
			e.printStackTrace();
			return false;
		}
	}

	@Override
	public boolean connect() {
		try {
			if(this.hostAddr.isMulticastAddress()){
				MulticastSocket msock = new MulticastSocket(port);
				msock.joinGroup(this.hostAddr);
				this.sock = msock;
			}else
				this.sock = new DatagramSocket(port);
			sock.setBroadcast(true);
			sock.setReuseAddress(true);
			//sock.setReceiveBufferSize(packetBufferSize);
			
			return true;
		} catch (IOException e) {
			Service.lastError = e.getMessage();
			e.printStackTrace();
			return false;
		}
		
	}

	@Override
	public void disconnect() {
		if(sock != null){
			sock.disconnect();
			sock.close();
		}
	}

	@Override
	public byte[] listen() {
		try{
			return queue.take();
	    } catch (Exception e) {
			e.printStackTrace();
			return null;
		} 
	}

	@Override
	public boolean prepare() {
		queue = new LinkedBlockingQueue<byte[]>(1);
		byte[] firstData = null;
		try {
			receive();
			firstData = listen();
		} catch (Exception e1) {
			e1.printStackTrace();
			return false;
		}
		if(firstData != null){
			this.packetBufferSize += packetBufferSize - firstData.length;
			try {
				sock.setReceiveBufferSize(packetBufferSize);
			} catch (SocketException e) {
				e.printStackTrace();
				return false;
			}
			System.out.println("Using packet buffer size: " + packetBufferSize);
			queue = new LinkedBlockingQueue<byte[]>();
			this.setDaemon(true);
			this.start();
			return true;
		}else
			return false;	
	}
	
	public void receive() throws IOException{
		byte[] packetBuffer = new byte[packetBufferSize];
		DatagramPacket packet = new DatagramPacket(packetBuffer, packetBufferSize);
		sock.receive(packet);
		queue.add(packet.getData());
	}
	
	@Override
	public String name() {
		return "UDP:RAWAUDIO";
	}
	
	public void run(){
		byte[] packetBuffer;
		DatagramPacket packet;
		while(isWorking()){
			try {
				packetBuffer = new byte[packetBufferSize];
				packet = new DatagramPacket(packetBuffer, packetBufferSize);
				sock.receive(packet);
				queue.add(packet.getData());
			} catch (Exception e) {
				e.printStackTrace();
				break;
			}
		}
	}
}
