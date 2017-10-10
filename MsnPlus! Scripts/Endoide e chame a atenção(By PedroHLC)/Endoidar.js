//Title: Endoide e chame a atenção!
//By:    PedroHLC
//Made In Brazil
//Edição e\ou falsificação de scripts sem permissão de seu verdadeiro criador é crime

//Teclas:
//F7 - Inicia
//F8 - Para

function OnEvent_ChatWndSendMessage(ChatWnd, Message){
	if (Message=="/endoidar"){
	     MsgPlus.AddTimer("State=OFF",300);
		return "";
	}
	if (Message=="/non-endoidar"){
	     MsgPlus.CancelTimer("State=OFF");
          MsgPlus.CancelTimer("State=ON");
          Messenger.MyStatus = 3;
		return "";
	}
}
function OnEvent_Timer(sTimerId){
    if(sTimerId == "State=OFF"){
         Messenger.MyStatus = 2;
         MsgPlus.CancelTimer("State=OFF");
         MsgPlus.AddTimer("State=ON",300);
    }
    if(sTimerId == "State=ON"){
         Messenger.MyStatus = 3;
         MsgPlus.CancelTimer("State=ON");
         MsgPlus.AddTimer("State=OFF",300);
    }
}

function OnGetScriptCommands(){
	var commands = "<ScriptCommands>";
	commands += "  <Command>"
	commands += "    <Name>endoidar</Name>"
	commands += "    <Description>Endoide de vez para chamar a atenção!</Description>"
	commands += "    <Name>non-endoidar</Name>"
	commands += "    <Description>Para de endoidar!</Description>"
	commands += "  </Command>"
	commands += "</ScriptCommands>"
	return commands;
}
function OnEvent_ChatWndEditKeyDown(wnd,key,ctrl,shift){
	switch(key)
	{
		case 118:
		{
			MsgPlus.AddTimer("State=OFF",300);
			break;
		}
		case 119:
		{
			MsgPlus.CancelTimer("State=OFF");
               MsgPlus.CancelTimer("State=ON");
               Messenger.MyStatus = 3;
			break;
		}
	}
}