package com.pedrohlc.cardsgames.truco;

import java.io.Console;
import java.io.IOException;

import com.pedrohlc.cardsgames.Card;

public class TrucoConsolePlayerListener implements TrucoPlayerListener {
	private TrucoPlayerInterpreter interp;
	private String head;
	private Console console;

	@Override
	public void setInterpreter(TrucoPlayerInterpreter interpreter) {
		this.interp = interpreter;
		this.head = interp.getID() + " > ";
		this.console = System.console();
	}
	
	public String consoleReadLine(String message){
		if(this.console != null)
			return this.console.readLine(message);
		System.out.print(message);
		String buffer = new String();
		Integer b=0;
		try {
			while((b = System.in.read()) >= 0){
				char c = (char)(b.byteValue());
				if(c == '\n')
					break;
				buffer += c;
			}
		} catch (IOException e) {
			return null;
		}
		return buffer;
	}

	@Override
	public int requestedDeckCut(long cardsnum) {
		System.out.println(head + "Seu turno de cortar o baralho!");
		while(true){
			String response = consoleReadLine(head + "Cortar o baralho na carta (1 à "+cardsnum+"): ");
			int responsei = Integer.parseInt(response);
			if(responsei > 0 && responsei <= cardsnum)
				return responsei-1;
			else
				System.out.println(head + "Resposta inválida! Responda novamente.");
		}
	}

	@Override
	public boolean answerTruco(TrucoPlayerInterpreter asker) {
		System.out.println(head + asker.getID() + " pediu truco a você!");
		while(true){
			String response = consoleReadLine(head + "Resposta (1=Aceitar; 2=Fugir): ");
			int responsei = Integer.parseInt(response);
			if(responsei == 1 || responsei == 2)
				return (responsei == 1);
			else
				System.out.println(head + "Resposta inválida! Responda novamente.");
		}
	}

	@Override
	public void recivedHand(Card[] yourcards) {
		System.out.println(head + "Você recebeu as cartas:"+this.getCardsNames(yourcards)+".");
	}
	
	private String getCardsNames(Card[] cards){
		String result = "";
		for(Card c : cards)
			result += (" " + c.getCardName());
		return result;
	}

	@Override
	public TrucoAction requestAction() {
		System.out.println(head + "Seu turno!");
		Object[] args = null;
		TrucoActionType atp = null;
		while(atp == null){
			String response = consoleReadLine(head + "O que pretende fazer? (1=Jogar carta; 2=Descartar carta; 3=Trucar; 4=Fugir): ");
			int responsei = Integer.parseInt(response);
			switch(responsei){
			case 1:
				Card handCards[] = interp.getHandCardsDump(); 
				System.out.println(head + "Suas cartas:" + this.getCardsNames(handCards) + ".");
				while(true){
					String response2 = consoleReadLine("Qual delas você deseja jogar? (Use os respectivos números; 0=Voltar): ");
					int response2i = Integer.parseInt(response2);
					if(response2i == 0)
						break;
					else if(response2i >= 1 && response2i <= handCards.length){
						atp = TrucoActionType.UseCard;
						args = new Object[]{(response2i-1)};
						break;
					}else
						System.out.println(head + "Resposta inválida! Responda novamente.");
				}
			break; case 2:
				Card handCards2[] = interp.getHandCardsDump(); 
				System.out.println(head + "Suas cartas:" + this.getCardsNames(handCards2) + ".");
				while(true){
					String response2 = consoleReadLine("Qual delas você deseja descartar? (Use os respectivos números; 0=Voltar): ");
					int response2i = Integer.parseInt(response2);
					if(response2i == 0)
						break;
					else if(response2i > 1 && response2i <= handCards2.length){
						atp = TrucoActionType.DiscardCard;
						args = new Object[]{(response2i-1)};
						break;
					}else
						System.out.println(head + "Resposta inválida! Responda novamente.");
				}
			break; case 3:
				atp = TrucoActionType.RequestTruco;
			break; case 4:
				atp = TrucoActionType.Run;
			break; default:
				System.out.println(head + "Resposta inválida! Responda novamente.");
			}
		}
		return new TrucoAction(atp, args);
	}

	@Override
	public void setCopa(Card copa) {
		System.out.println(head + "O número do copa é " + copa.getNumberName() + ".");
	}

	@Override
	public void onGameStarts(TrucoPlayerInterpreter[] players) {
		System.out.print(head + "O jogo começou! Jogadores:");
		int pim = players.length - 1;
		//System.out.print(" "+players[0].getID());
		for(int pi=0; pi<pim; pi++){
			TrucoPlayerInterpreter p = players[pi];
			System.out.print(" "+p.getID()+",");
		}
			System.out.print(" "+players[pim].getID());
		System.out.println(".");
	}

	@Override
	public void onRoundEnd(TrucoPlayerInterpreter[] winners) {
		System.out.print(head + "Fim de round, vencedores:");
		for(TrucoPlayerInterpreter p : winners)
			System.out.println(" "+p.getID());
	}

	@Override
	public void onStepEnd(TrucoPlayerInterpreter winnerplayer, Card winnercard,
			int winnerpoints) {
		System.out.println(head + "A carta vencedora foi " + winnercard.getCardName() + " do(a) " + winnerplayer.getID());
	}

	@Override
	public void onGameEnd(TrucoPlayerInterpreter[] players, int teamApoints,
			int teamBpoints) {
		System.out.print(head+players[0].getID());
		if(players.length <= 1)
			System.out.print(" ganhou o jogo por ");
		else{
			for(int i=1; i<players.length; i++)
				System.out.print(" & "+players[i].getID());
			System.out.print(" ganharam o jogo por ");
		}
		if(teamApoints > teamBpoints)
			System.out.println(teamApoints + " à " + teamBpoints + ".");
		else
			System.out.println(teamBpoints + " à " + teamApoints + ".");

	}

	@Override
	public void playerRequestedTruco(TrucoPlayerInterpreter asker,
			TrucoPlayerInterpreter answer) {
		System.out.println(head + asker.getID() + " pediu truco.");

	}

	@Override
	public void playerAnsweredTruco(TrucoPlayerInterpreter answerer,
			boolean answer) {
		if(answer)
			System.out.println(head + answerer.getID() + " aceitou o truco.");
		else
			System.out.println(head + answerer.getID() + " fugiu do truco.");
	}

	@Override
	public void playerUsedCard(TrucoPlayerInterpreter player, Card card) {
		System.out.println(head + player.getID() + " jogou um "+card.getCardName()+".");
	}

	@Override
	public void playerDiscartedCard(TrucoPlayerInterpreter player) {
		System.out.println(head + player.getID() + " descartou uma carta.");
	}

	@Override
	public void playerCutedDeck(TrucoPlayerInterpreter player) {
		System.out.println(head + player.getID() + " cortou o baralho.");
	}

	@Override
	public void playerRan(TrucoPlayerInterpreter player) {
		System.out.println(head + player.getID() + " fugiu do round.");
	}

}
