class Server
  def initialize
    neo_puts(I18n.t(:server_socket_start))
    neo_puts(I18n.t(:config)+":\n  "+I18n.t(:ip)+"=#{$HOST}\n  "+I18n.t(:port)+"=#{$PORT}\n  "+I18n.t(:server_name)+"=#{$SERVERNAME}")
    @server = TCPServer.new($HOST,$PORT)
    neo_puts(I18n.t(:server_socket_end))
    neo_puts(I18n.t(:server_sql_start))
    neo_puts("SQL "+I18n.t(:config)+":\n  "+I18n.t(:ip)+"=#{$SQL_H}\n  "+I18n.t(:server_sql_user)+"=#{$SQL_U}\n  "+I18n.t(:server_sql_psw)+"=#{$SQL_P}\n  "+I18n.t(:server_sql_db)+"=#{$SQL_DB}")
    @sql = Mysql.new($SQL_H,$SQL_U,$SQL_P,$SQL_DB)
    neo_puts(I18n.t(:server_sql_end))
    $clients = {}
    neo_puts(I18n.t(:server_ready))
    loop do
      #if $stop_server  == true
      #  @server = nil
      #  @sql = nil
      #  $clients = {}
      #  neo_puts("\n\nServer off\n\n")
      #  @server_on = false
      #  break
      #end
      Thread.start(@server.accept) do |client|
        begin
          if $clients[client] == nil
            $clients[client] = eval($CLIENTCLASS)
            $clients[client].sock = client
            $clients[client].sql = @sql
          end
          while client.gets
            @MSG =  $_
            handle(@MSG,client)
          end
          $clients[client].remove
          $clients.delete(client)
          if !client.closed?
            client.close
          end
        rescue Exception
          @err =  $!
          neo_puts(@err)
          $clients[client].sock.close if $client[client].sock.closed? == false
          $clients[client].remove if $clients[client].loggedin == 1
          $clients.delete(client) if $clients[client] != nil
          client.close if not client.closed?
          @err = $!
          neo_puts(@err.backtrace.join("\n"))
          neo_puts(I18n.t(:server_error)+"(#{client.peeraddr[3]}): #{@err}\n")
          log_err(@err)
          neo_puts(I18n.t(:server_logged)+"(#{client.peeraddr[3]})")
        end
      end
    end
  end
  
  def handle(msg, client)
    $clients[client].handle($clients, msg)
    return if msg.include?("<5>") or msg.include?("<6>")
    if $DEBUG_MSG
      neo_puts(I18n.t(:server_received)+"(#{client.peeraddr[2]}): #{msg}\n")
    end
    file = File.open($log['messages'], "a+")
    file.write(I18n.t(:server_received)+"(#{client.peeraddr[2]}): #{msg}")
    file.close()
  end
  
  def log_err(msg)
    trace = msg.backtrace.join("\n")
    file = File.open($log['error'], "a+")
    file.write(I18n.t(:error)+"(#{trace},#{Time.now.to_s}): #{msg}\n")
    file.close()
    neo_puts(I18n.t(:error)+"(#{trace},#{Time.now.to_s}): #{msg}\n")
  end
end