--  The process function to organize protocol
--  Copyright(c) 2006 sUiCiDeMAniC
--  Email:  manic15@gmail.com
--  Last update:  05/11/06

--------------------------------
--      Main Proccessing      --
--------------------------------
function process(cmd,data)


--------------------------------
--            CHAT            --
--------------------------------
  if cmd == "<chat>" then
    do NP():SendToAll(data) end

--------------------------------
--       AUTHENFICATION (0)   --
--------------------------------
  elseif cmd == "<0>" then
    do local sname = NP():GetServerName()
    NP():SendToUser(user.id,"<0 "..user.id..">'e' n="..sname.."</0>") end
  elseif cmd == "<auth>" then
    do local sname = NP():GetServerName()
NP():SendToUser(user.id,"<auth "..user.id..">'e' n="..sname.."</auth>") end

--------------------------------
--         ID Request (1)     --
--------------------------------
  elseif cmd == "<1>" then
    do NP():SendToUser(user.id,"<1>"..user.id.."</1>") end
  elseif cmd == "<getid>" then
    do NP():SendToUser(user.id,"<getid>"..user.id.."</getid>") end

--------------------------------
--        NAME Request (2)    --
--------------------------------
  elseif cmd == "<2>" then
    do NP():SendToUser(user.id,"<2>"..user.name.."</2>") end
  elseif cmd == "<getname>" then
    do NP():SendToUser(user.id,"<getname>"..user.name.."</getname>") end

--------------------------------
--   PROFILE/GROUP Request (3)--
--------------------------------
  elseif cmd == "<3>" then
    if user.profile == nil then
     do NP():SendToUser(user.id,"<3>'standard'</3>") end
    else
     do NP():SendToUser(user.id,"<3>"..user.profile.."</3>") end
    end
  elseif cmd == "<getgroup>" then
    if user.profile == nil then
     do NP():SendToUser(user.id,"<getgroup>'standard'</getgroup>") end
    else
     do NP():SendToUser(user.id,"<getgroup>"..user.profile.."</getgroup>") end
    end

--------------------------------
--        CLOSE USER (4)      --
--------------------------------
  elseif cmd == "<4>" then
    do NP():CloseSocket(user.ip) end
  elseif cmd == "<close>" then
    do NP():CloseSocket(user.ip) end

--------------------------------
--         NETPLAYER (5)      --
--------------------------------
  elseif cmd == "<5>" then
    do 
      local ndata = string.gsub(data,"<5>","")
      NP():SendToAll("<5 "..user.id..">"..ndata)
    end

  elseif cmd == "<netact>" then
    do 
      local nadata = string.gsub(data,"<netact>","")
      NP():SendToAll("<netact "..user.id..">"..nadata)
    end
  elseif cmd == "<netplayer>" then
    do 
      local ndata = string.gsub(data,"<netplayer>","")
      NP():SendToAll("<netplayer "..user.id.." >"..ndata)
    end

--------------------------------
--        MAP PLAYER ID (6)   --
--------------------------------
  elseif cmd == "<6a>" then
    do 
      --data = string.gsub(data, " ", "") 
      mapp_id = string.gsub(data, "<6a>", "") 
      --NP():SendToUser(user.id,"<6a>'Confirmed'</6a>\n")
    end
  elseif cmd == "<mappid>" then
    do 
      mapp_id = string.gsub(data, "<mappid>", "") 
      NP():SendToUser(user.id,"<mappid>'Confirmed'</mappid>\n")
    end


  elseif cmd == "<6b>" then
     do NP():SendToUser(user.id,"<6a>"..mapp_id.."</6a>") end

--------------------------------
--         MAP PLAYER (6)     --
--------------------------------
  elseif cmd == "<6>" then
    do 
      local nndata = string.gsub(data,"<6>","")
      NP():SendToUser(mapp_id,"<6 "..user.id..">"..nndata)
    end
  --elseif cmd == "<6>" then
  --  do NP():SendToUser(mapp_id, data) 
  --    NP():SendToUser(user.id, mapp_id..data.."\n") 
  --  end
   elseif cmd == "<mapplayer>" then
    do NP():SendToUser(mapp_id, data) 
      NP():SendToUser(user.id, mapp_id..data.."\n") 
    end

--------------------------------
--         KICK (7)           --
--------------------------------
  elseif cmd == "<7>" then
    do local kickid = string.gsub(data,"<7>","")
      local kickid = string.gsub(kickid,"</7>","")
      NP():SendToUser(kickid, "<18>kicked</18>\n")
      file = io.open("Moderation Logs\\ModLog - "..user.ip.." - "..user.name..".txt", "a+")
      file:write(kickid..data.."\n")
      file:close()
    end
   elseif cmd == "<kick>" then
    do local kickid = string.gsub(data,"<kick>","")
      local kickid = string.gsub(kickid,"</kick>","")
      NP():SendToUser(kickid, "<admin>kicked</admin>\n")
    end

--------------------------------
--         KICK ALL (8)       --
--------------------------------
  elseif cmd == "<8>" then
    do
      NP():SendToAll(kickid, "<18>kick_all</18>\n")
      file = io.open("Moderation Logs\\ModLog - "..user.ip.." - "..user.name..".txt", "a+")
      file:write(data.."\n")
      file:close()
    end
  elseif cmd == "<kickall>" then
    do
      NP():SendToAll(kickid, "<admin>kick_all</admin>\n")
    end
--------------------------------
--        REMOVE (9)          --
--------------------------------
  elseif cmd == "<9>" then
    do
      NP():SendToAll(data)
      NP():SendToAll("<chat>"..user.name.." saiu do jogo</chat>\n")
    end
  elseif cmd == "<remove>" then
    do
      NP():SendToAll(data)
    end

--------------------------------
--        REMOVE (9a)          --
--------------------------------
  elseif cmd == "<9a>" then
    do
      NP():SendToAll(data)
    end
  elseif cmd == "<remove>" then
    do
      NP():SendToAll(data)
    end

--------------------------------
--        SYSTEM (10)         --
--------------------------------
  elseif cmd == "<10>" then
    do NP():SendToAll(data) end
  elseif cmd == "<system>" then
    do NP():SendToAll(data) end

--------------------------------
--        TRADE ID (12)       --
--------------------------------
  elseif cmd == "<12a>" then
    do 
      data = string.gsub(data, " ", "") 
      trade_id = string.gsub(data, "<12a>", "") 
      NP():SendToUser(user.id,"<12a>'Confirmed'</12a>")
    end
  elseif cmd == "<tradeid>" then
    do 
      trade_id = string.gsub(data, "<tradeid>", "") 
      NP():SendToUser(user.id,"<tradeid>'Confirmed'</tradeid>")
    end
--------------------------------
--         TRADE (12)         --
--------------------------------
  elseif cmd == "<12>" then
    do NP():SendToUser(trade_id, data) end
  elseif cmd == "<trade>" then
    do NP():SendToUser(trade_id, data) end
--------------------------------
--      PRIVATE CHAT ID (13)  --
--------------------------------
  elseif cmd == "<13a>" then
    do 
      data = string.gsub(data, " ", "") 
      pchat_id = string.gsub(data, "<13a>", "") 
      --NP():SendToUser(user.id,"<13a>'Confirmed'</13a>")
    end
  elseif cmd == "<pchatid>" then
    do 
      pchat_id = string.gsub(data, "<pchatid>", "") 
      NP():SendToUser(user.id,"<pchatid>'Confirmed'</pchatid>")
    end
--------------------------------
--      PRIVATE CHAT (13)     --
--------------------------------
  elseif cmd == "<13>" then
    do local pmesg = string.gsub(data,"<13>","")
    NP():SendToUser(pchat_id, "<13 "..user.id..">"..pmesg) end
  elseif cmd == "<pchat>" then
    do NP():SendToUser(pchat_id, data) end

--------------------------------
--      Poke (15)             --
--------------------------------
  elseif cmd == "<15>" then
    do local idpoke = string.gsub(data,"<15>","")
      NP():SendToUser(idpoke,"<15>"..user.id.." poke")
    end

--------------------------------
--       SLAP PLAYER ID (16)  --
--------------------------------
  elseif cmd == "<16a>" then
    do 
      data = string.gsub(data, " ", "") 
      slapp_id = string.gsub(data, "<16a>", "") 
      NP():SendToUser(user.id,"<16a>'Confirmed'</16a>\n")
    end
  elseif cmd == "<slappid>" then
    do 
      slapp_id = string.gsub(data, "<slappid>", "") 
      NP():SendToUser(user.id,"<slappid>'Confirmed'</slappid>\n")
    end
--------------------------------
--       SLAP PLAYER (16)     --
--------------------------------
  elseif cmd == "<16>" then
    do 
      NP():SendToUser(slapp_id,"<18>"..data.."</18>\n")
      file = io.open("Moderation Logs\\ModLog - "..user.ip.." - "..user.name..".txt", "a+")
      file:write(slapp_id..data.."\n")
      file:close()
    end
  elseif cmd == "<slap>" then
    do 
      NP():SendToUser(slapp_id,"<admin>"..data.."</admin>\n")
    end
--------------------------------
--      TEST END (20)         --
--------------------------------
  elseif cmd == "<20>" then
    do NP():CloseSocket(user.id) end
  elseif cmd == "<testend>" then
    do NP():CloseSocket(user.id) end

--------------------------------
--         PvP (PvP)          --
--------------------------------
  elseif cmd == "<attack_id>" then
    do attackid = string.gsub(data,"<attack_id>","") end
  elseif cmd == "<result_id>" then
    do resultid = string.gsub(data,"<result_id>","") end
  elseif cmd == "<attack_effect>" then
    do NP():SendToUser(attackid,data) end
  elseif cmd == "<result_effect>" then
    do NP():SendToUser(resultid,data) end
--------------------------------
--         State (PvP)        --
--------------------------------
  elseif cmd == "<state_id>" then
    do stateid = string.gsub(data,"<state_id>","") end
  elseif cmd == "<state>" then
    do NP():SendToUser(stateid,data) end 
--------------------------------
--         Error (err)        --
--------------------------------
  elseif cmd == "<err>" then
    do local bugline = string.gsub(data,"<err>","")
       local bugline = string.gsub(bugline,"</err>","")
       file = io.open("Error Logs\\ErrorLog - "..user.ip.." - "..user.name..".txt", "a+")
       file:write(bugline.."\n")
       file:close()
    end
   
   elseif cmd == "<showani>" then
    do NP():SendToAll(data) end

--------------------------------
--     Map Chat ID (21)       --
--------------------------------
  elseif cmd == "<21a>" then
    do 
      data = string.gsub(data, " ", "") 
      mchat_id = string.gsub(data, "<21a>", "") 
      NP():SendToUser(user.id,"<21a>'Confirmed'</21a>")
    end
--------------------------------
--      Map Chat (21)         --
--------------------------------
  elseif cmd == "<21>" then
    do 
      NP():SendToUser(mchat_id, data) 
    end
--------------------------------
--    Get PM Message (22a)    --
--------------------------------
    elseif cmd == "<22a>" then
      do 	
        file = io.open("Private Messages\\PM - "..user.name..".txt", "r")
        for line in file:lines() do
         NP():SendToUser(user.id,"<22a>"..line.."</22a>\n")
        end
        NP():SendToUser(user.id,"<22a>Compelete</22a>\n")
        file:close()
      end
--------------------------------
--      Get PM Size (22c)     --
--------------------------------
     elseif cmd == "<22c>" then
      do
       pmcode = string.gsub(data,"<22c>","")
       pmsize = 0
       file = io.open("Private Messages\\PM - "..pm_username..".txt", "r")
       for line in file:lines() do
        for word in string.gfind(line, "%a+") do
         if word == "aaPMaa" then 
           pmsize = pmsize+1
         end
        end
       end
       NP():SendToUser(user.id,"<22c>"..pmsize.."</22c>\n") 
       file:close()
      end
--------------------------------
--     Write PM TO (22b)       --
--------------------------------
  elseif cmd == "<22b>" then
    do 
      data = string.gsub(data, " ", "") 
      pm_username = string.gsub(data, "<22b>", "") 
    end
--------------------------------
--    Write PM MEssage (22d)  --
--------------------------------
     elseif cmd == "<22d>" then
      do
        data = string.gsub(data,"<22d>","")
        data = string.gsub(data,"</22d>","")
        file = io.open("Private Messages\\PM - "..pm_username..".txt", "a+")
        file:write(data.."\n")
        file:close()
      end
--------------------------------
--Delete ALL PM MEssages (22e)--
--------------------------------
     elseif cmd == "<22e>" then
      do
        file = io.open("Private Messages\\PM - "..user.name..".txt", "w+")
        file:close()
      end
--------------------------------
--     Self Switch (23)       --
--------------------------------
  elseif cmd == "<23>" then
    do NP():SendToAll(data) end
--------------------------------
--     Trade Request(24)      --
--------------------------------
  elseif cmd == "<24>" then
    do 
      data = string.gsub(data, " ", "") 
      trade_id = string.gsub(data, "<24>", "") 
    end
--------------------------------
--     Trade Request(24c)     --
--------------------------------
  elseif cmd == "<24c>" then
    do 
      data = string.gsub(data, " ", "") 
      NP():SendToUser(user.id,"<24a>"..data.."</24a>")
      NP():SendToUser(trade_id, data)
    end
--------------------------------
--     Trade Exit(24d)        --
--------------------------------
  elseif cmd == "<24d>" then
    do 
      data = string.gsub(data, " ", "")  
      NP():SendToUser(trade_id, data) 
    end
--------------------------------
--     Trade Man ID(25)      --
--------------------------------
  elseif cmd == "<25>" then
    do 
      data = string.gsub(data, " ", "") 
      tradeid = string.gsub(data, "<25>", "") 
    end
--------------------------------
--     Trade Request(24a)     --
--------------------------------
  elseif cmd == "<25a>" then
    do NP():SendToUser(tradeid, data) end
--------------------------------
--     Trade Request(24b)     --
--------------------------------
  elseif cmd == "<25b>" then
    do NP():SendToUser(tradeid, data) end
--------------------------------
--     Trade Request(24d)     --
--------------------------------
  elseif cmd == "<25d>" then
    do NP():SendToUser(tradeid, data) end
--------------------------------
--     Trade Request(24e)     --
--------------------------------
  elseif cmd == "<25e>" then
    do NP():SendToUser(tradeid, data) end
--------------------------------
--     Trade Request(24f)     --
--------------------------------
  elseif cmd == "<25f>" then
    do NP():SendToUser(tradeid, data) end
--
--------------------------------
--  Data Variables (vr)       --
--------------------------------
  elseif cmd == "<vrL>" then
    do file = io.open("Data\\VR.dat", "r")
      for line in file:lines() do
        NP():SendToAll("<vrS>"..line.."<vrS>\n")
      end
      file:close()
    end
  elseif cmd == "<vrS>" then
    do file = io.open("Data\\VR.dat", "w")
      data = string.gsub(data, " ", "")
      file:write(data)
      file:close()
    end
--------------------------------
--  Data Switches (SW)        --
--------------------------------
  elseif cmd == "<swL>" then
    do file = io.open("Data\\SW.dat", "r")
      for line in file:lines() do
        NP():SendToAll("<swS>"..line.."<swS>\n")
      end
      file:close()
    end
  elseif cmd == "<swS>" then
    do file = io.open("Data\\SW.dat", "w")
      data = string.gsub(data, " ", "")
      file:write(data)
      file:close()
    end
--------------------------------
--  Serial       (ser)        --
--------------------------------
  elseif cmd == "<ser>" then
    do file = io.open("Data\\Serial.dat", "r")
      for line in file:lines() do
        NP():SendToAll("<ser>"..line.."</ser>\n")
      end
      file:close()
    end
--------------------------------
--  Version      (ver)        --
--------------------------------
  elseif cmd == "<ver>" then
    do file = io.open("Data\\Version.dat", "r")
      for line in file:lines() do
        NP():SendToAll("<ver>"..line.."</ver>\n")
      end
      file:close()
    end
  end
end