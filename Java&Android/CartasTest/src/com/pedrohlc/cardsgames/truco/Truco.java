package com.pedrohlc.cardsgames.truco;

import java.util.Collections;
import java.util.Vector;

import com.pedrohlc.cardsgames.Card;
import com.pedrohlc.cardsgames.Number;
import com.pedrohlc.cardsgames.Naipe;

public class Truco {
	protected TrucoDeck deck;
	protected Vector<TrucoPlayerInterpreter> players;
	private boolean gameStarted;
	private int roundpoints, someoneRaned, pointsA, pointsB, stepswonA, stepswonB;
	private Card usedcards[], zap;
	
	public Truco(){
		players = new Vector<TrucoPlayerInterpreter>();
		deck = new TrucoDeck(0);
	}
	
	public boolean canAddPlayer(){
		return players.size() < 4 && !gameStarted ;
	}
	
	public boolean addPlayer(TrucoPlayerInterpreter player){
		if(!canAddPlayer())
			return false;
		players.add((TrucoPlayerInterpreter)player);
		return true;
	}

	public boolean canStart() {
		return players.size() >= 2 && !gameStarted;
	}
	
	public Boolean isStarted() {
		return gameStarted;
	}
	
	public boolean start() {
		if(!canStart())
			return false;
		Collections.shuffle(players);
		for(TrucoPlayerInterpreter player : players)
			player.onGameStarts(this);
		pointsA = 0; pointsB = 0;
		int players_sequence[] = new int[players.size()];
		for(int i=0; i<players.size(); i++)
			players_sequence[i] = i;
		pointsA=0; pointsB=0;
		while(pointsA < 12 && pointsB < 12){
			stepswonA = 0; stepswonB = 0;
			roundpoints = 1;
			someoneRaned = -1;
			deck.reset();
			deck.shuffle();
			players.get(players_sequence[players_sequence.length-1]).requestCut(deck, this);
			for(TrucoPlayerInterpreter player : players)
				player.drawCards(deck);
			Card virou = deck.draw();
			zap = TrucoDeck.getZapFrom(virou);
			for(TrucoPlayerInterpreter player : players)
				player.player.setCopa(zap);
			Number numsbystr[] = getNumbersByStr(TrucoDeck.validNumbers, zap.getNumber());
			for(int stepi=0; stepi<3; stepi++){
				usedcards = new Card[players_sequence.length * 3];
				for(int psi=0; psi<players_sequence.length; psi++){
					TrucoPlayerInterpreter player = players.get(players_sequence[psi]);
					player.play(this);
					if(someoneRaned != -1) break;
				}
				boolean teamAwon = false;
				if(someoneRaned != -1){
					roundpoints = 1;
					//teamAwon = (someoneRaned == 1 || someoneRaned == 3);
					if(someoneRaned == 1 || someoneRaned == 3)
						stepswonA = 4;
					else
						stepswonB = 4;
					break;
				}else{
					int strongestcardplayer= players_sequence[0];
					Card strongestcard = usedcards[0];
					for(int c=1; c<usedcards.length; c++){
						Card card = usedcards[c];
						if(card == null)
							break;
						else if(card.equalsTo(zap)){
							strongestcardplayer = c;
							strongestcard = card;
							break;
						}else if(card.higherThan(strongestcard, Naipe.values(), numsbystr)){
							strongestcardplayer = c;
							strongestcard = card;
						}
					}
					teamAwon = (strongestcardplayer == 0 || strongestcardplayer == 2);
				}
				if(teamAwon)
					stepswonA += 1;
				else
					stepswonB += 1;
			}
			TrucoPlayerInterpreter roundwinners[]; 
			if(stepswonA > stepswonB){
				pointsA += roundpoints;
				if(players.size() > 2)
					roundwinners = new TrucoPlayerInterpreter[]{players.get(0), players.get(2)};
				else
					roundwinners = new TrucoPlayerInterpreter[]{players.get(0)};
			}else{
				pointsB += roundpoints;
				if(players.size() > 2)
					roundwinners = new TrucoPlayerInterpreter[]{players.get(1), players.get(3)};
				else
					roundwinners = new TrucoPlayerInterpreter[]{players.get(1)};
			}
			for(TrucoPlayerInterpreter player : players)
				player.player.onRoundEnd(roundwinners);
			int newplayers_sequence[] = new int[players.size()];
			if(players.size() > 2){
				newplayers_sequence[0] = players_sequence[3];
				newplayers_sequence[2] = players_sequence[1];
				newplayers_sequence[3] = players_sequence[2];
			}else{
				newplayers_sequence[0] = players_sequence[1];
			}//IN COMUM
				newplayers_sequence[1] = players_sequence[0];
			players_sequence = newplayers_sequence; 
		}
		TrucoPlayerInterpreter winners[];
		if(pointsA > pointsB)
			if(players.size() > 2)
				winners = new TrucoPlayerInterpreter[]{players.get(0), players.get(2)};
			else
				winners = new TrucoPlayerInterpreter[]{players.get(0)};
		else
			if(players.size() > 2)
				winners = new TrucoPlayerInterpreter[]{players.get(1), players.get(3)};
			else
				winners = new TrucoPlayerInterpreter[]{players.get(1)};
		for(TrucoPlayerInterpreter player : players)
			player.player.onGameEnd(winners, pointsA, pointsB);
		return true;
	}
	
	private Number[] getNumbersByStr(Number[] original, Number biggestguy){
		Vector<Number> numsbystr = new Vector<Number>();
		for(Number n : original)
			if(n != biggestguy)
				numsbystr.add(n);
		numsbystr.add(biggestguy);
		Number[] result = new Number[numsbystr.size()];
		numsbystr.copyInto(result);
		return result;
	}

	public void playerCutedDeck(TrucoPlayerInterpreter cutter){
		for(TrucoPlayerInterpreter player : players)
			player.player.playerCutedDeck(cutter);
	}
	
	public void playerUsedCard(TrucoPlayerInterpreter user, Card card){
		for(TrucoPlayerInterpreter player : players)
			player.player.playerUsedCard(user, card);
	}
	
	public void playerDiscartedCard(TrucoPlayerInterpreter user){
		for(TrucoPlayerInterpreter player : players)
			player.player.playerDiscartedCard(user);
	}
	
	public void playerRequestedTruco(TrucoPlayerInterpreter asker){
		int askeri = players.indexOf(asker), answereri;
		if(askeri == (players.size() - 1))
			answereri = 0;
		else
			answereri = askeri + 1;
		if(playerRequestedTruco(asker, players.get(answereri)))
			asker.play(this);
	}
	
	private boolean playerRequestedTruco(TrucoPlayerInterpreter asker, TrucoPlayerInterpreter answerer){
		for(TrucoPlayerInterpreter player : players)
			player.player.playerRequestedTruco(asker, answerer);
		boolean response = answerer.player.answerTruco(asker);
		if(response)
			roundpoints += 3;
		else
			playerRan(answerer);
		return response;
	}

	public void playerRan(TrucoPlayerInterpreter cagao) {
		someoneRaned = players.indexOf(cagao);
		for(TrucoPlayerInterpreter player : players)
			player.player.playerRan(cagao);
	}
}
