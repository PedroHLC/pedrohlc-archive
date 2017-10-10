class Server
  def initialize
    neo_puts(I18n.t(:server_socket_start))
    neo_puts(I18n.t(:config)+":\n  "+I18n.t(:ip)+"=#{$HOST}\n  "+I18n.t(:port)+"=#{$PORT}\n  "+I18n.t(:server_name)+"=#{$SERVERNAME}")
    @server = TCPServer.new($HOST,$PORT)
    neo_puts(I18n.t(:server_socket_end))
    neo_puts(I18n.t(:server_sql_start))
    neo_puts("SQL "+I18n.t(:config)+":\n  "+I18n.t(:ip)+"=#{$SQL_H}\n  "+I18n.t(:server_sql_user)+"=#{$SQL_U}\n  "+I18n.t(:server_sql_psw)+"=#{$SQL_P}\n  "+I18n.t(:server_sql_db)+"=#{$SQL_DB}")
    @sql = Mysql.new($SQL_H,$SQL_U,$SQL_P,$SQL_DB)
    
    if FileTest.exist?("ChatFilter.txt")
      $chat_filter = eval(File.open("ChatFilter.txt","r").read.to_s.downcase)
    else
      $chat_filter = []
    end
    
    if FileTest.exist?("EventsList.txt")
      $events = eval(File.open("EventsList.txt","r").read.to_s)
      $events = {} if !$events.is_a?(Hash) and $events.to_s.strip == ""
    else
      $events = {}
    end
    $events.each{ |event|
      if event == nil
        $events.delete(event)
        next
      elsif event.is_a?(Array)
        for i in 0..(event.size-1)
          if event[i].to_s.strip != ""
            event = event[i]
            break
          end
        end
      elsif event.is_a?(String)
        event = (eval(event))
      end
      if !event.is_a?(Event)
        $events.delete(event)
        next
      end
    }
    
    neo_puts(I18n.t(:server_sql_end))
    $clients = {}
    neo_puts(I18n.t(:server_ready))
    
    neo_puts(I18n.t(:server_shutdown_button)+"\n")
    
    @clients_receiver = Thread.new{
      loop do
        Thread.start(@server.accept) do |client|
          begin
            #if $clients[client] != nil
            #  $clients[client].remove if $clients[client].loggedin == 1
            #  $clients[client].sock.close
            #end
            $clients[client] = eval($CLIENTCLASS)
            $clients[client].sock = client
            $clients[client].sql = @sql
            while client.gets
              @MSG =  $_
              handle(@MSG,client)
            end
            $clients[client].remove
            $clients[client].sock.close if $client[client].sock.closed? == false
            $clients.delete(client)
            if !client.closed?
              client.close
            end
          rescue Exception => error
            log_err(error.to_s)
            if $clients[client] != nil
              $clients[client].remove if $clients[client].loggedin == 1
              $clients[client].sock.close if $client[client].sock.closed? == false
              $clients.delete(client)
            end
            neo_puts(I18n.t(:server_error)+"(#{client.peeraddr[3]}): #{@err}\n")
            client.close if not client.closed?
          end
        end
      end
    }
    loop do
      $events.each{ |event|
        next if event == nil
        next if !event.is_a?(Event)
        event.update
      }
      
      if (Win32API.new("user32","GetAsyncKeyState",['i'],'i').call(122) & 0x01 == 1)
        neo_puts(I18n.t(:server_shutdown_start)+"\n")
        for client in $clients.values
          next if client == nil
          client.remove if client.loggedin == 1
          client.sock.close if client.sock.closed? == false
          $clients.delete(client)
        end
        @clients_receiver.exit
        @server.close
        @sql.close
        neo_puts(I18n.t(:server_shutdown_end)+"\n")
        break
      end
    end
    return
  end
  
  def handle(msg, client)
    if $DEBUG_MSG and !msg.include?("<5>") and !msg.include?("<6>")
      neo_puts(I18n.t(:server_received)+"(#{client.peeraddr[2]}): #{msg.strip}\n")
    end
    file = File.open($log['messages'], "a+")
    file.write(I18n.t(:server_received)+"(#{client.peeraddr[2]}): #{msg.strip}\n")
    file.close
    $clients[client].handle($clients, msg)
  end
  
  def log_err(msg)
    trace = msg.backtrace.join("\n")
    file = File.open($log['error'], "a+")
    file.write(I18n.t(:error)+"\n"+msg.to_s+"\n")
    file.close
  end
end