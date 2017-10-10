package com.pedrohlc.cardsgames;

public class Card {
	protected long gid;
	protected Number number;
	protected Naipe nype;
	
	public Card(long gid, Naipe nype, Number number){
		this.gid = gid;
		this.nype = nype;
		this.number = number;
	}
	
	public Number getNumber(){
		return number;
	}
	
	public Naipe getNaipe(){
		return nype;
	}
	
	public static Card newJoker(long gid){
		return new Card(gid, null, null);
	}
	
	public boolean higherThan(Card another, Naipe[] nypelist, Number[] numberlist){
		int tnypei=-1, anypei=-1;
		for(int i=0; i<nypelist.length; i++){
			Naipe nype = nypelist[i];
			if(nype == this.nype)
				tnypei = i;
			else if(nype == another.getNaipe())
				anypei = i;
		}
		if(tnypei > anypei)
			return true;
		else if(tnypei < anypei)
			return false;
		int tnumberi=-1, anumberi=-1;
		for(int i=0; i<numberlist.length; i++){
			Number num = numberlist[i];
			if(num == this.number)
				tnumberi = i;
			else if(num == another.getNumber())
				anumberi = i;
		}
		return tnumberi > anumberi;
	}
	
	public boolean equalsTo(Card card){
		return (this.number == card.number && this.nype == card.nype);
	}

	public String getNypeName() {
		//♠♡♢♣♤♥♦♧
		switch(nype){
		case GOLD: return "♢";
		case HEART: return "♡";
		case SWORD: return "♠";
		case STICK: return "♣";
		default: return "KER";
		}
	}
	
	public String getNumberName(){
		switch(number){
		case N2: return "2";
		case N3: return "3";
		case N4: return "4";
		case N5: return "5";
		case N6: return "6";
		case N7: return "7";
		case Q: return "Q";
		case J: return "J";
		case K: return "K";
		case A: return "A";
		default: return "JO";
		}
	}
	
	public String getCardName() {
		return getNumberName() + getNypeName();
	}
}
