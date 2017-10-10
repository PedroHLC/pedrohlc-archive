package com.pedrohlc.wirelessout;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;

import javax.sound.sampled.LineUnavailableException;

public class TCPServer extends Thread implements Server{
	private ServerSocket sock;
	
	public TCPServer(String[] args) throws Exception{
		if(Global.instance != null)
			Global.instance.kill();
		Global.parseArgs(args);
		Global.instance = this;
		Global.clients = new Vector<Client>();
		sock = new ServerSocket(Global.port);
	}
	
	private void disconnect() {
		try {
			sock.close();
		} catch (IOException e) {}
	}

	public void kill(){
		try {
			this.finalize();
		} catch (Throwable e) {
			return;
		}
		this.disconnect();
		Global.finalizeInput();
	}
	
	@Override
	public void start(){
		try {
			Global.startInput();
		} catch (LineUnavailableException e) {
			e.printStackTrace();
			return;
		}
		super.start();
	}
	
	@Override
	public void run(){
		new Thread(new TCPClientLobby()).start();
		while(Global.instance == this){
			new SendMessageToAll(Global.input.getch());
		}
	}
	
	public void sendMessageToAll(byte[] data){
		for(Client c : Global.clients)
			c.send(data);
	}
	
	public static void main(String[] args){
		try {
			new TCPServer(args);
			Global.instance.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
		
	private class TCPClientLobby implements Runnable{
		private Socket getNewClient(){
			try{
				return sock.accept();
			} catch (IOException e) {
				return null;
			}
		}
		
		@Override
		public void run() {
			Socket cs;
			Client c;
			while((cs = getNewClient()) != null){
				c = new TCPClient(cs);
				if(c.doConnections())
					Global.clients.add(c);
			}
		}
	}
	
	private class SendMessageToAll implements Runnable {
		private byte[] data;
		
		public SendMessageToAll(byte[] data){
			this.data = data;
			new Thread(this).start();
		}
		
		@Override
		public void run() {
			if (data == null)
				return;
			Client c;
			for(int i=0; i < Global.clients.size(); i++){
				c = Global.clients.get(i);
				if(!c.send(data))
					Global.clients.remove(i);
			}
		}
		
	}

}