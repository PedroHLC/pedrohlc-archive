package com.pedrohlc.simplejchat.android;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ServerClient implements Runnable{
	private int id;
	private Socket socket;
	private String name;
	private Thread t;
	private PrintWriter out;
	private BufferedReader in;

	public ServerClient(int id, Socket socket){
		this.id = id;
		this.socket = socket;
		this.name = ("Guest " + String.valueOf(id));
		try{
			this.out = new PrintWriter(this.socket.getOutputStream(), true);
			this.in = 
					new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
		} catch (IOException e) {
			return;
		}
		this.t = new Thread(this);
		this.t.start();
	}

	public int getId(){	return this.id;	}
	public String getName(){	return this.name;	}
	
	public String readInput(){
		try {
			return this.in.readLine();
		} catch (IOException e) {
			return null;
		}
	}

	public void receiveFromSomeone(String message){
		if (this.socket.isConnected())
			this.out.println(message);
	}

	public void run()
	{
		String message;
		while ((message = readInput()) != null){
			if (message.charAt(0) == '/'){
				if (message.startsWith("/name ")){
					this.name = message.substring(6);
					this.out.println("Seu nome agora �: " + this.name);
				}else if (message.compareToIgnoreCase("/about") == 0){
					this.out.println("SimpleJChat foi criado por PedroHLC em 27-02-2012.\n\tVers�o 1.2.2 - Porta 5000.");
				}else if (message.compareToIgnoreCase("/boate") == 0){
					Server.sendForAll(message + " " + this.name);
				}else{
					this.out.println("Comando desconhecido ou argumento inv�lido!");
				}
			}
			else Server.sendForAll(this.name + ": " + message);
		}
	}
}