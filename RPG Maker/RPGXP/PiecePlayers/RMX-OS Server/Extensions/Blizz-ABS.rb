module RMXOS
  
  def self.load_current_extension
    return BlizzABS
  end
  
  module Data
    GlobalMasterActivate = 'Client \'CLIENT\' activate G-Master for map \'MAPID\'.'
    GlobalMasterDeactivate = 'Client \'CLIENT\' deactivate G-Master for map \'MAPID\'.'
    GlobalMasterRelease = 'Map \'MAPID\' has been released.'
    PartyDisbanded = 'The party has been disbanded.'
    PartyFull = 'Your party is already full.'
    PartyFullPlayer = 'The party of \'PLAYER\' is already full.'
    PartyInvitation = '\'PLAYER\' has invited you to join a party.'
    PartyInvited = 'You have invited \'PLAYER\' to join your party.'
    PartyJoined = 'You have joined the party of \'PLAYER\'.'
    PartyJoinedPlayer = '\'PLAYER\' has joined the party.'
    PartyNoJoinPlayer = '\'PLAYER\' has not accepted the party invitation.'
    PartyNotOnline = '\'PLAYER\' is not online anymore.'
    PartyRemoved = 'You have left the party.'
    PartyRemovedPlayer = '\'PLAYER\' has left the party.'
  end
  
end

#======================================================================
# module BlizzABS
#======================================================================

module BlizzABS
  
  VERSION = 1.4
  RMXOS_VERSION = 1.18
  SERVER_THREAD = true
  IDENTIFIER = 'Blizz-ABS'
  
  # START Configuration
  MAX_ONLINE_PARTY = 5
  GMASTER_TIMEOUT = 5 # after how much an inactive time global master client should be released
  SERVER_DISPLAY = false # show log in command prompt screen
  LOG_FILENAME = 'logs/blizzabs.log' # leave empty if no log file should be created
  DELETE_LOG_ON_START = true
  # END Configuration
  
  def self.initialize
    @client_times = {}
    @gmasters = {}
    @capable_clients = {}
    @battlers = {}
    if LOG_FILENAME != ''
      File.delete(LOG_FILENAME) if DELETE_LOG_ON_START && FileTest.exist?(LOG_FILENAME)
      RMXOS::Logs[IDENTIFIER] = LOG_FILENAME
    end
  end
  
  def self.main
    while RMXOS.server.running
      self.server_update
      sleep(0.1)
    end
  end
  
  def self.server_update
    Thread.exclusive {
      time = Time.now
      logged_in_clients = $clients.find_all {|client| client.player.user_id > 0}
      old_clients = @client_times.keys - logged_in_clients
      old_clients.each {|client|
        @client_times.delete(client)
        @capable_clients.delete(@capable_clients.key(client))
        self.try_deactivate_gmaster(client)
        if client.player.partyleader != ''
          client.action.execute_party_remove(client.player.username, client.player.partyleader)
        end
      }
      new_clients = logged_in_clients - @client_times.keys
      new_clients.each {|client| @client_times[client] = time}
      @capable_clients.keys.each {|key|
        if time - @client_times[@capable_clients[key]] > GMASTER_TIMEOUT
          client = @capable_clients[key]
          @capable_clients.delete(key)
          self.try_deactivate_gmaster(client)
        end
      }
      (@capable_clients.values - logged_in_clients).each {|client| @capable_clients.delete(@capable_clients.key(client))}
      map_ids = []
      logged_in_clients.each {|client| map_ids.push(client.player.map_id)}
      map_ids |= map_ids
      (@battlers.keys - map_ids).each {|map_id| @battlers.delete(map_id) if @battlers.has_key?(map_id)}
      (@gmasters.keys - map_ids).each {|map_id| self.release_map(map_id)}
      (map_ids - @gmasters.keys).each {|map_id| self.try_activate_gmaster(map_id)}
    }
  end
  
  def self.client_update(client)
    result = false
    case client.message
    when /\AGMD\Z/ # deactivate capable global master client
      @capable_clients.delete(client.player.user_id) if @capable_clients.has_key?(client.player.user_id)
      self.try_deactivate_gmaster(client, client.player.map_id) if client == @gmasters[client.player.map_id]
      result = true
    when /\APNG\Z/ # client ping
      if client.player.user_id != 0
        @client_times[client] = Time.now
        @capable_clients[client.player.user_id] = client if !@capable_clients.has_key?(client.player.user_id)
      end
    when /\AMEE(.+)\t(.+)/ # exchange variables for enemies
      id = $1.to_i
      variables = eval($2)
      @battlers[client.player.map_id] = {} if !@battlers.has_key?(client.player.map_id)
      @battlers[client.player.map_id][id] = Player.new(nil) if !@battlers[client.player.map_id].has_key?(id)
      @battlers[client.player.map_id][id].evaluate(variables)
      client.sender.send_to_map(client.message)
      result = true
    when /\AMEN(.+)/ # enter map
      map_id = $1.to_i
      if @battlers.has_key?(map_id)
        @battlers[map_id].each_key {|id|
          client.send("MEE#{id}\t#{@battlers[map_id][id].get_exchange_variables}")
        }
      end
    when /\ABED(.+)\t(.+)/ # broadcast enemy death
      if @gmasters[client.player.map_id] == client
        client.sender.send_to_map(client.message, true)
      else
        id = $1.to_i
        client.send("MEE#{id}\t#{@battlers[client.player.map_id][id].get_exchange_variables}")
      end
      result = true
    when /\AIRM(.+)\t(.+)/ # item remove
      if @gmasters[client.player.map_id] == client
        user_id, item_id = $1.to_i, $2.to_i
        client.sender.send_to_id(user_id, "IRM#{item_id}")
      end
      result = true
    when /\APIN(.+)/ # party invitation
      username = $1
      result = client.action.try_party_invite(username)
      case result
      when RMXOS::RESULT_SUCCESS
        message = RMXOS::Data::PartyInvited.sub('PLAYER') {username}
        color = RMXOS::Data::ColorInfo
      when RMXOS::RESULT_FAIL
        message = RMXOS::Data::PlayerNotOnlineMap.sub('PLAYER') {username}
        color = RMXOS::Data::ColorError
      when RMXOS::RESULT_ALTFAIL
        message = RMXOS::Data::PartyFull
        color = RMXOS::Data::ColorError
      end
      client.send("CHT#{color}\t0\t#{message}")
      result = true
    when /\APLE\Z/ # party leave
      client.action.execute_party_remove(client.player.username, client.player.partyleader)
      result = true
    when /\APRE(.+)/ # party remove
      username = $1
      client.action.execute_party_remove(username, client.player.partyleader)
      result = true
    when /\APME(.+)/ # party message
      client.sender.send_to_party("CHT#{$1}", true)
      result = true
    end
    return result
  end
  
  def self.try_activate_gmaster(map_id)
    return if @gmasters.has_key?(map_id)
    clients = @capable_clients.values.find_all {|client| client.player.map_id == map_id}
    return if clients.size == 0
    client = clients[0]
    client.send('GMA')
    @gmasters[map_id] = client
    if !@battlers.has_key?(map_id)
      @battlers[map_id] = {}
      client.send('MDR')
    end
    message = RMXOS::Data::GlobalMasterActivate.sub('CLIENT', client.player.username).sub('MAPID', map_id.to_s)
    self.log(message)
  end
  
  def self.try_deactivate_gmaster(client, map_id = nil)
    if map_id == nil
      @gmasters.each_key {|key|
        if client == @gmasters[key]
          map_id = key
          break
        end
      }
    end
    return if map_id == nil
    @gmasters.delete(map_id)
    client.send('GMD')
    message = RMXOS::Data::GlobalMasterDeactivate.sub('CLIENT', client.player.username).sub('MAPID', map_id.to_s)
    self.log(message)
    self.try_activate_gmaster(map_id)
    self.release_map(map_id) if !@gmasters.has_key?(map_id)
  end
  
  def self.release_map(map_id)
    @gmasters.delete(map_id) if @gmasters.has_key?(map_id)
    message = RMXOS::Data::GlobalMasterRelease.sub('MAPID', map_id.to_s)
    self.log(message)
  end
  
  def self.log(message)
    puts message if SERVER_DISPLAY
    RMXOS.log(IDENTIFIER, 'Log', message)
  end
  
end

#======================================================================
# Player
#======================================================================

class Player

  IGNORE_VARIABLES.push('@battler|@damage')
  IGNORE_VARIABLES.push('@battler|@hpdamage')
  IGNORE_VARIABLES.push('@battler|@spdamage')
  IGNORE_VARIABLES.push('@ai|@act|@kind')
  IGNORE_VARIABLES.push('@ai|@act|@id')
  
  attr_accessor :party
  attr_accessor :partyleader
  
  alias initialize_blizzabsrmxos_later initialize
  def initialize(client)
    initialize_blizzabsrmxos_later(client)
    self.reset_party
  end
  
  def reset_party
    @partyleader = ''
    @party = []
  end
  
end

#======================================================================
# Action
#======================================================================

class Action
  
  TYPE_PARTY_JOIN = 111
  
end
  
#======================================================================
# Action_Handler
#======================================================================

class Action_Handler
  
  def try_party_invite(username)
    return RMXOS::RESULT_ALTFAIL if @client.player.party.size >= BlizzABS::MAX_ONLINE_PARTY - 1
    client = @client.sender.get_client_by_name(username)
    return RMXOS::RESULT_FAIL if client == nil
    return RMXOS::RESULT_FAIL if client.player.map_id != @client.player.map_id
    client.action.current.type = Action::TYPE_PARTY_JOIN
    client.action.current.data = [@client.player.user_id, @client.player.username]
    message = "#{RMXOS::Data::PartyInvitation.sub('PLAYER') {@client.player.username}} #{RMXOS::Data::DoYouAccept}"
    client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
    return RMXOS::RESULT_SUCCESS
  end
  
  def execute_party_join
    user_id, leadername = @current.data
    leader = @client.sender.get_client_by_id(user_id)
    if leader == nil
      message = RMXOS::Data::PlayerNotOnlineMap.sub('PLAYER') {leadername}
      @client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{RMXOS::Data::PartyNotOnline}")
      return
    end
    if leader.player.party.size >= BlizzABS::MAX_ONLINE_PARTY - 1
      message = RMXOS::Data::PartyFullPlayer.sub('PLAYER') {leadername}
      @client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
      return
    end
    leader.player.party |= [@client.player.username]
    @client.player.party = leader.player.party.clone
    @client.player.partyleader = leader.player.partyleader = leadername
    message = RMXOS::Data::PartyJoined.sub('PLAYER') {leadername}
    @client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
    @client.send("PIN#{leadername}\t#{leader.player.party.inspect}")
    message = RMXOS::Data::PartyJoinedPlayer.sub('PLAYER') {@client.player.username}
    @client.sender.get_party_clients.each {|client|
      client.send("PIN#{leadername}\t#{leader.player.party.inspect}")
      client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
      client.player.party = leader.player.party.clone
    }
  end
  
  def execute_party_remove(username, leadername)
    client = @client.sender.get_client_by_name(username)
    clients = $clients.find_all {|client| client.player.partyleader == leadername}
    leader = @client.sender.get_client_by_name(leadername)
    party = clients - [client, leader]
    if username == leadername || leader == nil || party.size == 0
      clients.each {|client|
        if !client.socket.closed?
          client.send('PRM')
          client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{RMXOS::Data::PartyDisbanded}")
          client.player.reset_party
        end
      }
      return
    end
    if client != nil
      client.send('PRM')
      message = RMXOS::Data::PartyRemoved
      client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
      client.player.reset_party
    end
    leader.sender.send_to_party("PRE#{username}", true)
    message = RMXOS::Data::PartyRemovedPlayer.sub('PLAYER') {username}
    leader.sender.send_to_party("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}", true)
  end
  
  alias execute_yes_blizzabsrmxos_later execute_yes
  def execute_yes
    if @current.type == Action::TYPE_PARTY_JOIN
      self.execute_party_join
      @current.clear
    else
      execute_yes_blizzabsrmxos_later
    end
  end
  
  alias execute_no_blizzabsrmxos_later execute_no
  def execute_no
    if @current.type == Action::TYPE_PARTY_JOIN
      @client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{RMXOS::Data::PartyNoJoin}")
      name = @current.data[1]
      if name != nil
        message = RMXOS::Data::PartyNoJoinPlayer.sub('PLAYER') {@client.player.username}
        @client.sender.send_to_name(name, "CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
      end
      @current.clear
    else
      execute_no_blizzabsrmxos_later
    end
  end
  
end

#======================================================================
# Sender
#======================================================================

class Sender
  
  def get_party_clients(including = false)
    clients = $clients.find_all {|client| client.player.partyleader == @client.player.partyleader}
    clients.delete(@client) if !including
    return clients
  end

  def send_to_party(message, including = false)
    self.send_to_clients(self.get_party_clients(including), message)
  end
  
end