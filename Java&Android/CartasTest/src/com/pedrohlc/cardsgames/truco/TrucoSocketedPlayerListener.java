package com.pedrohlc.cardsgames.truco;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.pedrohlc.cardsgames.Card;

public class TrucoSocketedPlayerListener implements TrucoPlayerListener {
	private PrintWriter out;
	private BufferedReader in;
	
	public TrucoSocketedPlayerListener(Socket sock) throws IOException{
		this.out = new PrintWriter(sock.getOutputStream(), true);
	    this.in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
	}
	
	@Override
	public void setInterpreter(TrucoPlayerInterpreter interpreter) {
		//this.interp = interpreter;
	}

	@Override
	public int requestedDeckCut(long cardsnum) { //A<(str)bin>
		out.println('A' + Long.toBinaryString(cardsnum));
		try {
			String buffer = null;
			while((buffer = in.readLine()) != null){
				Pattern p = Pattern.compile("a(\\p{Alpha}+)\1");
				return Integer.valueOf(p.matcher(buffer).group(1));
			}
		} catch (IOException e) {}
		return -1;
	}

	@Override
	public boolean answerTruco(TrucoPlayerInterpreter asker) { //B<str>
		out.println('B' + asker.getID());
		try {
			String buffer = null;
			while((buffer = in.readLine()) != null){
				return (buffer.charAt(1)=='1');
			}
		} catch (IOException e) {}
		return false;
	}

	@Override
	public void recivedHand(Card[] yourcards) { //C<char><char><'\1'><char><char><'\1'><char><char>
		out.printf("C%s\1%s\1%s\1\n", yourcards[0].getCardName(), yourcards[1].getCardName(), yourcards[2].getCardName());
	}

	@Override
	public TrucoAction requestAction() {
		out.println('D');
		try {
			String buffer = null;
			while((buffer = in.readLine()) != null){
				Pattern p = Pattern.compile("d(\\p{Alpha}+)\1(\\p{Alpha}+)\1");
				Matcher m = p.matcher(buffer);
				switch(Integer.valueOf(m.group(1))){
				case 0:
				break; case 1:
					return new TrucoAction(TrucoActionType.RequestTruco, null);
				case 2:
					return new TrucoAction(TrucoActionType.UseCard, new Object[]{m.group(2)});
				case 3:
					return new TrucoAction(TrucoActionType.DiscardCard, new Object[]{m.group(2)});
				case 4:
					return new TrucoAction(TrucoActionType.Run, null);
				}
				break;
			}
		} catch (IOException e) {}
		return null; 
	}

	@Override
	public void setCopa(Card copa) {
		out.println('E'+copa.getCardName());
	}

	@Override
	public void onGameStarts(TrucoPlayerInterpreter[] players) {
		out.print('F');
		for(TrucoPlayerInterpreter p : players)
		out.print(p.getID()+'\1');
		out.print('\n');
	}

	@Override
	public void onRoundEnd(TrucoPlayerInterpreter[] winners) {
		out.print('G');
		for(TrucoPlayerInterpreter p : winners)
		out.print(p.getID()+'\1');
		out.print('\n');
	}

	@Override
	public void onStepEnd(TrucoPlayerInterpreter winnerplayer, Card winnercard,
			int winnerpoints) {
		out.printf("H%s\1%s\1%s\n", winnerplayer, winnercard.getCardName(), Integer.toBinaryString(winnerpoints));
	}

	@Override
	public void onGameEnd(TrucoPlayerInterpreter[] players, int teamApoints,
			int teamBpoints) {
		out.print('I');
		for(TrucoPlayerInterpreter p : players)
			out.print(p.getID()+'\1');
		out.println(Integer.toBinaryString(teamApoints)+Integer.toBinaryString(teamBpoints));
	}

	@Override
	public void playerRequestedTruco(TrucoPlayerInterpreter asker,
			TrucoPlayerInterpreter answer) {
		out.println('J'+asker.getID()+'\1'+answer.getID());
	}

	@Override
	public void playerAnsweredTruco(TrucoPlayerInterpreter answerer,
			boolean answer) {
		out.println('K'+answerer.getID()+'\1'+(answer ? '1' : '0'));
	}

	@Override
	public void playerUsedCard(TrucoPlayerInterpreter player, Card card) {
		out.println('L'+player.getID()+'\1'+card.getCardName()+'\1');
	}

	@Override
	public void playerDiscartedCard(TrucoPlayerInterpreter player) {
		out.println('M'+player.getID()+'\1');
	}

	@Override
	public void playerCutedDeck(TrucoPlayerInterpreter player) {
		out.println('N'+player.getID()+'\1');
	}

	@Override
	public void playerRan(TrucoPlayerInterpreter player) {
		out.println('O'+player.getID()+'\1');
	}

}
