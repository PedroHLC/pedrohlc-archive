#======================================================================
# Action_Handler
#----------------------------------------------------------------------
# Handles administrative actions.
#======================================================================

class Action_Handler
	
	#----------------------------------------------------------------------
	# Prepares the change another player's password.
	#  username - username of the other player
	#  newpass - new encrypted password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_forced_password_change(username, newpass)
		check = RMXOS.server.sql.query("SELECT user_id FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		# player does not exist
		return RMXOS::RESULT_FAIL if check.num_rows == 0
		# prepare yes/no action
		hash = check.fetch_hash
		@current.type = Action::TYPE_PASSWORD_CHANGE
		@current.data = [hash['user_id'].to_i, newpass, username]
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Prepares the change a guild's password.
	#  guildname - name of the guild
	#  newpass - new encrypted password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_forced_guild_password_change(guildname, newpass)
		check = RMXOS.server.sql.query("SELECT guild_id FROM guilds WHERE guildname = '#{RMXOS.fix_string(guildname)}'")
		# guild does not exist
		return RMXOS::RESULT_FAIL if check.num_rows == 0
		# prepare yes/no action
		hash = check.fetch_hash
		@current.type = Action::TYPE_GUILD_PASSWORD_CHANGE
		@current.data = [hash['guild_id'].to_i, newpass, guildname]
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Changes a player's group.
	#  username - username of the player with the new usergroup
	#  group - new usergroup
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_group_change(username, group)
		check = RMXOS.server.sql.query("SELECT usergroup FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		# user does not exist
		return RMXOS::RESULT_FAIL if check.num_rows == 0
		hash = check.fetch_hash
		# permission group needs to be higher
		return RMXOS::RESULT_DENIED if @client.player.usergroup <= hash['usergroup'].to_i
		# ban the player
		RMXOS.server.sql.query("UPDATE users SET usergroup = #{group} WHERE username = '#{RMXOS.fix_string(username)}'")
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		if client != nil
			# change player's usergroup
			client.player.usergroup = group
			# send new usergroup to player himself
			client.send("UGR#{client.player.usergroup}")
		end
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Kicks a player.
	#  username - username of the player to be kicked
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_kick(username)
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		if client != nil
			# permission group needs to be higher
			return RMXOS::RESULT_DENIED if @client.player.usergroup <= client.player.usergroup
			# kick the player
			client.action.execute_kick
			return RMXOS::RESULT_SUCCESS
		end
		return RMXOS::RESULT_FAIL
	end
	#----------------------------------------------------------------------
	# Bans a player.
	#  username - username of the player to be banned
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_ban(username)
		check = RMXOS.server.sql.query("SELECT user_id, usergroup FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		# user does not exist
		return RMXOS::RESULT_FAIL if check.num_rows == 0
		hash = check.fetch_hash
		# permission group needs to be higher
		return RMXOS::RESULT_DENIED if @client.player.usergroup <= hash['usergroup'].to_i
		# ban the player
		RMXOS.server.sql.query("UPDATE users SET banned = 1 WHERE user_id = '#{hash['user_id']}'")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Unbans a player.
	#  username - username of the player to be unbanned
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_unban(username)
		check = RMXOS.server.sql.query("SELECT user_id, usergroup FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		# user does not exist
		return RMXOS::RESULT_FAIL if check.num_rows == 0
		hash = check.fetch_hash
		# permission group needs to be higher
		return RMXOS::RESULT_DENIED if @client.player.usergroup <= hash['usergroup'].to_i
		# ban the player
		RMXOS.server.sql.query("UPDATE users SET banned = 0 WHERE user_id = '#{hash['user_id']}'")
		return RMXOS::RESULT_SUCCESS
	end

end
