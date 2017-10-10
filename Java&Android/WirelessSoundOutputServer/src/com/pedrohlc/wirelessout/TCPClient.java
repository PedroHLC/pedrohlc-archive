package com.pedrohlc.wirelessout;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class TCPClient implements Client{
	private Socket sock;
	private DataOutputStream out;
	//private BufferedReader in;
	
	public TCPClient(Socket sock){
		this.sock = sock;
	}
	
	public boolean doConnections(){
		try{
			this.sock.setTcpNoDelay(true);
			this.out = new DataOutputStream(this.sock.getOutputStream());
			/*this.in = 
			new BufferedReader(new InputStreamReader(this.sock.getInputStream()));*/
			return true;
		} catch (IOException e) {
			return false;
		}
	}
	
	public boolean send(byte[] data){
		try {
			out.write(data);
			return true;
		} catch (IOException e) {
			return false;
		}
	}
	
	/*public boolean getch(char[] buffer){
		try {
			in.read(buffer);
			return true;
		} catch (IOException e) {
			return false;
		}
	}*/
}
