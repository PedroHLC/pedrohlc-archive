#======================================================================
# Action_Handler
#----------------------------------------------------------------------
# Handles all basic actions.
#======================================================================

class Action_Handler
	
	# setting all accessible variables
	attr_reader   :current
	
	#----------------------------------------------------------------------
	# Initialization.
	#----------------------------------------------------------------------
	def initialize(client)
		@client = client
		@current = Action.new
	end
	#----------------------------------------------------------------------
	# Tries to register this client.
	#  username - username
	#  password - password's hash value
	# Returns: Success result of the register try.
	#----------------------------------------------------------------------
	def try_register(username, password)
		# try to find user
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		# user already exists
		return RMXOS::RESULT_FAIL if hash['count'].to_i > 0
		# get user count
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM users")
		hash = check.fetch_hash
		RMXOS.server.sql.query("START TRANSACTION")
		# first registered user becomes admin
		group = (hash['count'].to_i == 0 ? RMXOS::GROUP_ADMIN : RMXOS::GROUP_PLAYER)
		# register new user
		RMXOS.server.sql.query("INSERT INTO users (username, password, usergroup) VALUES ('#{RMXOS.fix_string(username)}', '#{password}', #{group})")
		# get new user ID
		check = RMXOS.server.sql.query("SELECT user_id FROM users WHERE username = '#{RMXOS.fix_string(username)}'")
		hash = check.fetch_hash
		user_id = hash['user_id'].to_i
		RMXOS.server.sql.query("INSERT INTO user_data (user_id, lastlogin) VALUES (#{user_id}, '#{RMXOS.get_sqltime(Time.now.getutc)}')")
		# get client's IP address
		ip = @client.socket.peeraddr[3]
		# record IP
		RMXOS.server.sql.query("REPLACE INTO ips(user_id, ip) VALUES (#{user_id}, '#{ip}')")
		RMXOS.server.sql.query("COMMIT")
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Tries to log in this client.
	#  username - username
	#  password - password's hash value
	# Returns: Success result.
	#----------------------------------------------------------------------
	def try_login(username, password)
		# find this user
		check = RMXOS.server.sql.query("SELECT user_id, usergroup, banned FROM users WHERE username = " +
			"'#{RMXOS.fix_string(username)}' AND password = '#{password}'")
		# either username or password is incorrect
		return RMXOS::RESULT_FAIL if check.num_rows == 0
		hash = check.fetch_hash
		# this user is banned
		return RMXOS::RESULT_DENIED if hash['banned'] != '0'
		user_id = hash['user_id'].to_i
		# get client's IP address
		ip = @client.socket.peeraddr[3]
		# if using IP banning
		if USE_IP_BANNING
			# match against recorded IPs
			check = RMXOS.server.sql.query("SELECT DISTINCT users.user_id FROM users JOIN ips ON users.user_id = ips.user_id " +
				"WHERE banned = 1 AND ips.ip = '#{ip}'")
			# IP matches with IP of a banned user
			return RMXOS::RESULT_DENIED if check.num_rows > 0
		end
		# this user is already logged in
		return RMXOS::RESULT_ALTFAIL if $clients.any? {|client| client.player.user_id == user_id}
		# get user main data
		@client.player.user_id = user_id
		@client.player.username = username
		@client.player.usergroup = hash['usergroup'].to_i
		# log last login time
		RMXOS.server.sql.query("UPDATE user_data SET lastlogin = '#{RMXOS.get_sqltime(Time.now.getutc)}' WHERE user_id = #{@client.player.user_id}")
		# record IP
		RMXOS.server.sql.query("REPLACE INTO ips(user_id, ip) VALUES (#{user_id}, '#{ip}')")
		# find all buddies
		self.setup_buddies
		# get other user data
		check = RMXOS.server.sql.query("SELECT guild_id FROM user_data WHERE user_id = #{user_id}")
		hash = check.fetch_hash
		# set all guild related data if player is in a guild
		self.setup_guild_data(hash['guild_id'].to_i) if hash['guild_id'] != nil
		# notify if new PMs in the inbox
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM inbox WHERE recipient_id = #{@client.player.user_id} AND unread = 1")
		hash = check.fetch_hash
		@client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{RMXOS::Data::NewPMs}") if hash['count'].to_i > 0
		# notify if inbox is full
		check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM inbox WHERE recipient_id = #{@client.player.user_id}")
		hash = check.fetch_hash
		if hash['count'].to_i >= INBOX_SIZE
			@client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{RMXOS::Data::InboxFull}")
		end
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Changes the user password.
	#  oldpass - old encrypted password
	#  newpass - new encrypted password
	# Returns: Action result of this action.
	#----------------------------------------------------------------------
	def try_password_change(oldpass, newpass)
		check = RMXOS.server.sql.query("SELECT password FROM users WHERE user_id = #{@client.player.user_id}")
		hash = check.fetch_hash
		# password check
		return RMXOS::RESULT_FAIL if oldpass != hash['password']
		# prepare yes/no action
		@current.type = Action::TYPE_PASSWORD_CHANGE
		@current.data = [@client.player.user_id, newpass, @client.player.username]
		return RMXOS::RESULT_SUCCESS
	end
	#----------------------------------------------------------------------
	# Executes YES on the last action.
	#----------------------------------------------------------------------
	def execute_yes
		# check action type
		case @current.type
		when Action::TYPE_PASSWORD_CHANGE then self.execute_password_change
		when Action::TYPE_GUILD_PASSWORD_CHANGE then self.execute_guild_password_change
		when Action::TYPE_GUILD_DISBAND then self.execute_guild_disband
		when Action::TYPE_GUILD_TRANSFER then self.execute_guild_transfer
		when Action::TYPE_GUILD_JOIN then self.execute_guild_join
		when Action::TYPE_GUILD_LEAVE then self.execute_guild_leave
		when Action::TYPE_TRADE_REQUEST then self.execute_trade_request
		when Action::TYPE_BUDDY_ADD then self.execute_buddy_add
		when Action::TYPE_BUDDY_REMOVE then self.execute_buddy_remove
		when Action::TYPE_PM_DELETE then self.execute_pm_delete
		when Action::TYPE_PM_DELETE_ALL then self.execute_pm_delete_all
		else
			# no request message
			@client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{RMXOS::Data::NoRequest}")
		end
		# clear current
		@current.clear
	end
	#----------------------------------------------------------------------
	# Executes NO on the last action.
	#----------------------------------------------------------------------
	def execute_no
		name = nil
		# check action type
		case @current.type
		when Action::TYPE_PASSWORD_CHANGE, Action::TYPE_GUILD_PASSWORD_CHANGE
			# player confirmation message
			message1 = RMXOS::Data::PasswordNoChange
		when Action::TYPE_GUILD_DISBAND
			# player confirmation message
			message1 = RMXOS::Data::GuildNoDisband.sub('GUILD') {@client.player.guildname}
		when Action::TYPE_GUILD_TRANSFER
			# player confirmation message
			message1 = RMXOS::Data::GuildNoTransfer
			# answer to requester
			message2 = RMXOS::Data::GuildNoTransferPlayer.sub('PLAYER') {@client.player.username}
			name = @client.player.guildleader
		when Action::TYPE_GUILD_JOIN
			# player confirmation message
			message1 = RMXOS::Data::GuildNoJoin
			# answer to requester
			message2 = RMXOS::Data::GuildNoJoinPlayer.sub('PLAYER') {@client.player.username}
			name = @current.data[1]
		when Action::TYPE_GUILD_LEAVE
			if @current.data[1] == @client.player.username
				# player confirmation message
				message1 = RMXOS::Data::GuildNoLeave.sub('GUILD') {@client.player.guildname}
			else
				# confirmation message for no removal from guild
				message1 = RMXOS::Data::GuildNoRemove.sub('PLAYER') {@current.data[1]}
			end
		when Action::TYPE_TRADE_REQUEST
			# player confirmation message
			message1 = RMXOS::Data::TradeNoRequest
			# answer to requester
			message2 = RMXOS::Data::TradeNoRequestPlayer.sub('PLAYER') {@client.player.username}
			name = @current.data[0]
		when Action::TYPE_BUDDY_ADD
			# player confirmation message
			message1 = RMXOS::Data::BuddyNoAdd
			# answer to requester
			message2 = RMXOS::Data::BuddyNoAddPlayer.sub('PLAYER') {@client.player.username}
			name = @current.data[0]
		when Action::TYPE_BUDDY_REMOVE
			# player confirmation message
			message1 = RMXOS::Data::BuddyNoRemovePlayer.sub('PLAYER') {@current.data[0]}
		when Action::TYPE_PM_DELETE, Action::TYPE_PM_DELETE_ALL
			# player confirmation message
			message1 = RMXOS::Data::PMNoDeletion
		else
			# no request message
			message1 = RMXOS::Data::NoRequest
		end
		# send player confirmation message
		@client.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message1}")
		# send answer to requester if requester exists
		@client.sender.send_to_name(name, "CHT#{RMXOS::Data::ColorInfo}\t0\t#{message2}") if name != nil
		# clear action
		@current.clear
	end
	#----------------------------------------------------------------------
	# Executes a password change.
	#----------------------------------------------------------------------
	def execute_password_change
		# change password
		user_id, newpass, username = @current.data
		RMXOS.server.sql.query("UPDATE users SET password = '#{newpass}' WHERE user_id = #{user_id}")
		@client.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{RMXOS::Data::PasswordChanged}")
		# log this action if action log is turned on
		if RMXOS.server.options.log_actions
			RMXOS.log(@client.player, 'Action', "user password change: #{user_id} (#{username})")
		end
	end
	#----------------------------------------------------------------------
	# Broadcasts disconnection of this client by kicking.
	#----------------------------------------------------------------------
	def execute_kick
		@client.send('KCK')
		@client.terminate
		$clients.delete(@client)
	end
	#----------------------------------------------------------------------
	# Sets up buddies.
	#----------------------------------------------------------------------
	def setup_buddies
		@client.player.buddies = []
		# get all buddy IDs
		check = RMXOS.server.sql.query("SELECT * FROM buddy_list WHERE user1_id = #{@client.player.user_id} OR user2_id = #{@client.player.user_id}")
		check.num_rows.times {
			hash = check.fetch_hash
			if hash['user1_id'].to_i == @client.player.user_id
				@client.player.buddies.push(hash['user2_id'].to_i)
			else
				@client.player.buddies.push(hash['user1_id'].to_i)
			end
		}
		# convert buddy IDs
		@client.player.buddies.each_index {|i|
			check = RMXOS.server.sql.query("SELECT username FROM users WHERE user_id = #{@client.player.buddies[i]}")
			hash = check.fetch_hash
			@client.player.buddies[i] = hash['username']
		}
	end
	#----------------------------------------------------------------------
	# Sets up all guild related data.
	#  guild_id - ID of the guild
	#----------------------------------------------------------------------
	def setup_guild_data(guild_id)
		# get guild data
		check = RMXOS.server.sql.query("SELECT guildname, leader_id FROM guilds WHERE guild_id = #{guild_id}")
		hash = check.fetch_hash
		@client.player.guildname = hash['guildname']
		# get guild leader name
		if hash['leader_id'].to_i != @client.player.user_id
			check = RMXOS.server.sql.query("SELECT username FROM users WHERE user_id = #{hash['leader_id']}")
			hash = check.fetch_hash
			@client.player.guildleader = hash['username']
		else
			# this player is the guild leader
			@client.player.guildleader = @client.player.username
		end
		# get guild member count
		check = RMXOS.server.sql.query("SELECT username FROM users JOIN user_data ON users.user_id = " +
			"user_data.user_id WHERE guild_id = #{guild_id}")
		@client.player.guildmembers = []
		check.num_rows.times {
			hash = check.fetch_hash
			@client.player.guildmembers.push(hash['username'])
		}
	end
	#----------------------------------------------------------------------
	# Checks if this client has trades enabled.
	#  user_id - user ID of the other client
	# Returns: True or False.
	#----------------------------------------------------------------------
	def can_trade?(user_id)
		check = RMXOS.server.sql.query("SELECT notrade FROM user_data WHERE user_id = #{user_id}")
		# user does not exist, can't trade
		return false if check.num_rows == 0
		hash = check.fetch_hash
		return (hash['notrade'] == '0')
	end

end
