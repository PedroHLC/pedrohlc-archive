//Title: Flood System 
//By:    PedroHLC 
//Ver:   0.64 BETA
//Made In Brasil
function OnGetScriptCommands(){
	var commands = "<ScriptCommands>";
	commands += "  <Command>"
	commands += "    <Name>flood</Name>"
	commands += "    <Description>Você começa a floodar</Description>"
	commands += "  </Command>"
	commands += "</ScriptCommands>"
	return commands;
}
function OnEvent_ChatWndSendMessage(ChatWnd, Message){
	if(Message.substring(0,6)=="/flood"){
		flood_msg = "";
		flood_msg += Message.substring(7,77);
		if (flood_msg==""){
			MsgPlus.DisplayToast('Flood System', 'Use:\n/flood Mesnsagem');
			return "";
		}
		if (Message.substring(77,1162)!=""){
			MsgPlus.DisplayToast('Flood System', 'A mesnsagem deve conter no maximo 77 caracteres');
			return "";
		}
		Message = "";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		Message += flood_msg + "\n";
		return Message;
	}
}