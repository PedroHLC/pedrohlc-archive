package com.pedrohlc.simplejchat.android;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;

public class ServerReception implements Runnable {
	
	protected Thread t = null;
	private ServerSocket sock = null;
	private Vector<ServerClient> clients = null;
	
	public ServerReception(){
		this.clients = new Vector<ServerClient>();
		try {
			this.sock = new ServerSocket(Main.port);
		} catch (IOException e) {
			e.printStackTrace();
			Server.i.finish();
		}
		this.t = new Thread(this);
		this.t.start();
	}

	@Override
	public void run() {
		int nclienti = 0;
		Socket nclient = null;
		while((nclient = newClient()) != null){
			this.clients.add(nclienti, new ServerClient(nclienti, nclient));
			nclienti++;
		}
	}
	
	private Socket newClient(){
		try{
	    	return this.sock.accept();
	    }catch (IOException e) {
	    	e.printStackTrace();
	    	return null;
	    }
	}
	
	public void sendForAll(String message){
		for (ServerClient client : this.clients)
			client.receiveFromSomeone(message);
	}

	public void destroy() {
		try{
			this.sock.close();
		}catch(Exception e){
			return;
		}
		/*if(t != null)
			t.stop();*/
	}
}
