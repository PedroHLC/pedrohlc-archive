begin
  require('./socket.so')
  print 'Digite o IP: '
  $socket = TCPSocket.open(gets.strip, 5000)
  print 'Diga seu nome: '
  name = gets.strip
  #$socket.send("çççname<#{name}/>\n", 0)
  loop do
    msg = gets
    case msg
    #when /\/name<(.*)\/>/
      #nname = $1.strip
      #$socket.send("çççnname<#{name}/><#{nname}/>\n", 0)
      #name = nname
    when /\/quit/
      break
    when /\/help/
      puts '\t/name <Seu nome aqui/> #MUDA O NOME'
      puts '\t/quit #SAI CORRETAMENTE DO CHAT'
      puts '\t/cmd <comando/> #EXCUTA UM COMANDO NO RECEPTOR'
      puts '\t/selfcmd <comando/> #EXCUTA UM COMANDO NESSA JANELA'
      puts '\t/buzz #CHAMA A ATENÇÃO'
    when /\/selfcmd<(.*)\/>/
      begin
        puts "Feche o programa para continuar a conversa!"
        system($1.to_s.strip)
        rescue Exception => error
          puts 'o comando falhou!'
      end
    else
      #$socket.send(name + ': ' + msg + "\n", 0)
      $socket.send(msg + "\n", 0)
    end
  end
  $socket.close
rescue Exception => error
  puts error
  gets
end