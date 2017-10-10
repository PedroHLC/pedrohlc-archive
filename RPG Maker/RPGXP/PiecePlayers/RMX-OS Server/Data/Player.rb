#======================================================================
# Player
#----------------------------------------------------------------------
# Contains player related data.
#======================================================================

class Player
	
	IGNORE_VARIABLES = []
	
	# setting all accessible variables
	attr_accessor :user_id
	attr_accessor :username
	attr_accessor :usergroup
	attr_accessor :buddies
	attr_accessor :guildname
	attr_accessor :guildleader
	attr_accessor :guildmembers
	attr_accessor :map_id
	attr_reader   :exchange_variables
	
	#----------------------------------------------------------------------
	# Initialization.
	#----------------------------------------------------------------------
	def initialize(client)
		@client = client
		# database data for this user
		@user_id = -1
		@username = ''
		@usergroup = RMXOS::GROUP_PLAYER
		@buddies = []
		self.reset_guild
		# very useful when saving the transmitting map status since it's already on the server
		@map_id = 0
		@exchange_variables = {}
	end
	#----------------------------------------------------------------------
	# Resets guild data.
	#----------------------------------------------------------------------
	def reset_guild
		@guildname = ''
		@guildleader = ''
		@guildmembers = []
	end
	#----------------------------------------------------------------------
	# Evaluates the received data.
	# variables - array of exchange_variables
	#----------------------------------------------------------------------
	def evaluate(variables)
		(variables.keys - IGNORE_VARIABLES).each {|key| @exchange_variables[key] = variables[key]}
	end
	#----------------------------------------------------------------------
	# Cets all player data.
	# Returns: Data string.
	#----------------------------------------------------------------------
	def get_all_data
		return "#{self.get_current_data}\t#{@map_id}"
	end
	#----------------------------------------------------------------------
	# Cets player data for the current map.
	# Returns: Data string.
	#----------------------------------------------------------------------
	def get_current_data
		return "#{self.get_player_data}\t#{self.get_exchange_variables}"
	end
	#----------------------------------------------------------------------
	# Cets player data.
	# Returns: Data string.
	#----------------------------------------------------------------------
	def get_player_data
		data = []
		data.push(@user_id.to_s)
		data.push(RMXOS.fix_string(@username))
		data.push(@usergroup.to_s)
		return "#{data.join("\t")}"
	end
	#----------------------------------------------------------------------
	# Cets player exchange variables.
	# Returns: Data string.
	#----------------------------------------------------------------------
	def get_exchange_variables
		return @exchange_variables.inspect
	end
	#----------------------------------------------------------------------
	# Cets buddies as list.
	# Returns: Buddies as list.
	#----------------------------------------------------------------------
	def get_buddies_list
		return (@buddies.size == 0 ? 'nil' : @buddies.map {|name| name = "'#{RMXOS.fix_string(name)}'"}.join(','))
	end
	#----------------------------------------------------------------------
	# Cets guild members as list.
	# Returns: Guild members as list.
	#----------------------------------------------------------------------
	def get_guildmembers_list
		return (@guildmembers.size == 0 ? 'nil' : @guildmembers.map {|name| name = "'#{RMXOS.fix_string(name)}'"}.join(','))
	end

end