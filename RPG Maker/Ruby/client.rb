#==============================================================================
# Nome: System_Network
# Descrição: Sistema base ( Network )
#------------------------------------------------------------------------------
# Criado por: PedroHLC
# Equipa: RPG - Soft
# Versão: 1.0
#------------------------------------------------------------------------------
# RPG - Soft © Alguns direitos reservados - 2010 / 2011
# Nota:
# Este script esta disponibilizado sobre a seguinte licença
# http://www.arenamaker.com/forum/index.php?topic=182.0
#==============================================================================

$stopme = false

require 'socket'

class System_Network
  def initialize
    @server_name = ""
    @server_port = 0
    @server_host = ""
    @server_sepn = ""
    @pvp_allow = false
    @pvp_maps = [0]
    @account_passoword = ""
    @account_type = ""
    @temp_char_id = 0
    @temp_loading_process = false
    @temp_can_load = false
    @temp_connected = false
    @net_socket = nil
    @net_players = {}
    @net_events = {}
  end
  
  def test_connect
    return "busy" if @temp_connected != false
    if @net_socket != nil
      @net_socket.close
      @net_socket = nil
    end
    begin
      @net_socket = TCPSocket.new(@server_host, @server_port)
    rescue
      @net_socket = nil
      return false
    end
    return true
  end
  
  def connect(a="Test Server", b=5000, c="127.0.0.1", d=0.chr, e=true)
    disconnect
    @server_name = a.to_s
    @server_port = b.to_i
    @server_host = c.to_s
    @server_sepn = d.to_s
    @pvp_allow = e
    @temp_connected = test_connect
    if @temp_connected == false
      disconnect
      print "Erro ao tentar conectar à '#{c}'!"
    end
  end
  
  def disconnect
    if @net_socket != nil
      @net_socket.close if !@net_socket.closed?
      @net_socket = nil
    end
    @temp_connected = false
    @server_name = ""
    @server_port = 0
    @server_host = ""
    @server_sepn = ""
    @net_socket = nil
    @net_players = {}
    @net_events = {}
  end
  
  def login(login, pass, type)
    deslogin
    @account_login = login
    @account_passoword = pass
    @account_type = type
  end
  
  def deslogin
    @account_login = ""
    @account_passoword = ""
    @account_type = ""
  end
  
  def sendmsg(msg)
    return false if @temp_connected == false
    return @net_socket.send(msg + "\n",0)
  end
  
  def gets(*args)
    return @net_socket.gets(*args)
  end
  
  def received(msg)
    puts msg
  end
  
  def update
    return false if @temp_connected == false or @net_socket == nil
    msg = gets(0xff)
    if msg != false and msg != nil
      received(msg)
      $stopme = true
      return true
    else
      onConnLoose
      return false
    end
  end
  
  def onConnLoose
  end
  
end

begin
#Test Area
$net_test = System_Network.new
$net_test.connect("Test Server", 3309, "127.0.0.1", 0.chr, true)
$net_test.sendmsg("ping")
while(!$stopme)
	sleep(1)
	break if !$net_test.update
end
$net_test.disconnect
rescue Exception => error
puts error.to_s
end
gets();