package com.pedrohlc.cardsgames.truco;

import java.util.Vector;

import com.pedrohlc.cardsgames.Card;
import com.pedrohlc.cardsgames.FullDeck;
import com.pedrohlc.cardsgames.Number;
import com.pedrohlc.cardsgames.Naipe;

public class TrucoDeck extends FullDeck {
	protected static Number validNumbers[] = {Number.N4, Number.N5, Number.N6, Number.N7, Number.Q, Number.J, Number.K, Number.A, Number.N2, Number.N3};	
	
	public TrucoDeck(long firstCardGID) {
		super(firstCardGID);
	}
	
	public void reset() {
		cards = new Vector<Card>();
		long cardid = firstCardGID;
		for(Naipe nype : Naipe.values())
			for(Number number : validNumbers){
				cards.add(new Card(cardid, nype, number));
				cardid++;
			}
	}
	
	public static Card getZapFrom(Card turner){
		int tnumi = -1, numsnum=validNumbers.length, znumi;
		for(int i=0; i < numsnum; i++)
			if(validNumbers[i] == turner.getNumber()){
				tnumi = i;
				break;
			}
		if(tnumi == (numsnum - 1))
			znumi = 0;
		else
			znumi = tnumi + 1;
		return new Card(-1, Naipe.STICK, validNumbers[znumi]);
	}

}
