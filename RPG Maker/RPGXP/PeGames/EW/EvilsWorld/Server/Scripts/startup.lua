--  The main script, do not tamper with if you have no knowledge of Lua
--  Copyright(c) 2006 sUiCiDeMAniC
--  Email:  manic15@gmail.com
--  Last update:  03/11/06

dofile( "./Scripts/functions.lua" )

function StartUp()

end

function OnConnect()
  NP():SendToUser( user.id , "<13>Bem vindo ao servidor "..NP():GetServerName().. ", divirtase "..user.name.."; Seu ip é: "..user.ip.." e seu grupo é: "..user.group.."</13>" ) 
  StartNPCLoop()
end

function OnCMD(data,cmd)
      do process(cmd,data) end
--NP():SendToAll( "<chat>O Jogador "..user.name.." acabou de entrar no server!!</chat>" )
end

function OnDisconnect()
  --NP():SendToAll( "<chat>O jogador "..user.name.." saiu do servidor</chat>" )
end
