#======================================================================
# Action_Handler
#----------------------------------------------------------------------
# Handles extended actions.
#======================================================================

class Action_Handler
	
	#----------------------------------------------------------------------
	# Executes adding a buddy from the buddy list.
	#  username - username of the new buddy
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_buddy_add(username)
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		# player doesn't exist
		return RMXOS::RESULT_FAIL if hash['count'].to_i == 0
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		# not online
		return RMXOS::RESULT_ALTFAIL if client == nil
		# not on the same map
		return RMXOS::RESULT_ALTFAIL if client.player.map_id != @client.player.map_id
		# prepare invitation
		client.action.current.type = Action::TYPE_BUDDY_ADD
		client.action.current.data = [@client.player.username, @client.player.user_id]
		# send invitation
		message = "#{RMXOS::Data::BuddyAdd.sub('PLAYER') {@client.player.username}} #{RMXOS::Data::DoYouAccept}"
		client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Executes removing a buddy from the buddy list.
	#  username - username of the buddy to be removed
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_buddy_remove(username)
		# get user data
		check = RMXOS.server.sql.query("SELECT user_id FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		# prepare yes/no action
		@current.type = Action::TYPE_BUDDY_REMOVE
		@current.data = [username, hash['user_id'].to_i]
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Tries sending a PM to a user.
	#  username - user ID of the recipient
	#  message - the message
	#  sender - the username of the player sending the message
	# Returns: Whether the PM was successful or not.
	#----------------------------------------------------------------------
	def try_pm_send(username, message, sender = @client.player.username)
		check = RMXOS.server.sql.query("SELECT user_id FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		return RMXOS::RESULT_ALTFAIL if check.num_rows == 0
		# get user ID
		hash = check.fetch_hash
		user_id = hash['user_id'].to_i
		# check inbox
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM inbox WHERE recipient_id = #{user_id}")
		hash = check.fetch_hash
		# inbox is full
		if hash['count'].to_i >= INBOX_SIZE - 1
			# send message to player if he's online
			@client.sender.send_to_name(username, "CHT#{RMXOS::Data::ColorInfo}\t0\t#{RMXOS::Data::InboxFull}")
			return RMXOS::RESULT_ALTFAIL
		end
		# store the PM in the inbox
		RMXOS.server.sql.query("INSERT INTO inbox (recipient_id, message, sendername, senddate) VALUES (#{user_id}, '#{RMXOS.fix_string(message)}', '#{RMXOS.fix_string(sender)}', '#{RMXOS.get_sqltime(Time.now.getutc)}')")
		# notify player of new PM
		@client.sender.send_to_name(username, "CHT#{RMXOS::Data::ColorOK}\t0\t#{RMXOS::Data::NewPMs}")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Executes deletion of a PM.
	#  pm_id - ID of the PM to be deleted
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_pm_delete(pm_id)
		check = RMXOS.server.sql.query("SELECT unread FROM inbox WHERE recipient_id = #{@client.player.user_id} AND pm_id = #{pm_id}")
		# PM does not exist
		return RMXOS::RESULT_FAIL if check.num_rows == 0
		hash = check.fetch_hash
		# prepare yes/no action
		@current.type = Action::TYPE_PM_DELETE
		@current.data = pm_id
		# PM is unread
		return RMXOS::RESULT_ALTFAIL if hash['unread'] != '0'
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Executes deletion of all PMs.
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_pm_delete_all
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM inbox WHERE recipient_id = #{@client.player.user_id}")
		hash = check.fetch_hash
		# inbox already empty
		return RMXOS::RESULT_FAIL if hash['count'].to_i == 0
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM inbox WHERE recipient_id = #{@client.player.user_id} AND unread = 1")
		hash = check.fetch_hash
		# prepare yes/no action
		@current.type = Action::TYPE_PM_DELETE_ALL
		# inbox has unread PMs
		return RMXOS::RESULT_ALTFAIL if hash['count'].to_i > 0
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Executes requesting a trade with a player.
	#  username - username of the other player
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_trade_request(username)
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		# player doesn't exist
		return RMXOS::RESULT_FAIL if hash['count'].to_i == 0
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		# not online
		return RMXOS::RESULT_ALTFAIL if client == nil
		# not on the same map
		return RMXOS::RESULT_ALTFAIL if client.player.map_id != @client.player.map_id
		# prepare request
		client.action.current.type = Action::TYPE_TRADE_REQUEST
		client.action.current.data = [@client.player.username, @client.player.user_id]
		# send invitation
		message = "#{RMXOS::Data::TradeRequestPlayer.sub('PLAYER') {@client.player.username}} #{RMXOS::Data::DoYouAccept}"
		client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Executes adding a buddy from the buddy list.
	#----------------------------------------------------------------------
	def execute_buddy_add
		username, user_id = @current.data
		# add to buddy list
		RMXOS.server.sql.query("INSERT INTO buddy_list (user1_id, user2_id) VALUES (#{user_id}, #{@client.player.user_id})")
		# notify this player
		@client.send("BAD#{username}")
		message = RMXOS::Data::BuddyAddedPlayer.sub('PLAYER') {username}
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
		@client.player.buddies.push(username)
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		# if client is still online
		if client != nil
			# notify other player of new buddy
			client.send("BAD#{@client.player.username}")
			message = RMXOS::Data::BuddyAddedPlayer.sub('PLAYER') {@client.player.username}
			client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
			client.player.buddies.push(@client.player.username)
		end
	end
	#----------------------------------------------------------------------
	# Executes removing a buddy from the buddy list.
	#----------------------------------------------------------------------
	def execute_buddy_remove
		username, user_id = @current.data
		# delete from buddy list
		RMXOS.server.sql.query("DELETE FROM buddy_list WHERE user1_id = #{@client.player.user_id} AND user2_id = #{user_id} " + 
				"OR user1_id = #{user_id} AND user2_id = #{@client.player.user_id}")
		# notify this player
		@client.send("BRE#{username}")
		message = RMXOS::Data::BuddyRemovePlayer.sub('PLAYER') {username}
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
		@client.player.buddies.delete(username)
		# find the player if he's online
		client = @client.sender.get_client_by_name(username)
		# if client is still online
		if client != nil
			# notify other player that he lost a buddy
			client.send("BRE#{@client.player.username}")
			message = RMXOS::Data::BuddyRemovePlayer.sub('PLAYER') {@client.player.username}
			client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
			client.player.buddies.delete(@client.player.username)
		else
			self.try_pm_send(username, RMXOS::Data::BuddyRemovePlayer.sub('PLAYER') {@client.player.username}, RMXOS::Data::Server)
		end
	end
	#----------------------------------------------------------------------
	# Executes deletion of a PM.
	#----------------------------------------------------------------------
	def execute_pm_delete
		pm_id = @current.data
		RMXOS.server.sql.query("DELETE FROM inbox WHERE pm_id = #{pm_id}")
		message = RMXOS::Data::PMDeleted.sub('MESSAGEID') {pm_id.to_s}
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{message}")
	end
	#----------------------------------------------------------------------
	# Executes deletion of all PMs.
	#----------------------------------------------------------------------
	def execute_pm_delete_all
		RMXOS.server.sql.query("DELETE FROM inbox WHERE recipient_id = #{@client.player.user_id}")
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{RMXOS::Data::PMDeletedAll}")
	end
	#----------------------------------------------------------------------
	# Executes a trade request to start the trade.
	#----------------------------------------------------------------------
	def execute_trade_request
		username, user_id = @current.data
		# notify this player to begin the trade
		@client.send("TRS0\t#{user_id}")
		# notify other player to begin the trade, other player is the host
		@client.sender.send_to_id(user_id, "TRS1\t#{@client.player.user_id}")
	end

end
