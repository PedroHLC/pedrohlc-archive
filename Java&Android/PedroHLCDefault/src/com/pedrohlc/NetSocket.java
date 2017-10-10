package com.pedrohlc;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

public class NetSocket {
	private Socket sock;
	private DataInputStream in;
	private DataOutputStream out;
	
	public NetSocket(){
		sock = null;
		in = null;
		out = null;
	}
	
	public boolean connect(String addr, int port) throws UnknownHostException, IOException{
		return connect(new Socket(addr, port));
	}
	
	public boolean connect(Socket temp_sock) throws UnknownHostException, IOException{
		if(sock != null) close();
		DataInputStream temp_in = new DataInputStream(sock.getInputStream());
		DataOutputStream temp_out = new DataOutputStream(sock.getOutputStream());
		if(temp_sock != null & temp_in != null & temp_out != null){
			sock = temp_sock;
			in = temp_in;
			out = temp_out;
			return true;
		}else
			return false;
	}
	
	public String gets(){
		try {
			return in.readUTF();
		} catch (Exception e) {}
		return null;
	}
	
	public boolean send(String msg){
		try {
			out.writeUTF(msg + '\0');
			return true;
		} catch (Exception e) {}
		return false;
	}
	
	public void close(){
		try {
			in.close();
			out.close();
			sock.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		in = null;
		out = null;
		sock = null;
	}
}