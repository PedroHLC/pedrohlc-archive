package com.pedrohlc.cardsgames;

public interface Deck {
	public void reset();
	public void shuffle();
	public void cut(int cardindex);
	public Card draw();
	public int getRemainingCardsNum();
}
