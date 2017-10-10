package com.pedrohlc.wirelessout;

import java.util.Vector;

import javax.sound.sampled.LineUnavailableException;

public class Global {
	public static Server instance;
	protected static Input input;
	protected static int sampleRate, bufferSize;
	protected static byte sampleBitsNum, channelsNum;
	protected static Vector<Client> clients = null;
	protected static int port;
	
	public static boolean parseArgs(String[] args){
		if(args.length < 4){
			System.out.println("Incorrect number of arguments.");
			return false;
		}
		sampleRate = Integer.valueOf(args[0]);
		sampleBitsNum = Byte.valueOf(args[1]);
		channelsNum = Byte.valueOf(args[2]);
		port = Integer.valueOf(args[3]);
		if(args.length >= 5)
			bufferSize = Integer.valueOf(args[4]);
		if (sampleRate <= 0 || sampleBitsNum <= 0 || channelsNum <= 0){
			System.out.println("One or more arguments are invalid.");
			return false;
		}
		return true;
	}
	
	public static void startInput() throws LineUnavailableException{
		if(input == null)
			input = new LocalInput();
		System.out.println("Starting: " + input.dump());
	}
	
	public static void finalizeInput(){
		if(input != null)
			input.disconnect();
	}

	public static void setInput(LocalInput localInput) {
		input = localInput;		
	}
}
