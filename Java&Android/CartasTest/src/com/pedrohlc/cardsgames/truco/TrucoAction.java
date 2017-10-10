package com.pedrohlc.cardsgames.truco;

public class TrucoAction {
	private TrucoActionType actionType;
	private Object[] actionArgs;
	// Default Args:
	//RequestTruco = null
	//UseCard= {Integer cardIndexFromHand}
	//DiscardCard = {Integer cardIndexFromHand}
	//Run = null
	
	public TrucoAction(TrucoActionType actionType, Object[] actionArgs){
		this.actionArgs = actionArgs;
		this.actionType = actionType;
	}
	
	public TrucoActionType getType(){
		return actionType;
	}
	
	public Object[] getArgs(){
		return actionArgs;
	}
}
