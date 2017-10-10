#Servidor
$main_sock = TCPServer.new(Settings::SERVER_HOST, Settings::SERVER_PORT)
SocketEncryption.change_pass(Settings::SERVER_PASS)
puts "Servidor pronto para receber clientes em: #{Settings::SERVER_HOST}:#{Settings::SERVER_PORT}"
$database = MySQL_DB.new(Settings::DB_HOST, Settings::DB_USER, Settings::DB_PASS, Settings::DB_NAME)
puts "Database conectada com sucesso!"
$clients = {}

#Interlocutor
$intersect = Thread.new{
loop do
  Thread.start($main_sock.accept) do |client|
    head = "#{client.peeraddr[2]}(#{client.peeraddr[3]})"
    log('client',head,'Connected succefully!')
    begin
      $clients[client] = Client.new
      $clients[client].sock = client
      $clients[client].pc_name = client.peeraddr[2].to_s
      $clients[client].pc_ip = client.peeraddr[3].to_s
      loop do
        got = client.gets
        if got.nil?
          $clients[client].fail_times += 1
          if $clients[client].fail_times >= 6
            $clients[client].quit
            log('client',head,'Shutdown!')
            break
          end
        elsif got.is_a?(String)
          $clients[client].fail_times = 0
          msg = SocketEncryption.desencrypt(got)
          log('port',head, msg) if msg != '8'
          $clients[client].received(msg)
        else
          $clients[client].fail_times = 0
          log_msg = "Something strange got: (#{got.class.to_s}) #{got.to_s}"
          log('port',head, log_msg)
        end
      end
      $clients[client].sock.close if $clients[client].sock.closed? == false
      $clients.delete(client)
    rescue Exception => error
      log('client',head,error.to_s)
      $clients.delete(client)
    end
  end
end
}

puts "Para desligar o servidor corretamente pressione F11"

#Aplicativo
$KEY_READER = Win32API.new('user32','GetAsyncKeyState','l','i')
loop do
  if $KEY_READER.call(122)== (-32768) and 0X01 == 1
    puts "Finalindo o servidor, por favor espere..."
    $intersect.kill
    for client in $clients.values
      if client != nil
        client.sock.close if !client.sock.closed?
      end
      $clients.delete(client)
    end
    $main_sock.close
    break
  end
end