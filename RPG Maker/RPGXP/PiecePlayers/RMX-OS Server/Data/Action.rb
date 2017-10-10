#======================================================================
# Action
#----------------------------------------------------------------------
# Represents an action setup.
#======================================================================

class Action
	
	# enumeration of action types
	TYPE_NONE = 0
	
	TYPE_PASSWORD_CHANGE = 11
	
	TYPE_GUILD_PASSWORD_CHANGE = 21
	TYPE_GUILD_DISBAND = 22
	TYPE_GUILD_TRANSFER = 23
	TYPE_GUILD_JOIN = 24
	TYPE_GUILD_LEAVE = 25
	
	TYPE_TRADE_REQUEST = 31
	
	TYPE_BUDDY_ADD = 41
	TYPE_BUDDY_REMOVE = 42
	
	TYPE_PM_DELETE = 51
	TYPE_PM_DELETE_ALL = 52
	
	# setting all accessible variables
	attr_accessor :type
	attr_accessor :data
	
	#----------------------------------------------------------------------
	# Initialization.
	#----------------------------------------------------------------------
	def initialize
		self.clear
	end
	#----------------------------------------------------------------------
	# Clears last action data
	#----------------------------------------------------------------------
	def clear
		@type = TYPE_NONE
		@data = nil
	end
	#----------------------------------------------------------------------
	# Checks if the last action is valid.
	# Returns: True or False.
	#----------------------------------------------------------------------
	def valid?
		return (@type != TYPE_NONE)
	end
	
end
