class Client
 
  attr_accessor     :sock
  attr_accessor     :sql
  attr_accessor     :clients
  attr_accessor     :map_id
  attr_accessor     :name
  attr_accessor     :level
  attr_accessor     :netid
  attr_accessor     :hp
  attr_accessor     :sp
  attr_accessor     :username
  attr_accessor     :event
  attr_accessor     :agi
  attr_accessor     :pdef
  attr_accessor     :eva
  attr_accessor     :mdef
  attr_accessor     :states
  attr_accessor     :damage
  attr_accessor     :gold
  attr_accessor     :loggedin
  attr_accessor     :maxhp
  attr_accessor     :maxsp
  attr_accessor     :str
  attr_accessor     :dex
  attr_accessor     :int
  attr_accessor     :atk
  attr_accessor     :exp
  attr_accessor     :upp
  attr_accessor     :bank_gold
  attr_reader         :id                       # ID
  attr_reader         :x                        # map x-coordinate (logical)
  attr_reader         :y                        # map y-coordinate (logical)
  attr_reader         :real_x                   # map x-coordinate (real * 128)
  attr_reader         :real_y                   # map y-coordinate (real * 128)
  attr_reader         :tile_id                  # tile ID (invalid if 0)
  attr_reader         :character_name           # character file name
  attr_reader         :character_hue            # character hue
  attr_reader         :opacity                  # opacity level
  attr_reader         :blend_type               # blending method
  attr_reader         :direction                # direction
  attr_reader         :pattern                  # pattern
  attr_reader         :move_route_forcing       # forced move route flag
  attr_reader         :through                  # through
  attr_accessor      :animation_id             # animation ID
  attr_accessor      :transparent              # transparent flag
  attr_accessor      :class_id         #class ID
  attr_accessor      :raca_id          #raça ID
  
  def initialize
    @sock = nil
    @sql = nil
    @clients = {}
    @last_msg = ""
    @servername = $SERVERNAME
    @map_id = 0
    @name = ""
    @level = -1
    @netid = -1
    @hp = -1
    @sp = -1
    @username = ""
    @move_tom = true
    @event = self
    @eva = 0
    @agi = 0
    @pdef = 0
    @mdef = 0
    @maxhp = 0
    @maxsp = 0
    @str = 0
    @dex = 0
    @int = 0
    @atk = 0
    @states = []
    @damage = 0
    @gold = 0
    @ver = 1.7
    @group = "Standart"
    @pm = ""
    @class_id = 0
    @raca_id = 0
    @id = 0
    @x = 0
    @y = 0
    @real_x = 0
    @real_y = 0
    @tile_id = 0
    @character_name = ""
    @character_hue = 0
    @opacity = 255
    @blend_type = 0
    @direction = 2
    @pattern = 0
    @move_route_forcing = false
    @through = false
    @animation_id = 0
    @transparent = false
    @original_direction = 2
    @original_pattern = 0
    @move_type = 0
    @move_speed = 4
    @move_frequency = 6
    @move_route = nil
    @move_route_index = 0
    @original_move_route = nil
    @original_move_route_index = 0
    @walk_anime = true
    @step_anime = false
    @direction_fix = false
    @always_on_top = false
    @anime_count = 0
    @stop_count = 0
    @jump_count = 0
    @jump_peak = 0
    @wait_count = 0
    @locked = false
    @prelock_direction = 0
    @loggedin = 0
    @exp = 1
    @upp = 0
    @char_id = 1
    @bank_gold = 0
    @itens = []
    @weapons = []
    @armors = []
  end
  
  def login(name,password)
    @select = @sql.query("SELECT * FROM users WHERE name='#{name}'")
    @hash = @select.fetch_hash
    if @select.num_rows() < 1
      return "not exist"
    end
    if @hash['password'] != password
      return "wrong password"
    end
    if @hash['banned'].to_i == 1
      return "not exist"
    end
    if @hash['loggedin'].to_i == 1
      return "logged in"
    end
    @loggedin = 1
    @netid = @hash['id'].to_i
    @bank_gold = @hash['bank_gold'].to_i
    @group = @hash['net_group'].to_s
    #@sql.query("UPDATE users SET loggedin=1 WHERE name='#{name}'")
    return "ok"
  end
  
  def register(user,pass)
    @check = @sql.query("SELECT loggedin FROM users WHERE name='#{user}'")
    if @check.num_rows() >= 1
      return "exist"
    end
    @sql.query("INSERT INTO users(name,password) VALUES('#{user}','#{pass}')")
    return "done"
  end
  
  def handle(clients_list, msg)
    @clients = clients_list
    @last_msg = msg
    @msg = msg
    case @msg
    when /<0>'e'<\/0>/ # authnificate
        send("<0 0>'e' n=#{$SERVERNAME}</0>\n")
    when /<login (.*)>(.*)<\/login>/
      result = login($1,$2)
      if result=="not exist"
        send("<login>'wu','standart'</login>\n")
      elsif result=="wrong password"
        send("<login>'wp','standart'</login>\n")
      elsif result=="logged in"
        send("<login>'lg','standart'</login>\n")
      elsif result=="ok"
        send("<login>'allow','#{@group}'</login>\n")
        send("<1>#{@netid}</1>\n")
        send("<2>#{$1}</2>\n")
        send("<exec>$no_pvp=#{$NO_PVP}</exec>\n")
      end
    when /<reges (.*)>(.*)<\/reges>/
      stats = register($1,$2)
        if stats == "exist"
         send("<reges>'exist'</reges>\n")
        else
          send("<reges>'ok'</reges>\n")
        end
    when /<5>(.*)<\/5>/
      return unless @char_id >= 1
      eval($1)
      sendall("<5 #{@netid}>#{$1}</5>\n")
    when /<ver>(.*)<\/ver>/
    @ver = $1
    send("<ver>#{@ver}</ver>\n")
    when /<1>(.*)<\/1>/
    send("<1>#{@netid}</1>\n")
    when /<2>(.*)<\/2>/
    send("<2>#{@name}</1>\n")
    when /<check>(.*)<\/check>/
    send("<check>'#{@group}'</check>\n")
    when /<mod>(.*)<\/mod>/
    send("<mod>#{$MOTD}</mod>\n")
    when /<exist>(.*)<\/exist>/
    @exist = @sql.query("SELECT banned FROM users WHERE name='#{$1}'")
    if @exist.num_rows() == 1
      send("<exist>1</exist>\n")
    else
      send("<exist>0</exist>\n")
    end
    when /<chat>(.*)<\/chat>/
    chat_log_add($1.to_s)
    puts "Chat{#{$1}}\n"
    sendall("<chat>#{$1}</chat>\n",true)
    when /<getpm>(.*)<\/getpm>/
    send("<getpm>#{$1}</getpm>\n")
    when /<21a>(.*)/
    send("<21a>'Confirmed'</21a>\n")
    when /<21>(.*)<\/21>/
    sendall("<21>#{$1}</21>\n")
    when /<9>(.*)<\/9>/
    remove
    when /<set_acc>(.*),(.*)<\/set_acc>/
    set_acc_type("#{$1}","#{$2}")
    when /<load (.*)>(.*)<\/load>/
    temp = load_char($1,$2.to_i)
    send("<load #{$2.to_i}>#{temp}</load>\n")
    when /<cs>(.*),(.*)<\/cs>/
    limit = $2.to_i
    for i in 0..limit
      temp = check_chars_created($1.to_s,i)
      if temp[0] == true
        send("<cselect>#{i.to_s},#{temp[1].to_s},#{temp[2].to_s}</cselect>\n")
      else
        send("<cselect>#{i.to_s},NE,NE</cselect>\n")
      end
    end
    when /<creat>(.*),(.*),(.*),(.*),(.*),(.*),(.*)<\/creat>/
    @char_id = ($1.to_i+1)
    @sql.query("INSERT INTO char#{@char_id}(owner,name) VALUES(#{$7},#{$2})")
    @sql.query("UPDATE char#{@char_id} SET raça_id=#{$3} WHERE owner=#{$7}")
    @sql.query("UPDATE char#{@char_id} SET class_id=#{$4} WHERE owner=#{$7}")
    @sql.query("UPDATE char#{@char_id} SET genero_id=#{$5} WHERE owner=#{$7}")
    @sql.query("UPDATE char#{@char_id} SET graphic_name=#{$6} WHERE owner=#{$7}")
    when /<banco (.*)>(.*)<\/banco>/
      return unless @char_id >= 1
      @gold = (@gold.to_i)
      @bank_gold = (@bank_gold.to_i)
      value = ($2.to_i)
      case $1.to_s
      when "add"
        if @gold >= value
          @gold -= value
          send("<banco 0>#{@gold}</banco>\n")
          @bank_gold += value
          @sql.query("UPDATE users SET bank_gold=#{@bank_gold} WHERE name='#{@username}'")
          return
        else
          send("<banco 2>0</banco>\n")
          return
        end
      when "rem"
        if @bank_gold >= value
          @gold += value
          send("<banco 1>#{@gold}</banco>\n")
          @bank_gold -= value
          @sql.query("UPDATE users SET bank_gold=#{@bank_gold} WHERE name='#{@username}'")
          return
        else
          send("<banco 3>0</banco>\n")
          return
        end
      end
    when /<del>(.*)<\/del>/
      puts "DeleteChar(Id,User) #{$1},#{@username}"
    when /<gmove>#(.*),(.*),(.*),(.*)<\/gmove>/
      sendall(msg,false)
    when /<ei>(.*)<\/ei>/
      return unless @char_id >= 1
      @sql.query("UPDATE char#{@char_id} SET equiped=#{$1} WHERE owner='#{user}'")
    else
      sendall(msg,true)
    end    
    return unless @char_id >= 1
    save_user_status(@username)
  end 
  
  def send(msg)
    sock.send(msg,0)
  end
  
  def remove
    @sql.query("UPDATE users SET loggedin=0 WHERE name='#{@username}'") if @username != ""
    sendall("<9>#{@netid}</9>\n")
    $clients.delete(self)
  end
  
  def sendall(data,including = false)
    # Sending to all
	clients.values.each do |client|
	next if (client.sock == @sock and !including) or client.netid==-1
      next if client.sock == nil
      next if client.sock.closed?
	    client.send(data)
    end
  end
  
  def ic
    return
  end
  
  def start(id)
    return
  end
  
  def sendmap(msg)
    for client in $clients.values
      if client.map_id == map_id
        client.send(msg)
      end
    end
  end

  def chech_rank_pos(user)
    @check = @sql.query("SELECT rank_pos FROM users WHERE name='#{user}'")
    return @check
  end

  def add_rank_pos(user, value)
    $old_pos = chech_rank_pos(user)
    $new_pos = ($old_pos+value)
    if $new_pos < 0
      $new_pos = 0
    end
    @sql.query("UPDATE users SET rank_pos=#{$new_pos} WHERE name='#{user}'")
  end
  
  def set_acc_type(user,value)
    case value
    when "on"
      @sql.query("UPDATE users SET group='Vip' WHERE name='#{user}'")
      @group="Vip"
    when "off"
     @sql.query("UPDATE users SET group='Standart' name='#{user}'")
     @group="Standart"
    when "adm"
      @sql.query("UPDATE users SET group='Admin' WHERE name='#{user}'")
      @group="Admin"
    when "gm"
      @sql.query("UPDATE users SET group='GM' WHERE name='#{user}'")
      @group="GM"
    end
  end
  
  def check_chars_created(user,id)
    graphic=""
    name=""
    checkcc = @sql.query("SELECT * FROM char#{id.to_i+1} WHERE owner='#{user}'")
    if checkcc.num_rows() < 1
      return [false,graphic,name]
    else
      hash = checkcc.fetch_hash
      graphic = hash['graphic_name'].to_s
      cname = hash['name'].to_s
      return [true,graphic,cname]
    end
  end
  
  def  save_user_status(user,char_id=@char_id)
    return unless @char_id >= 1
    @c_select = @sql.query("SELECT * FROM char#{@char_id} WHERE owner='#{user}'")
    if @c_select.num_rows() < 1
      return
    end
    @c_hash = @c_select.fetch_hash
    temp2 = "["
    if @states != nil
    for i in 0..@states.size
      if i == @states.size
        temp2+="#{@states[i]}"
      else
        temp2+="#{@states[i]},"
      end
    end
    temp2+="]"
    else 
    temp2="[]"
    end
    if @c_hash['states'].to_s != temp2.to_s
      @sql.query("UPDATE char#{char_id} SET states='#{temp2}' WHERE owner='#{user}'")
    end
    if @c_hash['hp'].to_i != @hp.to_i
      @sql.query("UPDATE char#{char_id} SET hp=#{@hp} WHERE owner='#{user}'")
    end
    if @c_hash['sp'].to_i != @sp.to_i
      @sql.query("UPDATE char#{char_id} SET sp=#{@sp} WHERE owner='#{user}'")
    end
    if @c_hash['map_id'].to_i != @map_id.to_i
      @sql.query("UPDATE char#{char_id} SET map_id=#{@map_id} WHERE owner='#{user}'")
    end
    if @c_hash['map_x'].to_i != @x.to_i
      @sql.query("UPDATE char#{char_id} SET map_x=#{@x} WHERE owner='#{user}'")
    end
    if @c_hash['map_y'].to_i != @y.to_i
      @sql.query("UPDATE char#{char_id} SET map_y=#{@y} WHERE owner='#{user}'")
    end
    if @c_hash['eva'].to_i != @eva.to_i
      @sql.query("UPDATE char#{char_id} SET eva=#{@eva} WHERE owner='#{user}'")
    end
    if @c_hash['agi'].to_i != @agi.to_i
      @sql.query("UPDATE char#{char_id} SET agi=#{@agi} WHERE owner='#{user}'")
    end
    if @c_hash['pdef'].to_i != @pdef.to_i
      @sql.query("UPDATE char#{char_id} SET pdef=#{@pdef} WHERE owner='#{user}'")
    end
    if @c_hash['mdef'].to_i != @mdef.to_i
      @sql.query("UPDATE char#{char_id} SET mdef=#{@mdef} WHERE owner='#{user}'")
    end
    if @c_hash['gold'].to_i != @gold.to_i
      @sql.query("UPDATE char#{char_id} SET gold=#{@gold} WHERE owner='#{user}'")
    end
    if @c_hash['graphic_name'].to_s != @character_name.to_s
      @sql.query("UPDATE char#{char_id} SET graphic_name='#{@character_name}' WHERE owner='#{user}'")
    end
    if @c_hash['map_direction'].to_i != @direction.to_i
      @sql.query("UPDATE char#{char_id} SET map_direction=#{@direction} WHERE owner='#{user}'")
    end
    if @c_hash['move_speed'].to_i != @move_speed.to_i
      @sql.query("UPDATE char#{char_id} SET move_speed=#{@move_speed} WHERE owner='#{user}'")
    end
    if @c_hash['move_frequency'].to_i != @move_frequency.to_i
      @sql.query("UPDATE char#{char_id} SET move_frequency=#{@move_frequency} WHERE owner='#{user}'")
    end
    if @c_hash['walk_anime'].to_s != @walk_anime.to_s
      @sql.query("UPDATE char#{char_id} SET walk_anime='#{@walk_anime}' WHERE owner='#{user}'")
    end
    if @c_hash['step_anime'].to_s != @step_anime.to_s
      @sql.query("UPDATE char#{char_id} SET step_anime='#{@step_anime}' WHERE owner='#{user}'")
    end
    if @c_hash['always_on_top'].to_s != @always_on_top.to_s
      @sql.query("UPDATE char#{char_id} SET always_on_top='#{@always_on_top}' WHERE owner='#{user}'")
    end
    if @c_hash['char_exp'].to_i != @exp.to_i
      @sql.query("UPDATE char#{char_id} SET char_exp=#{@exp} WHERE owner='#{user}'")
    end
    if @c_hash['maxhp'].to_i != @maxhp.to_i
      @sql.query("UPDATE char#{char_id} SET maxhp=#{@maxhp} WHERE owner='#{user}'")
    end
    if @c_hash['maxsp'].to_i != @maxsp.to_i
      @sql.query("UPDATE char#{char_id} SET maxsp=#{@maxsp} WHERE owner='#{user}'")
    end
    if @c_hash['str'].to_i != @str.to_i
      @sql.query("UPDATE char#{char_id} SET str=#{@str} WHERE owner='#{user}'")
    end
    if @c_hash['dex'].to_i != @dex.to_i
      @sql.query("UPDATE char#{char_id} SET dex=#{@dex} WHERE owner='#{user}'")
    end
    if @c_hash['inte'].to_i != @int.to_i
      @sql.query("UPDATE char#{char_id} SET inte=#{@int} WHERE owner='#{user}'")
    end
    if @c_hash['upp'].to_i != @upp.to_i
      @sql.query("UPDATE char#{char_id} SET upp=#{@upp} WHERE owner='#{user}'")
    end
    return
  end
  
  def load_char(user,char_id)
    @char_id = char_id
    @c_select = @sql.query("SELECT * FROM char#{char_id} WHERE owner='#{user}'")
    if @c_select.num_rows() < 1
      return ""
    end
    @c_hash = @c_select.fetch_hash
    @hp = @c_hash['maxhp'].to_i
    @sp = @c_hash['maxsp'].to_i
    @map_id = @c_hash['map_id'].to_i
    @x = @c_hash['map_x'].to_i
    @y = @c_hash['map_y'].to_i
    @dex = @c_hash['dex'].to_i
    @agi = @c_hash['agi'].to_i
    @pdef = @c_hash['pdef'].to_i
    @mdef = @c_hash['mdef'].to_i
    @gold = @c_hash['gold'].to_i
    @character_name = @c_hash['graphic_name'].to_s
    @direction = @c_hash['map_direction'].to_i
    @move_speed = @c_hash['move_speed'].to_i
    @move_frequency =@c_hash['move_frequency'].to_i
    @walk_anime = @c_hash['walk_anime'].to_s
    @step_anime = @c_hash['step_anime'].to_s
    @always_on_top = @c_hash['always_on_top'].to_s
    @exp = @c_hash['char_exp'].to_i
    @upp = @c_hash['upp'].to_i
    @raca_id = @c_hash['raça_id'].to_i
    @class_id = @c_hash['class_id'].to_i
    @name = @c_hash['name'].to_s
    msg = "[#{@hp},#{@sp},#{@map_id},#{@x},#{@y},#{@dex},#{@agi},#{@pdef},#{@mdef},#{@c_hash['states']},#{@gold},'#{@character_name}',#{@direction},#{@move_speed},#{@move_frequency},#{@walk_anime},#{@step_anime},#{@always_on_top},#{@exp},'#{@name}',#{@upp},#{@raca_id},#{@class_id}]"
    return msg
  end
  
  def chat_log_add(msg)
    file = File.open($log['chat'], "a+")
    file.write(msg+"\n")
    file.close()
  end
  
  def gain_item(id)
  end
  def gain_weapon(id)
  end
  def gain_armor(id)
  end
  def lose_item(id)
  end
  def lose_weapon(id)
  end
  def lose_armor(id)
  end
  def save_invetory(char_id=0)
  end
  
end #End of Client