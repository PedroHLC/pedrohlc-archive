package com.pedrohlc.cardsgames.truco;

import java.util.Vector;

import com.pedrohlc.cardsgames.Card;

public class TrucoDebugPlayerListener implements TrucoPlayerListener {
	private TrucoPlayerInterpreter interp;
	private static final String head = "Debug > ";
	private static boolean show = false;

	public void setInterpreter(TrucoPlayerInterpreter interpreter) {
		interp = interpreter;
	}

	public int requestedDeckCut(long cardsnum) {
		//if(show) System.out.println(head+interp.getID() + " has to cut the deck.");
		int cuton = new Double(Math.random() * (cardsnum - 1)).intValue();
		if(show) System.out.println(head+interp.getID() + " cortou o baralho na "+cuton+"ª carta de "+cardsnum+".");
		return cuton;
	}

	public boolean answerTruco(TrucoPlayerInterpreter asker) {
		//if(show) System.out.println(head+interp.getID() + " has to answer "+asker.getID()+" truco.");
		boolean response = new Double(Math.random()).intValue() == 1;
		if(show) System.out.print(head+interp.getID() + " ");
		if(response)
			if(show) System.out.println("aceitou.");
		else
			if(show) System.out.println("fugiu.");
		return response; 
	}

	public void recivedHand(Card[] yourcards) {
		if(show) System.out.print(head+interp.getID() + " recebeu as cartas:");
		for(Card card: yourcards)
			if(show) System.out.print(" "+card.getCardName());
		if(show) System.out.println(".");
	}

	public TrucoAction requestAction() {
		//if(show) System.out.println(head+interp.getID() + " has to play.");
		TrucoActionType types[] = TrucoActionType.values();
		TrucoActionType type = types[new Double(Math.random() * (types.length - 1)).intValue()];
		if(show) System.out.print(head+interp.getID() + " ");
		Vector<Object> args = null;//new Vector<Object>();
		switch(type){
		case RequestTruco:
			if(show) System.out.println(" pediu TRUCO.");
		break;case UseCard:
			int usedCard = aCardFromHand();
			if(show) System.out.println(" jogou a carta "+ getCardFromHand(usedCard).getCardName()+" na mesa.");
			args = new Vector<Object>();
			args.add(usedCard);
		break;case DiscardCard:
			int discartedCard = aCardFromHand();
			if(show) System.out.println(" descartou a carta "+getCardFromHand(discartedCard).getCardName()+" na mesa.");
			args = new Vector<Object>();
			args.add(discartedCard);
		break;default:
			if(show) System.out.println(" desistiu da rodada.");
		}
		if(args == null)
			return new TrucoAction(type, null);
		else
			return new TrucoAction(type, args.toArray());
	}
		
	private int aCardFromHand(){
		return new Double(Math.random() * (interp.getHandCardsDump().length - 1)).intValue();
	}
	
	private Card getCardFromHand(int index){
		return interp.getHandCardsDump()[index];
	}

	public void setCopa(Card copa) {
		if(show) System.out.println(head+"O copa da vez é o "+copa.getNumberName()+".");
	}
	public void onGameStarts(TrucoPlayerInterpreter[] players) {}
	//public void dropPlayer(TrucoPlayerInterpreter players) {}
	public void onRoundEnd(TrucoPlayerInterpreter[] winners) {}
	public void onStepEnd(TrucoPlayerInterpreter winnerplayer, Card winnercard,
			int winnerpoints) {}
	public void playerRequestedTruco(TrucoPlayerInterpreter asker,
			TrucoPlayerInterpreter answer) {}
	public void playerAnsweredTruco(TrucoPlayerInterpreter answerer,
			boolean answer) {}
	public void playerUsedCard(TrucoPlayerInterpreter player, Card card) {}
	public void playerDiscartedCard(TrucoPlayerInterpreter player) {}
	public void playerCutedDeck(TrucoPlayerInterpreter player) {}
	public void playerRan(TrucoPlayerInterpreter player) {}
	public void onGameEnd(TrucoPlayerInterpreter[] players, int teamApoints,
			int teamBpoints) {
		if(show) System.out.print(head+players[0].getID());
		for(int i=1; i<players.length; i++)
			if(show) System.out.print(" and "+players[i].getID());
		if(show) System.out.print(" ganhou/ganharam o jogo por ");
		if(teamApoints > teamBpoints)
			if(show) System.out.println(teamApoints + " à " + teamBpoints + ".");
		else
			if(show) System.out.println(teamBpoints + " à " + teamApoints + ".");
	}

}
