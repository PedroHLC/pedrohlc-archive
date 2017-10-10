package com.pedrohlc.cardsgames;

import java.util.Vector;

public class Hand {
	private Vector<Card> cards;
	
	public void drawCards(int quantity, Deck deck){
		cards = new Vector<Card>();
		for(int i=0; i < quantity; i++)
			cards.add(deck.draw());
	}
	
	public void lostCard(int index){
		cards.remove(index);
	}
	
	public Card[] dumpCards(){
		Card[] dumpedcards = new Card[cards.size()];
		cards.copyInto(dumpedcards);
		return dumpedcards;
	}
	
	public Card getCard(int index){
		return cards.get(index);
	}
}
