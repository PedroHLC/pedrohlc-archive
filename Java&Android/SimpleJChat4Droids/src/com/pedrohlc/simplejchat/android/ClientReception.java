package com.pedrohlc.simplejchat.android;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientReception implements Runnable {
	
	protected Thread t;
	private Socket sock;
	private PrintWriter out;
	private BufferedReader in;
	private String ip;
	
	public ClientReception(String ip){
		if(ip == null){
			this.ip = Main.ip;
			try{
				this.sock = new Socket(this.ip, Main.port);
				this.out = new PrintWriter(this.sock.getOutputStream(), true);
				this.in = 
					new BufferedReader(new InputStreamReader(this.sock.getInputStream()));
			}catch(Exception e){
				e.printStackTrace();
				Client.i.finish();
			}start();
		}else{
			this.ip = ip;
			tryLuckyMode();
		}
			
	}
	
	public void start(){
		if(this.t != null){
			new Exception(this.toString() + " has already started.");
		}
		this.t = new Thread(this);
	    this.t.start();
	}
	
	private void tryLuckyMode(){
		try{
			this.sock = new Socket(this.ip, Main.port);
			this.out = new PrintWriter(this.sock.getOutputStream(), true);
			this.in = 
					new BufferedReader(new InputStreamReader(this.sock.getInputStream()));
			sendMsg("Te achei no estou com sorte!");
			String msg = null;
			if(((msg = readInputLine()) != null)
					&(msg.contains("Te achei no estou com sorte!"))){
				Main.founded = true;
				System.out.println(msg);
				Client.r = this;
				Main.i.goToActivity(Client.class);
			}
		}catch(Exception e){}
	};
	
	public void destroy(){
		try {
			this.sock.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		/*if(t != null)
			t.stop();*/
	}
	
	private String readInputLine(){
		try{
			return this.in.readLine();
		}catch (IOException e){
			e.printStackTrace();
			Client.i.finish();
			return null;
		}
	}
	
	private void interpretLine(String str){
		if(str.charAt(0) == '/'){
			if (str.startsWith("/boate ")) {
				Client.i.println(str.substring(7) + " começou a boate!");
				Client.i.boate();
			}
		}else{
			Client.i.println(str);
		}
	}
	
	@Override
	public void run() {
		String msg = null;
		while((msg = readInputLine()) != null){
			System.out.println(msg);
			interpretLine(msg);
		}
	}
	
	public void sendMsg(String in){
		if (in.length() <= 0) return;
		else if ((in.charAt(0) == '/') && 
				(in.contentEquals("/clear"))) {
			Client.i.clear();
			return;
		}else{
			System.out.println(in + "\n" + this.sock + "\n" + this.in + "\n" + this.out);
			out.println(in);
		}
	}

}
