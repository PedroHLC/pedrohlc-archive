class Client
 
  attr_accessor     :id
  attr_accessor     :x
  attr_accessor     :y
  attr_accessor     :real_x
  attr_accessor     :real_y
  attr_accessor     :tile_id
  attr_accessor     :character_name
  attr_accessor     :character_hue
  attr_accessor     :opacity
  attr_accessor     :blend_type
  attr_accessor     :direction
  attr_accessor     :pattern
  attr_accessor     :move_route_forcing
  attr_accessor     :through
  attr_accessor     :animation_id
  attr_accessor     :transparent
  attr_accessor     :class_id
  attr_accessor     :raca_id
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
  attr_accessor     :equiped
  attr_accessor     :guild
  
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
    @equiped = ""
    @item = ""
    @weapon = ""
    @armor = ""
    @guild = ""
    @banned = 0
    @job = ""
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
    @banned = @hash['banned'].to_i 
    if @banned == 1
      return "not exist"
    end
    if @hash['loggedin'].to_i == 1
      return "logged in"
    end
    @loggedin = 1
    @name = name.to_s.downcase
    @netid = @hash['id'].to_i
    @bank_gold = @hash['bank_gold'].to_i
    @group = @hash['net_group'].to_s.downcase
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
    when /<0>'e'<\/0>/
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
        send("<2>#{@name}</2>\n")
        if $NO_PVP == true
          send("<exec>$no_pvp=1;</exec>\n")
        else
          send("<exec>$no_pvp=0;</exec>\n")
        end
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
    send("<2>#{@name}</2>\n")
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
    puts "Chat Filter NIL"if $chat_filter == nil
    mau_linguajar = false
    for i in 0..($chat_filter.size - 1)
      if $1.to_s.downcase.include?($chat_filter[i].to_s)
        mau_linguajar = true
      end
    end
    if mau_linguajar == true
      send("<chat>Administração: Por Favor modere o seu linguajar!</chat>\n")
    else
      puts "Chat{#{$1}}\n"
      sendall("<chat>#{$1}</chat>\n",true)
    end
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
    send("<load #{$2.to_i}>#{load_char($1,$2.to_i)}</load>\n")
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
    @guild = ""
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
    when /<oc (.*)>(.*)<\/oc>/
      for client in $clients.values
        if client.name = $1.to_s
          eval("client.#{$2}")
          break
          return
        end
      end
    when /<del>(.*)<\/del>/
      puts "DeleteChar(Id,User) #{$1},#{@username}"
    when /<gmove>(.*),(.*),(.*),(.*)<\/gmove>/
      sendall(msg,false)
    when /<ei>(.*)<\/ei>/
      return unless @char_id >= 1
      @equiped = $1.to_s
      @sql.query("UPDATE char#{@char_id} SET equiped=#{$1} WHERE owner='#{@username}'")
    when /<guild>(.*),(.*)<\/guild>/
      if $1.to_s.downcase.include?("check")
        if @char_id.to_i <= 0
          send("<guild>check,</guild>\n")
          return
        end
        #@guild = @sql.query("SELECT char_guild FROM char#{@char_id} WHERE name='#{@username}'")
        send("<guild>check,#{@guild}</guild>\n")
      elsif $1.to_s.downcase.include?("create")
        if @sql.query("SELECT * FROM guilds WHERE name='#{$2.to_s.downcase}'").num_rows() >= 1
          send("<guild>create,1</guild>\n")
        else
          @guild = $2.to_s.downcase
          @sql.query("INSERT INTO guilds(name,master_char,master_owner) VALUES('#{@guild}','#{@name}','#{@username}')")
          @sql.query("UPDATE char#{@char_id} SET char_guild='#{@guild}' WHERE owner='#{@username}'")
          send("<guild>create,0</guild>\n<5>@guild=#{@guild}</5>\n")
        end
      elsif $1.to_s.downcase.include?("enter")
        if @sql.query("SELECT * FROM guilds WHERE name='#{$2.to_s.downcase}'").num_rows() >= 1
          @guild = $2.to_s.downcase
          @sql.query("UPDATE char#{@char_id} SET char_guild='#{@guild}' WHERE owner='#{@username}'")
          members_old = @sql.query("SELECT members FROM guilds WHERE name='#{$2.to_s.downcase}'")
          members = "#{members_old}(#{@username},#{@name});"
          @sql.query("UPDATE guilds SET members='#{members}' WHERE name='#{$2.to_s.downcase}'")
          send("<guild>enter,1</guild>\n")
        else
          send("<guild>enter,0</guild>\n")
        end
      end
    else
      sendall(msg,true)
    end    
    save_user_status(@username)
  end 
  
  def send(msg)
    if $DEBUG_MSG and !msg.include?("<5>") and !msg.include?("<6>")
      neo_puts(I18n.t(:server_sended)+"(#{@sock.peeraddr[2]}): #{msg.strip}\n")
    end
    file = File.open($log['messages'], "a+")
    file.write(I18n.t(:server_sended)+"(#{@sock.peeraddr[2]}): #{msg.strip}\n")
    file.close()
    sock.send(msg,0)
  end
  
  def remove
    @sql.query("UPDATE users SET loggedin=0 WHERE name='#{@username}'") if @username != ""
    sendall("<9>#{@netid}</9>\n") if @netid != nil
    #$clients.delete(self)
  end
  
  def sendall(data,including=false)# Sending to all
    file = File.open($log['messages'], "a+")
    if including
      file.write(I18n.t(:server_sended)+"(ALL/TODOS): #{data.to_s.strip}")
      neo_puts(I18n.t(:server_sended)+"(ALL/TODOS): #{data.to_s.strip}") if $DEBUG
    else
      file.write(I18n.t(:server_sended)+"(ALL/TODOS-#{@sock.peeraddr[2].to_s.strip}): #{data}")
      neo_puts(I18n.t(:server_sended)+"(ALL/TODOS-#{@sock.peeraddr[2].to_s.strip}): #{data}") if $DEBUG
    end
    file.close()
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
  
  def  save_user_status(user)
    char_id = @char_id
    unless char_id >= 1
      return
    end
    @c_select = @sql.query("SELECT * FROM char#{char_id} WHERE owner='#{user}'")
    if @c_select.num_rows() < 1
      return
    end
    @c_hash = @c_select.fetch_hash
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
    if @c_hash['walk_anime'].to_i != @walk_anime.to_i
      @sql.query("UPDATE char#{char_id} SET walk_anime='#{@walk_anime}' WHERE owner='#{user}'")
    end
    if @c_hash['step_anime'].to_i != @step_anime.to_i
      @sql.query("UPDATE char#{char_id} SET step_anime='#{@step_anime}' WHERE owner='#{user}'")
    end
    if @c_hash['always_on_top'].to_i != @always_on_top.to_i
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
      @sql.query("UPDATE char#{char_id} SET str=#{@str.to_i} WHERE owner='#{user}'")
    end
    if @c_hash['dex'].to_i != @dex.to_i
      @sql.query("UPDATE char#{char_id} SET dex=#{@dex.to_i} WHERE owner='#{user}'")
    end
    if @c_hash['inte'].to_i != @int.to_i
      @sql.query("UPDATE char#{char_id} SET inte=#{@int.to_i} WHERE owner='#{user}'")
    end
    if @c_hash['agi'].to_i != @agi.to_i
      @sql.query("UPDATE char#{char_id} SET agi=#{@agi} WHERE owner='#{user}'")
    end
    if @c_hash['upp'].to_i != @upp.to_i
      @sql.query("UPDATE char#{char_id} SET upp=#{@upp} WHERE owner='#{user}'")
    end
    if @c_hash['items'] != @item
      @sql.query("UPDATE char#{char_id} SET items='#{@item}' WHERE owner='#{user}'")
    end
    if @c_hash['weapons'] != @weapon
      @sql.query("UPDATE char#{char_id} SET weapons='#{@weapon}' WHERE owner='#{user}'")
    end
    if @c_hash['armors'] != @armor
      @sql.query("UPDATE char#{char_id} SET armors='#{@armor}' WHERE owner='#{user}'")
    end
    if @c_hash['skills'] != @skills
      @sql.query("UPDATE char#{char_id} SET skills='#{@skills}' WHERE owner='#{user}'")
    end
    if @c_hash['skill_key'] != @skill_key
      @sql.query("UPDATE char#{char_id} SET skill_key='#{@skill_key}' WHERE owner='#{user}'")
    end
    if @c_hash['states'] != @states
      @sql.query("UPDATE char#{char_id} SET states='#{@states}' WHERE owner='#{user}'")
    end
    if @c_hash['player_job'] != @job
      @sql.query("UPDATE char#{char_id} SET player_job='#{@job}' WHERE owner='#{user}'")
    end
    return
  end
  
  def load_char(user,char_id)
    @char_id = char_id.to_i
    @c_select = @sql.query("SELECT * FROM char#{char_id} WHERE owner='#{user}'")
    if @c_select.num_rows() < 1
      return ""
    end
    @c_hash = @c_select.fetch_hash
    @maxhp = @hp = @c_hash['maxhp'].to_i
    @maxsp = @sp = @c_hash['maxsp'].to_i
    @map_id = @c_hash['map_id'].to_i
    @x = @c_hash['map_x'].to_i
    @y = @c_hash['map_y'].to_i
    @str = @c_hash['str'].to_i
    @int = @c_hash['inte'].to_i
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
    @equiped = @c_hash['equiped'].to_s
    @guild = @c_hash['char_guild'].to_s
    @skills= @c_hash['skills'].to_s
    @skill_key = @c_hash['skill_key'].to_i
    @item = @c_hash['items'].to_s
    @weapon =@c_hash['weapons'].to_s
    @armor = @c_hash['armors'].to_s
    @states = @c_hash['states'].to_s
    @job = @c_hash['player_job'].to_s
    #Fix
    @skills = "[]" if @skills.to_s == ""
    @item = "[]" if @item.to_s == ""
    @weapon = "[]" if @weapon.to_s == ""
    @armor = "[]" if @armor.to_s == ""
    @states = "[]" if @states.to_s == ""
    #End of "Fix"
    msg = "[#{@maxhp},#{@maxsp},#{@map_id},#{@x},#{@y},#{@dex},#{@agi},#{@pdef},#{@mdef},[],#{@gold},'#{@character_name}',#{@direction},#{@move_speed},#{@move_frequency},#{@walk_anime},#{@step_anime},#{@always_on_top},#{@exp},'#{@name}',#{@upp},#{@raca_id},#{@class_id},'#{@equiped}',#{@str},#{@int},'#{@guild}',#{@skills},#{@skill_key},#{@item},#{@weapon},#{@armor},#{@states},'#{@job}']"
    return msg
  end
  
  def send_inventory
  end
  
  def chat_log_add(msg)
    file = File.open($log['chat'], "a+")
    file.write(msg+"\n")
    file.close()
  end
  
  def block
    @sql.query("UPDATE users SET banned=1 WHERE name='#{@username}'") if @username != "" and @banned != 1
    @banned = 1
    send("<5>#{self.banned}</5>\n")
    remove
  end
  
end #End of Client