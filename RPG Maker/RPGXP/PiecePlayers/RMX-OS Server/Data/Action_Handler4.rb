#======================================================================
# Action_Handler
#----------------------------------------------------------------------
# Handles guild related actions.
#======================================================================

class Action_Handler
	
	#----------------------------------------------------------------------
	# Creates a guild.
	#  guildname - name of the new guild
	#  password - password for new guild
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_guild_create(guildname, password)
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM guilds WHERE guildname = '#{RMXOS.fix_string(guildname)}'")
		hash = check.fetch_hash
		# guild already exists
		return RMXOS::RESULT_FAIL if hash['count'].to_i > 0
		# register the new guild
		RMXOS.server.sql.query("START TRANSACTION")
		RMXOS.server.sql.query("INSERT INTO guilds (guildname, password, leader_id) VALUES ('#{RMXOS.fix_string(guildname)}', '#{password}', #{@client.player.user_id})")
		check = RMXOS.server.sql.query("SELECT guild_id FROM guilds WHERE guildname = '#{RMXOS.fix_string(guildname)}'")
		hash = check.fetch_hash
		RMXOS.server.sql.query("UPDATE user_data SET guild_id = #{hash['guild_id']} WHERE user_id = #{@client.player.user_id}")
		RMXOS.server.sql.query("COMMIT")
		# setup guild data
		@client.player.guildname = guildname
		@client.player.guildleader = @client.player.username
		@client.player.guildmembers = [@client.player.username]
		# send guild data to player
		@client.send("GIN#{guildname}\t#{@client.player.guildleader}\t#{@client.player.get_guildmembers_list}")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Changes the guild password.
	#  oldpass - old encrypted password
	#  newpass - new encrypted password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_guild_password_change(oldpass, newpass)
		check = RMXOS.server.sql.query("SELECT guild_id, password FROM guilds WHERE guildname = '#{RMXOS.fix_string(@client.player.guildname)}'")
		hash = check.fetch_hash
		# password check
		return RMXOS::RESULT_FAIL if oldpass != hash['password']
		# prepare yes/no action
		@current.type = Action::TYPE_GUILD_PASSWORD_CHANGE
		@current.data = [hash['guild_id'].to_i, newpass, @client.player.guildname]
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Transfers leadership of the guild.
	#  username - username of the new leader
	#  password - guild password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_guild_transfer(username, password)
		check = RMXOS.server.sql.query("SELECT password FROM guilds WHERE guildname = '#{RMXOS.fix_string(@client.player.guildname)}'")
		hash = check.fetch_hash
		# password check
		return RMXOS::RESULT_FAIL if password != hash['password']
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		# player doesn't exist
		return RMXOS::RESULT_ALTFAIL if hash['count'].to_i == 0
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		# not online
		return RMXOS::RESULT_ALTFAIL if client == nil
		# not on the same map
		return RMXOS::RESULT_ALTFAIL if client.player.map_id != @client.player.map_id
		# prepare invitation
		client.action.current.type = Action::TYPE_GUILD_TRANSFER
		# send invitation
		message = "#{RMXOS::Data::GuildTransfer.sub('PLAYER') {@client.player.guildleader}} #{RMXOS::Data::DoYouAccept}"
		client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Disbands the guild.
	#  password - guild password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_guild_disband(password)
		check = RMXOS.server.sql.query("SELECT guild_id, password FROM guilds WHERE guildname = '#{RMXOS.fix_string(@client.player.guildname)}'")
		hash = check.fetch_hash
		# password check
		return RMXOS::RESULT_FAIL if password != hash['password']
		# prepare yes/no action
		@current.type = Action::TYPE_GUILD_DISBAND
		@current.data = hash['guild_id'].to_i
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Invites a player to the guild.
	#  username - username of the player to be invited
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_guild_invite(username)
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		# player doesn't exist
		return RMXOS::RESULT_FAIL if hash['count'].to_i == 0
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		# not online
		return RMXOS::RESULT_FAIL if client == nil
		# not on the same map
		return RMXOS::RESULT_FAIL if client.player.map_id != @client.player.map_id
		# guild check
		check = RMXOS.server.sql.query("SELECT guild_id FROM user_data WHERE user_id = #{client.player.user_id}")
		hash = check.fetch_hash
		return RMXOS::RESULT_ALTFAIL if hash['guild_id'] != nil
		# prepare invitation
		client.action.current.type = Action::TYPE_GUILD_JOIN
		client.action.current.data = [@client.player.guildname, @client.player.username]
		# send invitation
		message = "#{RMXOS::Data::GuildInvitation.sub('GUILD') {@client.player.guildname}} #{RMXOS::Data::DoYouAccept}"
		client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Removes a player from the guild.
	#  username - username of the player to be removed
	#  password - guild password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_guild_remove(username, password)
		check = RMXOS.server.sql.query("SELECT password FROM guilds WHERE guildname = '#{RMXOS.fix_string(@client.player.guildname)}'")
		hash = check.fetch_hash
		# password check
		return RMXOS::RESULT_FAIL if password != hash['password']
		# prepare yes/no action
		check = RMXOS.server.sql.query("SELECT user_id FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		@current.type = Action::TYPE_GUILD_LEAVE
		@current.data = [@client.player.guildname, username, hash['user_id'].to_i]
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Leaves a guild.
	#  password - user password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_guild_leave(password)
		# password check
		check = RMXOS.server.sql.query("SELECT password FROM users WHERE user_id = #{@client.player.user_id}")
		hash = check.fetch_hash
		return RMXOS::RESULT_FAIL if password != hash['password']
		# prepare yes/no action
		@current.type = Action::TYPE_GUILD_LEAVE
		@current.data = [@client.player.guildname, @client.player.username, @client.player.user_id]
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Executes a guild password change.
	#----------------------------------------------------------------------
	def execute_guild_password_change
		# change password
		guild_id, newpass, guildname = @current.data
		RMXOS.server.sql.query("UPDATE guilds SET password = '#{newpass}' WHERE guild_id = #{guild_id}")
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{RMXOS::Data::PasswordChanged}")
		# log this action if action log is turned on
		if RMXOS.server.options.log_actions
			RMXOS.log(@client.player, 'Action', "guild password change: #{guild_id} (#{guildname})")
		end
	end
	#----------------------------------------------------------------------
	# Executes the disbanding of the guild.
	#----------------------------------------------------------------------
	def execute_guild_disband
		# get guild ID
		guild_id = @current.data
		# delete the guild
		RMXOS.server.sql.query("DELETE FROM guilds WHERE guild_id = #{guild_id}")
		# notify all guild members
		message = RMXOS::Data::GuildDisbanded.sub('GUILD') {@client.player.guildname}
		# notify online members
		offline_members = @client.player.guildmembers.clone
		@client.sender.get_guild_clients(true).each {|client|
			# notify all guild members that the guild has been disbanded
			client.send('GRM')
			client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
			client.player.reset_guild
			offline_members.delete(client.player.username)
		}
		# send PM to all offline members
		offline_members.each {|username| self.try_pm_send(username, message, RMXOS::Data::Server)}
	end
	#----------------------------------------------------------------------
	# Executes guild leadership transfer.
	#----------------------------------------------------------------------
	def execute_guild_transfer
		# new leader
		RMXOS.server.sql.query("UPDATE guilds SET leader_id = #{@client.player.user_id} WHERE guildname = '#{RMXOS.fix_string(@client.player.guildname)}'")
		# set new leader data
		@client.player.guildleader = @client.player.username
		# notify player
		leader_message = "GLE#{@client.player.username}"
		@client.send(leader_message)
		message = RMXOS::Data::GuildLeader.sub('GUILD') {@client.player.guildname}
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
		# notify all guild members
		message = RMXOS::Data::GuildLeaderPlayer.sub('GUILD') {@client.player.guildname}.sub('PLAYER') {@client.player.username}
		message = "CHT#{RMXOS::Data::ColorOK}\t0\t#{message}"
		@client.sender.get_guild_clients.each {|client|
			# notify all guild members of the new leader
			client.player.guildleader = @client.player.guildleader
			client.send(leader_message)
			client.send(message)
		}
	end
	#----------------------------------------------------------------------
	# Executes joining a guild.
	#----------------------------------------------------------------------
	def execute_guild_join
		guildname, leadername = @current.data
		# get guild data
		check = RMXOS.server.sql.query("SELECT guild_id FROM guilds WHERE guildname = '#{RMXOS.fix_string(guildname)}'")
		hash = check.fetch_hash
		guild_id = hash['guild_id'].to_i
		RMXOS.server.sql.query("UPDATE user_data SET guild_id = #{guild_id} WHERE user_id = #{@client.player.user_id}")
		# set all guild related data
		self.setup_guild_data(guild_id)
		# send guild data to player
		@client.send("GIN#{guildname}\t#{@client.player.guildleader}\t#{@client.player.get_guildmembers_list}")
		# notify player that he has joined
		message = RMXOS::Data::GuildJoined.sub('GUILD') {guildname}
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
		# notify players that this player has joined the guild
		message = RMXOS::Data::GuildJoinedPlayer.sub('PLAYER') {@client.player.username}
		@client.sender.get_guild_clients.each {|client|
			# send and set up all necessary data
			client.send("GJO#{@client.player.username}")
			client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
			client.player.guildmembers.push(RMXOS.fix_string(@client.player.username))
		}
	end
	#----------------------------------------------------------------------
	# Executes leaving the guild.
	#----------------------------------------------------------------------
	def execute_guild_leave
		guildname, username, user_id = @current.data
		# remove member from guild
		RMXOS.server.sql.query("UPDATE user_data SET guild_id = NULL WHERE user_id = #{user_id}")
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		# if client is online
		if client != nil
			client.send('GRM')
			# send message to player leaving guild
			message = RMXOS::Data::GuildRemoved.sub('GUILD') {guildname}
			client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
			# notify all guild members that this player is not a guild member anymore
			client.sender.send_to_guild("GRE#{username}")
			message = RMXOS::Data::GuildRemovedPlayer.sub('PLAYER') {username}.sub('GUILD') {guildname}
			client.sender.send_to_guild("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
			# reset all guild related data
			client.player.reset_guild
		else
			# leave a message in the player's inbox
			message = RMXOS::Data::GuildRemoved.sub('GUILD') {guildname}
			self.try_pm_send(username, message, RMXOS::Data::Server)
			# notify all guild members that this player is not a guild member anymore
			@client.sender.send_to_guild("GRE#{username}", true)
			message = RMXOS::Data::GuildRemovedPlayer.sub('PLAYER') {username}.sub('GUILD') {guildname}
			@client.sender.send_to_guild("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}", true)
		end
	end

end
