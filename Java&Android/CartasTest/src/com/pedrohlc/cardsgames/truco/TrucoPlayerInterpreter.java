package com.pedrohlc.cardsgames.truco;

import com.pedrohlc.cardsgames.Card;
import com.pedrohlc.cardsgames.Hand;

public class TrucoPlayerInterpreter {
	private String iD;
	private Hand hand;
	protected TrucoPlayerListener player;
	
	public Card[] getHandCardsDump(){
		return hand.dumpCards();
	}
	
	public TrucoPlayerInterpreter(TrucoPlayerListener output, String iD){
		this.iD = iD;
		this.hand = new Hand();
		this.player = output;
		this.player.setInterpreter(this);
	}
	
	public String getID(){
		return iD;
	}
	
	public void onGameStarts(Truco truco) {
		TrucoPlayerInterpreter[] players = new TrucoPlayerInterpreter[truco.players.size()];
		truco.players.copyInto(players);
		player.onGameStarts(players);		
	}
	
	public void drawCards(TrucoDeck deck) {
		hand.drawCards(3, deck);
		player.recivedHand(hand.dumpCards());
	}
	
	public void requestCut(TrucoDeck deck, Truco game){
		deck.cut(player.requestedDeckCut(deck.getRemainingCardsNum()));
		game.playerCutedDeck(this);
		
	}
	
	public void play(Truco game){
		TrucoAction act = player.requestAction();
		switch(act.getType()){
		case UseCard:
			int cardi = (Integer)act.getArgs()[0];
			Card card = hand.getCard(cardi);
			hand.lostCard(cardi);
			game.playerUsedCard(this, card);
		break;case RequestTruco:
			game.playerRequestedTruco(this);
		break;case DiscardCard:
			hand.lostCard((Integer)act.getArgs()[0]);
			game.playerDiscartedCard(this);
		break;case Run:
			game.playerRan(this);
		}
	}
	
}
