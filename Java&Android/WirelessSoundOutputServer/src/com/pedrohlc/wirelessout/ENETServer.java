package com.pedrohlc.wirelessout;

import java.net.InetSocketAddress;
import java.util.Vector;

import org.bespin.enet.EnetException;
import org.bespin.enet.Event;
import org.bespin.enet.Host;
import org.bespin.enet.Peer;

import javax.sound.sampled.LineUnavailableException;

public class ENETServer extends Thread implements Server {
	private Host sock;
	private static final int TIMEOUT = 8000; 
	
	public ENETServer(String[] args) throws Exception{
		if(Global.instance != null)
			Global.instance.kill();
		Global.parseArgs(args);
		Global.instance = this;
		Global.clients = new Vector<Client>();
		sock = new Host(new InetSocketAddress("127.0.0.1", Global.port), 32, 1, 0, 0);
	}
	
	private void disconnect() {
		try {
			sock.finalize();
		} catch (Throwable e) {}
	}

	public void kill(){
		this.disconnect();
		Global.finalizeInput();
		try {
			this.finalize();
		} catch (Throwable e) {
			return;
		}
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
		new Thread(new ENETClientLobby()).start();
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
			new ENETServer(args);
			Global.instance.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
		
	private class ENETClientLobby implements Runnable{
		private Peer getNewClient(){
			try{
				Event event = sock.service(TIMEOUT);
				if(event != null)
					if(event.type() == Event.Type.Connect){
						System.out.printf("Some beauty has connected!\n");
						return event.peer();
					}else System.out.printf("An event!\n");
				return null;
			} catch (EnetException e) {
				return null;
			}
		}
		
		@Override
		public void run() {
			Peer cs;
			Client c;
			while((cs = getNewClient()) != null){
				c = new ENETClient(cs);
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