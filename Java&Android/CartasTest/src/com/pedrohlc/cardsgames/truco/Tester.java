package com.pedrohlc.cardsgames.truco;

public class Tester {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("++ com.pedrohlc.cardsgames.TRUCO v0.0.5\n\n");
		TrucoConsolePlayerListener console = new TrucoConsolePlayerListener();
		Truco truco = new Truco();
		truco.addPlayer(new TrucoPlayerInterpreter(new TrucoDebugPlayerListener(), "Homer Simpson"));
		//truco.addPlayer(new TrucoPlayerInterpreter(new TrucoDebugPlayerListener(), "Patrick"));
		//truco.addPlayer(new TrucoPlayerInterpreter(new TrucoDebugPlayerListener(), "Burro"));
		truco.addPlayer(new TrucoPlayerInterpreter(console, "Você"));
		truco.start();
	}

}
