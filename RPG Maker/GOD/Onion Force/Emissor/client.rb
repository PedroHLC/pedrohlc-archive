class Client
  attr_accessor("sock")
  attr_accessor("pc_name")
  attr_accessor("pc_ip")
  attr_accessor("id")
  def initialize
    @sock = nil
    @pc_name = ""
    @pc_ip = "0.0.0.0"
    @id = (-1)
    @database = MySQL_Client.new
  end
  
  def send(msg, for_all=false)
    log('send', '', msg)
    @sock.send(msg, for_all.to_i)
  end
  
  def login(login, pass)
    send("<login #{login}>wp</login>")
    send("<login #{login}>[#{@db_user.load('type')},#{@db_user.load('id')}]</login>")
  end
  
  def received(msg)
    case msg
    when /<login (.*)>(.*)<\/login>/
      login($1.to_s, $2.to_s)
    when /ping/
      send("pong")
    end
  end
  
end