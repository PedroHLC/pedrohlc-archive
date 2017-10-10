package com.pedrohlc.cardsgames.truco;

import com.pedrohlc.cardsgames.Card;

public interface TrucoPlayerListener {
	public void setInterpreter(TrucoPlayerInterpreter interpreter);
	// Need interaction
	public int requestedDeckCut(long cardsnum);
	public boolean answerTruco(TrucoPlayerInterpreter asker);
	public void recivedHand(Card[] yourcards);
	public TrucoAction requestAction();
	// Just information
	public void setCopa(Card copa);
	public void onGameStarts(TrucoPlayerInterpreter[] players);
	//public void dropPlayer(TrucoPlayerInterpreter players);
	public void onRoundEnd(TrucoPlayerInterpreter[] winners);
	public void onStepEnd(TrucoPlayerInterpreter winnerplayer, Card winnercard, int winnerpoints);
	public void onGameEnd(TrucoPlayerInterpreter[] players, int teamApoints, int teamBpoints);
	public void playerRequestedTruco(TrucoPlayerInterpreter asker, TrucoPlayerInterpreter answer);
	public void playerAnsweredTruco(TrucoPlayerInterpreter answerer, boolean answer);
	public void playerUsedCard(TrucoPlayerInterpreter player, Card card);
	public void playerDiscartedCard(TrucoPlayerInterpreter player);
	public void playerCutedDeck(TrucoPlayerInterpreter player);
	public void playerRan(TrucoPlayerInterpreter player);
}
