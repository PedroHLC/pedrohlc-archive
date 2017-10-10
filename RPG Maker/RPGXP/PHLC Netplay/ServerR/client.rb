class Client
  attr_accessor("sock")
  attr_accessor("pc_name")
  attr_accessor("pc_ip")
  attr_accessor("id")
  attr_accessor("fail_times")
  def initialize
    @sock = nil
    @pc_name = ""
    @pc_ip = "0.0.0.0"
    @id = (-1)
    @database = MySQL_Client.new
    @fail_times = 0
  end
  
  def head
    return "#{@pc_name}(#{@pc_ip})"
  end
  
  def send(msg, for_all=false)
    log('send', head, msg) if msg != '8'
    @sock.send(SocketEncryption.encrypt(msg) + "\n", for_all.to_i)
  end
  
  def login(login, pass)
    result = @database.user_login(login, pass)
    case result
    when 1
      send("<login #{login}>wp,0</login>")
    when 2
    send("<login #{login}>al,0</login>")
    else
      send("<login #{login}>#{@database.user_load('type')},#{@database.user_load('id')}</login>")
    end
  end
  
  def logoff
    return if @database.user_load('id') <= 0
    @database.logoff
  end
  
  def quit
    logoff
  end
  
  def received(msg)
    case msg
    when /<login (.*)>(.*)<\/login>/
      login($1.to_s, $2.to_s)
    when /logoff/
      logoff
    when '8'
      send("8")
    end
  end
  
end