//Beep new messages!
//By PedroHLC
function OnEvent_ChatWndReceiveMessage(ChatWnd, Origin, Message, MsgKind){
  if (Origin!=Messenger.MyName){
    Interop.Call("Kernel32","Beep",500,300)
  }
}