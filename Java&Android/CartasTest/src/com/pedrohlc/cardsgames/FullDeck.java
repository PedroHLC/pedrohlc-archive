package com.pedrohlc.cardsgames;

import java.util.Collections;
import java.util.Vector;

public class FullDeck implements Deck {
	protected long firstCardGID;
	protected Vector<Card> cards;
	//private Vector<Card> drawed_cards;
	
	public FullDeck(long firstCardGID){
		this.firstCardGID = firstCardGID;
		reset();
	}

	public void reset() {
		//drawed_cards = new Vector<Card>();
		cards = new Vector<Card>();
		long cardid = firstCardGID;
		for(Naipe nype : Naipe.values())
			for(Number number : Number.values()){
				cards.add(new Card(cardid, nype, number));
				cardid++;
			}
		cards.add(Card.newJoker(cardid));
		cardid++;
		cards.add(Card.newJoker(cardid));
	}

	public void shuffle() {
		Collections.shuffle(cards);
	}

	@Override
	public Card draw() {
		int id = cards.size() - 1;
		Card card = cards.get(id);
		cards.remove(id);
		//drawed_cards.add(card);
		return card;
	}

	public void cut(int cardindex) {
		int cards_size = cards.size();
		if(cardindex < 0 || cardindex >= cards_size)
			return;
		Vector<Card> bottom = new Vector<Card>(),
					 up = new Vector<Card>();
		for(int i=0; i<cards_size; i++){
			if(i <= cardindex)
				bottom.add(cards.get(i));
			else
				up.add(cards.get(i));
		}
		cards = new Vector<Card>();
		cards.addAll(up);
		cards.addAll(bottom);
	}

	public int getRemainingCardsNum() {
		return cards.size();
	}
}
