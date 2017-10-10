#======================================================================
# Sender
#----------------------------------------------------------------------
# Provides methods for sending messages.
#======================================================================

class Sender
	
	#----------------------------------------------------------------------
	# Initialization.
	#----------------------------------------------------------------------
	def initialize(client)
		@client = client
	end
	#----------------------------------------------------------------------
	# Sends a message to the actual connected client.
	#  message - message that will be sent
	#----------------------------------------------------------------------
	def send(message)
		if !@client.socket.closed?
			@client.socket.send(message + "\n", 0)
			RMXOS.log(@client.player, 'Outgoing Message', message) if RMXOS.server.options.log_messages
		end
	end
	#----------------------------------------------------------------------
	# Gets all clients on the same map including or excluding self.
	#  including - whether to include or exclude this client
	# Returns: Clients on the same map.
	#----------------------------------------------------------------------
	def get_map_clients(including = false)
		# find all clients on this map
		clients = $clients.find_all {|client| client.player.map_id == @client.player.map_id}
		# exclude self if necessary
		clients.delete(@client) if !including
		return clients
	end
	#----------------------------------------------------------------------
	# Gets all clients on the same map including or excluding self.
	#  including - whether to include or exclude this client
	# Returns: Clients in the same guild.
	#----------------------------------------------------------------------
	def get_guild_clients(including = false)
		# find all clients in the guild
		clients = $clients.find_all {|client| client.player.guildname == @client.player.guildname}
		# exclude self if necessary
		clients.delete(@client) if !including
		return clients
	end
	#----------------------------------------------------------------------
	# Gets all clients including or excluding self.
	#  including - whether to include or exclude this client
	# Returns: All connected clients.
	#----------------------------------------------------------------------
	def get_all_clients(including = false)
		# find all clients in the guild
		clients = $clients.clone
		# exclude self if necessary
		clients.delete(@client) if !including
		return clients
	end
	#----------------------------------------------------------------------
	# Finds the client with a specific username.
	#  username - username of the connected client
	# Returns: Either the client or nil if not found.
	#----------------------------------------------------------------------
	def get_client_by_name(username)
		$clients.each {|client| return client if client.player.username.downcase == username.downcase}
		return nil
	end
	#----------------------------------------------------------------------
	# Finds the client with a specific user ID.
	#  user_id - user ID of the connected client
	# Returns: Either the client or nil if not found.
	#----------------------------------------------------------------------
	def get_client_by_id(user_id)
		$clients.each {|client| return client if client.player.user_id == user_id}
		return nil
	end
	#----------------------------------------------------------------------
	# Sends a message to all clients.
	#  message - message that will be sent
	#  including - whether to include or exclude this client
	#----------------------------------------------------------------------
	def send_to_all(message, including = false)
		# get all clients
		clients = $clients.clone
		# exclude self if necessary
		clients.delete(@client) if !including
		# send them a message
		self.send_to_clients(clients, message)
	end
	#----------------------------------------------------------------------
	# Sends a message to all clients on the same map.
	#  message - message that will be sent
	#  including - whether to include or exclude this client
	#----------------------------------------------------------------------
	def send_to_map(message, including = false)
		# get all clients on the same map
		clients = self.get_map_clients(including)
		# send them a message
		self.send_to_clients(clients, message)
	end
	#----------------------------------------------------------------------
	# Sends a message to all clients in the same guild.
	#  message - message that will be sent
	#  including - whether to include or exclude this client
	#----------------------------------------------------------------------
	def send_to_guild(message, including = false)
		# send them a message
		self.send_to_clients(self.get_guild_clients(including), message)
	end
	#----------------------------------------------------------------------
	# Sends a message to actual clients.
	#  clients - clients that will receive the message
	#  message - message that will be sent
	#----------------------------------------------------------------------
	def send_to_clients(clients, message)
		clients.each {|client|
			# skip if no connection exists
			next if client.socket == nil
			# skip if connection is closed
			next if client.socket.closed?
			# skip if this client isn't logged in yet
			next if client.player.user_id <= 0
			client.send(message)
		}
	end
	#----------------------------------------------------------------------
	# Sends a message to a specific actual client.
	#  username - username of the client
	#  message - message that will be sent
	# Returns: Whether the sending succeeded or failed.
	#----------------------------------------------------------------------
	def send_to_name(username, message)
		client = self.get_client_by_name(username)
		# client not found
		return false if client == nil
		# failed if no connection exists
		return false if client.socket == nil
		# failed if connection is closed
		return false if client.socket.closed?
		# success
		client.send(message)
		return true
	end
	#----------------------------------------------------------------------
	# Sends a message to a specific actual client.
	#  user_id - user ID of the client
	#  message - message that will be sent
	# Returns: Whether the sending succeeded or failed.
	#----------------------------------------------------------------------
	def send_to_id(user_id, message)
		client = self.get_client_by_id(user_id)
		# client not found
		return false if client == nil
		# failed if no connection exists
		return false if client.socket == nil
		# failed if connection is closed
		return false if client.socket.closed?
		# success
		client.send(message)
		return true
	end

end