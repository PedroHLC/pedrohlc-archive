//Title: SuperPing!
//By:    PedroHLC 
//Ver:   1.0.2
//Made In Brasil

function OnEvent_ChatWndReceiveMessage(ChatWnd, Origin, Message, MsgKind){
	if ((Message == "Ping? [request]") & (Origin != Messenger.MyName)){
	  ChatWnd.SendMessage("\x05\x033Pong! [SPEED OF LIGHT]");
	  return "\x05\x033Ping?";
	}
}