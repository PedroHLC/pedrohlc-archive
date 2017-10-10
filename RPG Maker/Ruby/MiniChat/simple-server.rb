begin
  require('./Win32API.so')
  require('./socket.so')
  $socket = TCPServer.open(5000)
  loop do
    Thread.start($socket.accept) do |client|
      begin
        puts "*\t#{client.peeraddr[3]} conectou-se!"
        loop do
          got = client.gets
          if got.nil?
            break
            return
          end
          case got
          when /çççname<(.*)\/>/
            puts "*\t#{client.peeraddr[3]} chama-se #{$1}"
          when /(.*): \/cmd<(.*)\/>/
            puts "*\t#{$1} rodou o comando: #{$2}\nFeche o programa para continuar a conversa!"
            begin
              system($2.to_s.strip)
            rescue Exception => error
              puts '*\to comando falhou!'
            end
          when /çççnname<(.*)\/><(.*)\/>/
            puts "*\t#{$1} agora chama-se #{$2}"
          when /(.*): \/beep/
            puts "\a#{$1} bipou-lhe!"
          when /(.*): \/buzz/
            Win32API.new('user32', 'MessageBox', 'ippi', 'i').call(0, 'Alguem está chamando sua atenção?', '...', 0)
          else
            puts got.chop
          end
        end
      rescue Exception => error
        puts "*\t#{client.peeraddr[3]} fez com o servidor falhar!"
      end
      puts "*\t#{client.peeraddr[3]} saiu!"
      client.close
    end
  end
  $socket.close
rescue Exception => error
  puts error
  gets
end