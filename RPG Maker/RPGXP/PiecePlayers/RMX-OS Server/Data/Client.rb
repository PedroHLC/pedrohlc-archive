#======================================================================
# Client
#----------------------------------------------------------------------
# Serves as server side connection for clients.
#======================================================================

class Client
	
	# setting all accessible variables
	attr_accessor :message
	attr_accessor :login_timeout
	attr_reader   :socket
	attr_reader   :sender
	attr_reader   :action
	attr_reader   :player
	attr_reader   :saving_queries
	
	#----------------------------------------------------------------------
	# Initialization.
	#----------------------------------------------------------------------
	def initialize(socket)
		# received message
		@message = ''
		# socket connection
		@socket = socket
		# utility classes
		@sender = Sender.new(self)
		@action = Action_Handler.new(self)
		@player = Player.new(self)
		# login timeout
		@login_timeout = LOGIN_TIMEOUT
		# saving queries since the saving is executed as one transaction for consistency
		@saving_queries = ['START TRANSACTION']
	end
	#----------------------------------------------------------------------
	# Handles received messages for this client.
	#  message - received message
	#----------------------------------------------------------------------
	def handle(message)
		@message = message
		# update all loaded extensions with this client if they are active
		abort = false
		RMXOS.extensions.each_value {|extension| abort |= extension.client_update(self)}
		return if abort
		# default message handle
		return if self.check_game
		return if self.check_connection
		return if self.check_admin_commands
		return if self.check_mod_commands
		return if self.check_normal_commands
		return if self.check_buddy_commands
		return if self.check_pm_commands
		return if self.check_trade_commands
		return if self.check_guild_commands
		return if self.check_saving
		return if self.check_loading
	end
	#----------------------------------------------------------------------
	# Checks messages related to ingame procedures.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_game
		case @message
		when /\APNG\Z/ # client ping
			return true
		when /\ADCT\Z/ # disconnect
			self.terminate
			return true
		when /\ACHT(.+)/ # chat entry
			@sender.send_to_map(@message, true)
			return true
		when /\ACHA(.+)/ # action chat entry
			@sender.send_to_map(@message, true)
			return true
		when /\AENT\Z/ # enter server
			# broadcast to everybody that a new player has entered the server
			@sender.send_to_all("MEN#{@player.user_id},0")
			return true
		when /\AMEN(.+)/ # enter map
			# get new map ID
			@player.map_id = $1.to_i
			exchange_variables = "MEV#{@player.get_current_data}"
			map_entry = "MEN#{@player.user_id}\t#{@player.map_id}"
			# to all clients on the same map
			@sender.get_map_clients.each {|client|
				# send exchange variables
				client.send(exchange_variables)
				# send map entry message
				client.send(map_entry)
				# send their data to current client
				self.send("MEV#{client.player.get_current_data}")
				# send their map data to current client
				self.send("MEN#{client.player.user_id}\t#{client.player.map_id}")
			}
			return true
		when /\AMEX\Z/ # exit map
			# broadcast map leaving to everybody on the same map
			@sender.send_to_map("MEX\t#{@player.user_id}")
			# map currently unassigned
			@player.map_id = 0
			return true
		when /\AMEV(.+)/ # exchange variables for players
			variables = eval($1)
			# store the exchange variables
			@player.evaluate(variables)
			# send the new data to everybody on the same map if being on an actual map
			@sender.send_to_map("MEV#{@player.get_player_data}\t#{variables.inspect}") if @player.map_id != 0
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks connection related messages.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_connection
		case @message
		when /\ALIN(.+)\t(.+)/ # login request
			result = @action.try_login($1, $2)
			# if login was successful
			if result == RMXOS::RESULT_SUCCESS
				# send user data
				self.send("UID#{@player.user_id}")
				self.send("USR#{@player.username}")
				self.send("UGR#{@player.usergroup}")
				self.send("BUD#{@player.get_buddies_list}")
				# send guild data
				if @player.guildname != ''
					self.send("GIN#{@player.guildname}\t#{@player.guildleader}\t#{@player.get_guildmembers_list}")
				end
			end
			self.send("LIN#{result}")
			return true
		when /\AREG(.+)\t(.+)/ # register request
			result = @action.try_register($1, $2)
			# if registering was successful
			if result == RMXOS::RESULT_SUCCESS
				# log in as well
				@action.try_login($1, $2)
				# send user data
				self.send("UID#{@player.user_id}")
				self.send("USR#{@player.username}")
				self.send("UGR#{@player.usergroup}")
				self.send("BUD#{@player.get_buddies_list}")
				# send guild data
				if @player.guildname != ''
					self.send("GIN#{@player.guildname}\t#{@player.guildleader}\t#{@player.get_guildmembers_list}")
				end
			end
			self.send("REG#{result}")
			return true
		when /\ACON(.+)/ # connection request
			version = $1.to_f
			# get all properly connected clients
			clients = $clients.find_all {|client| client.player.user_id != 0}
			# version not high enough
			if version < RMXOS_VERSION
				result = RMXOS::RESULT_FAIL
			# server is full
			elsif (clients - [self]).size >= MAXIMUM_CONNECTIONS
				result = RMXOS::RESULT_DENIED
			else
				result = RMXOS::RESULT_SUCCESS
			end
			self.send("CON#{result}\t#{RMXOS_VERSION}")
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for transmitted admin chat commands.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_admin_commands
		case @message
		when /\AAKA\Z/ # kick all
			# check permissions additionally
			if @player.usergroup >= RMXOS::GROUP_2NDADMIN
				# execute kick
				($clients - [self]).each {|client| client.action.execute_kick}
				message = RMXOS::Data::Kickall
				color = RMXOS::Data::ColorOK
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', 'kick all') if RMXOS.server.options.log_actions
			else
				message = RMXOS::Data::ActionDenied2.sub('ACTION') {'kick all'}
				color = RMXOS::Data::ColorError
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', 'DENIED kick all') if RMXOS.server.options.log_actions
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AAPA(.+)\t(.+)/ # change player password
			username, newpass = $1, $2
			# prepare everything for password change
			if @player.usergroup >= RMXOS::GROUP_2NDADMIN
				result = @action.try_forced_password_change(username, newpass)
			else
				result = RMXOS::RESULT_DENIED
			end
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::PasswordForcing.sub('ENTITY') {username}} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "password change #{username}") if RMXOS.server.options.log_actions
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotExist.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_DENIED
				message = RMXOS::Data::ActionDenied.sub('PLAYER') {username}.sub('ACTION') {'change password of'}
				color = RMXOS::Data::ColorError
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED password change #{username}") if RMXOS.server.options.log_actions
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AAGP(.+)\t(.+)/ # change guild password
			guildname, newpass = $1, $2
			# prepare everything for password change
			if @player.usergroup >= RMXOS::GROUP_2NDADMIN
				result = @action.try_forced_guild_password_change(guildname, newpass)
			else
				result = RMXOS::RESULT_DENIED
			end
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::PasswordForcing.sub('ENTITY') {guildname}} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "password change #{guildname}") if RMXOS.server.options.log_actions
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::GuildNotExist.sub('GUILD') {guildname}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_DENIED
				message = RMXOS::Data::ActionDenied.sub('PLAYER') {guildname}.sub('ACTION') {'change password of'}
				color = RMXOS::Data::ColorError
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED password change #{guildname}") if RMXOS.server.options.log_actions
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGRC(.+)\t(.+)/ # change player usergroup
			username, group = $1, $2.to_i
			# if own usergroup superior to the new group of the other user
			if @player.usergroup > group
				result = @action.try_group_change(username, group)
			else
				result = RMXOS::RESULT_DENIED
			end
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::GroupChangeSuccess.sub('PLAYER') {username}
				color = RMXOS::Data::ColorOK
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "change usergroup: #{username}") if RMXOS.server.options.log_actions
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotExist.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_DENIED
				message = RMXOS::Data::ActionDenied.sub('PLAYER') {username}.sub('ACTION') {'change usergroup of'}
				color = RMXOS::Data::ColorError
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED change usergroup: #{username}") if RMXOS.server.options.log_actions
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AAEV(.+)/ # global script evaluation
			# check permission group first
			if @player.usergroup >= RMXOS::GROUP_2NDADMIN
				@sender.send_to_all("EVA#{$1}")
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "global eval: #{$1}") if RMXOS.server.options.log_actions
			else
				self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{RMXOS::Data::ActionDenied2.sub('ACTION') {'global eval'}}")
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED global eval: #{$1}") if RMXOS.server.options.log_actions
			end
			return true
		when /\AASE(.+)/ # server script evaluation
			script = $1
			# check permission group first
			if @player.usergroup >= RMXOS::GROUP_2NDADMIN
				begin
					eval(script)
					self.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{RMXOS::Data::ScriptExecuted}")
					# log this action if action log is turned on
					RMXOS.log(@player, 'Action', "server eval: #{script}") if RMXOS.server.options.log_actions
				rescue SyntaxError
					self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{RMXOS::Data::InvalidSyntax}")
				rescue
					self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{$!.message}")
				end
			else
				self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{RMXOS::Data::ActionDenied2.sub('ACTION') {'server eval'}}")
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED server eval: #{$1}") if RMXOS.server.options.log_actions
			end
			return true
		when /\AASQ(.+)/ # SQL script evaluation
			script = $1
			# check permission group first
			if @player.usergroup >= RMXOS::GROUP_2NDADMIN
				begin
					RMXOS.server.sql.query(script)
					self.send("CHT#{RMXOS::Data::ColorOK}\t0\t#{RMXOS::Data::ScriptExecuted}")
					# log this action if action log is turned on
					RMXOS.log(@player, 'Action', "server SQL: #{script}") if RMXOS.server.options.log_actions
				rescue
					self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{$!.message}")
				end
			else
				self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{RMXOS::Data::ActionDenied2.sub('ACTION') {'server SQL'}}")
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED server SQL: #{$1}") if RMXOS.server.options.log_actions
			end
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for transmitted mod chat commands.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_mod_commands
		case @message
		when /\AMKI(.+)/ # kick player
			username = $1
			# try to kick the player
			if @player.usergroup >= RMXOS::GROUP_MOD
				result = @action.try_kick(username)
			else
				result = RMXOS::RESULT_DENIED
			end
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::ActionSuccess.sub('PLAYER') {username}.sub('ACTION') {'kicked'}
				color = RMXOS::Data::ColorOK
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "kick: #{username}") if RMXOS.server.options.log_actions
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotOnline.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_DENIED
				message = RMXOS::Data::ActionDenied.sub('PLAYER') {username}.sub('ACTION') {'kick'}
				color = RMXOS::Data::ColorError
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED kick: #{username}") if RMXOS.server.options.log_actions
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AMBA(.+)/ # ban player
			username = $1
			# try to ban the player
			if @player.usergroup >= RMXOS::GROUP_MOD
				result = @action.try_ban(username)
			else
				result = RMXOS::RESULT_DENIED
			end
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::ActionSuccess.sub('PLAYER') {username}.sub('ACTION') {'banned'}
				color = RMXOS::Data::ColorOK
				# kick the player if he's online
				@action.try_kick(username)
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "ban: #{username}") if RMXOS.server.options.log_actions
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotExist.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_DENIED
				message = RMXOS::Data::ActionDenied.sub('PLAYER') {username}.sub('ACTION') {'ban'}
				color = RMXOS::Data::ColorError
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED ban: #{username}") if RMXOS.server.options.log_actions
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AMUB(.+)/ # unban player
			username = $1
			# try to unban the player
			if @player.usergroup >= RMXOS::GROUP_MOD
				result = @action.try_unban(username)
			else
				result = RMXOS::RESULT_DENIED
			end
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::ActionSuccess.sub('PLAYER') {username}.sub('ACTION') {'unbanned'}
				color = RMXOS::Data::ColorOK
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "unban: #{username}") if RMXOS.server.options.log_actions
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotExist.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_DENIED
				message = RMXOS::Data::ActionDenied.sub('PLAYER') {username}.sub('ACTION') {'unban'}
				color = RMXOS::Data::ColorError
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED unban: #{username}") if RMXOS.server.options.log_actions
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AMGM(.+)/ # global chat entry
			# check permission group first
			if @player.usergroup >= RMXOS::GROUP_MOD
				@sender.send_to_all("CHT#{$1}", true)
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "global message: #{$1}") if RMXOS.server.options.log_actions
			else
				message = RMXOS::Data::ActionDenied2.sub('ACTION') {'global message'}
				color = RMXOS::Data::ColorError
				self.send("CHT#{color}\t0\t#{message}")
				# log this action if action log is turned on
				RMXOS.log(@player, 'Action', "DENIED global message: #{$1}") if RMXOS.server.options.log_actions
			end
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for transmitted normal chat commands.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_normal_commands
		case @message
		when /\AWCH(.+)\t(.{3})\t(.+)\t(.+)/ # whisper chat
			username, color, id, message = $1, $2, $3, $4
			message = "CHT#{color}\t#{id}\t#{message}"
			if @sender.send_to_name(username, message)
				self.send(message) if username != @player.username
			else
				self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{RMXOS::Data::PlayerNotOnline.sub('PLAYER') {username}}")
			end
			return true
		when /\ANPS(.+)\t(.+)/ # new password with confirmation by using the old one
			oldpass, newpass = $1, $2
			# try to change the password
			result = @action.try_password_change(oldpass, newpass)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::PasswordChanging} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PasswordIncorrect
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\ATRQ(.+)/ # trade request
			username = $1
			# try to request a trade with a player
			result = @action.try_trade_request(username)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::TradeRequestedPlayer.sub('PLAYER') {username}
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotExist.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_ALTFAIL
				message = RMXOS::Data::PlayerNotOnMap.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AYES\Z/ # answered YES
			@action.execute_yes
			return true
		when /\ANOO\Z/ # answered NO
			@action.execute_no
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for transmitted pm chat commands.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_buddy_commands
		case @message
		when /\ABAD(.+)/ # adding to buddy list
			username = $1
			# try to add the player to the buddy list
			result = @action.try_buddy_add(username)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::BuddyAddingPlayer.sub('PLAYER') {username}
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotExist.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_ALTFAIL
				message = RMXOS::Data::PlayerNotOnMap.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\ABRE(.+)/ # removing from buddy list
			username = $1
			# try to remove the player from the buddy list
			@action.try_buddy_remove(username)
			# send message
			message = "#{RMXOS::Data::BuddyRemovingPlayer.sub('PLAYER') {username}} #{RMXOS::Data::AreYouSure}"
			self.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for transmitted pm chat commands.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_pm_commands
		case @message
		when /\APMM(.+)\t(.+)/ # send PM
			username, message = $1, $2
			# try to delete all PMs
			result = @action.try_pm_send(username, message)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::PMSent.sub('PLAYER') {username}
				color = RMXOS::Data::ColorOK
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotExist.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_ALTFAIL
				message = RMXOS::Data::InboxFullPlayer.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\APM(U|A)\Z/ # unread PMs, all PMs
			if $1 == 'U'
				check = RMXOS.server.sql.query("SELECT pm_id, sendername, senddate FROM inbox WHERE recipient_id = #{@player.user_id} AND unread = 1")
			else
				check = RMXOS.server.sql.query("SELECT pm_id, sendername, senddate FROM inbox WHERE recipient_id = #{@player.user_id}")
			end
			pms = []
			check.num_rows.times {
				hash = check.fetch_hash
				pms.push("#{hash['pm_id']},'#{RMXOS.fix_string(hash['sendername'])}',#{RMXOS.get_rubytime(hash['senddate'])}")
			}
			self.send("PMA#{pms.join(',')}")
			return true
		when /\APMO(.+)/ # open PM
			pm_id = $1.to_i
			check = RMXOS.server.sql.query("SELECT sendername, senddate, message FROM inbox WHERE recipient_id = #{@player.user_id} AND pm_id = #{pm_id}")
			if check.num_rows == 0
				self.send("CHT#{RMXOS::Data::ColorError}\t0\t#{RMXOS::Data::PMNotExist}")
				return true
			end
			hash = check.fetch_hash
			RMXOS.server.sql.query("UPDATE inbox SET unread = 0 WHERE pm_id = #{pm_id}")
			self.send("PMO#{hash['sendername']}\t#{RMXOS.get_rubytime(hash['senddate'])}\t#{hash['message']}")
			return true
		when /\APMD(.+)/ # delete PM
			pm_id = $1.to_i
			# try to delete that PM
			result = @action.try_pm_delete(pm_id)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::PMDeleting.sub('MESSAGEID') {pm_id.to_s}} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PMNotExist.sub('MESSAGEID') {pm_id.to_s}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_ALTFAIL # just a warning that the PM is unread
				message = "#{RMXOS::Data::PMDeletingUnread.sub('MESSAGEID') {pm_id.to_s}} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\APMC\Z/ # delete all PMs
			# try to delete all PMs
			result = @action.try_pm_delete_all
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::PMDeletingAll} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::InboxEmpty.sub('MESSAGEID') {pm_id.to_s}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_ALTFAIL # just a warning that there are unread PMs
				message = "#{RMXOS::Data::PMDeletingUnreadAll} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\APMS\Z/ # inbox status
			check = RMXOS.server.sql.query("SELECT COUNT(*) AS count FROM inbox WHERE recipient_id = #{@player.user_id}")
			hash = check.fetch_hash
			message = RMXOS::Data::InboxStatus.sub('STATUS') {"#{hash['count']}/#{INBOX_SIZE}"}
			self.send("CHT#{RMXOS::Data::ColorInfo}\t0\t#{message}")
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for transmitted trade commands.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_trade_commands
		case @message
		when /\ATCO(.+)/ # trade confirm
			user_id = $1.to_i
			# abort if trade confirm message could not be delivered
			self.send('TCA') if !@sender.send_to_id(user_id, 'TCO')
			return true
		when /\ATCA(.+)/ # trade complete abort
			user_id = $1.to_i
			@sender.send_to_id(user_id, 'TCA')
			return true
		when /\ATRI(.+)\t(.+)/ # trade items
			user_id, data = $1.to_i, $2
			# abort if trade items message could not be delivered
			self.send('TCA') if !@sender.send_to_id(user_id, "TRI#{data}")
			return true
		when /\ATRC(.+)/ # trade cancel
			user_id = $1.to_i
			# abort if trade cancel message could not be delivered
			self.send('TCA') if !@sender.send_to_id(user_id, 'TRC')
			return true
		when /\ATCC(.+)/ # trade confirm cancel
			user_id = $1.to_i
			# abort if trade confirm cancel message could not be delivered
			self.send('TCA') if !@sender.send_to_id(user_id, 'TCC')
			return true
		when /\ATRX(.+)/ # trade execute
			user_id = $1.to_i
			client = @sender.get_client_by_id(user_id)
			# if client exists
			if client != nil
				# if other client isn't done with the saving queries yet
				if !client.saving_queries.include?(nil)
					# mark as done
					@saving_queries.push(nil)
				else
					# get the saving queries from the other client
					@saving_queries += client.saving_queries
					@saving_queries.delete(nil)
					# clear other player's queries
					client.saving_queries.clear
					client.saving_queries.push('START TRANSACTION')
					# execute all saving queries
					@saving_queries.push('COMMIT')
					@saving_queries.each {|query| RMXOS.server.sql.query(query)}
					@saving_queries = ['START TRANSACTION']
					# finalize trade
					client.send('TRF')
					self.send('TRF')
				end
			else
				# something went wrong, abort trade
				@saving_queries = ['START TRANSACTION']
				self.send('TCA')
			end
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for transmitted guild chat commands.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_guild_commands
		case @message
		when /\AGCR(.+)\t(.+)/ # guild creation
			guildname, password = $1, $2
			# try to create a guild
			result = @action.try_guild_create(guildname, password)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::GuildCreateSuccess.sub('GUILD') {guildname}
				color = RMXOS::Data::ColorOK
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::GuildCreateFail.sub('GUILD') {guildname}
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGPS(.+)\t(.+)/ # new guild password with confirmation by using the old one
			oldpass, newpass = $1, $2
			# try to change the password
			result = @action.try_guild_password_change(oldpass, newpass)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::PasswordChanging} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PasswordIncorrect
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGDI(.+)/ # guild disbanding
			password = $1
			# try to disband the guild
			result = @action.try_guild_disband(password)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::GuildDisbanding.sub('GUILD') {@player.guildname}} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PasswordIncorrect
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGTR(.+)\t(.+)/ # guild transfer
			username, password = $1, $2
			# try to remove a guild member
			result = @action.try_guild_transfer(username, password)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::GuildTransferring.sub('PLAYER') {username}.sub('GUILD') {@player.guildname}
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PasswordIncorrect
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_ALTFAIL
				message = RMXOS::Data::PlayerNotOnMap.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGIN(.+)/ # guild invitation
			username = $1
			# try to remove a guild member
			result = @action.try_guild_invite(username)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = RMXOS::Data::GuildInvited.sub('PLAYER') {username}
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PlayerNotOnlineMap.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			when RMXOS::RESULT_ALTFAIL
				message = RMXOS::Data::PlayerAlreadyGuild.sub('PLAYER') {username}
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGRE(.+)\t(.+)/ # remove member from guild
			username, password = $1, $2
			# try to remove a guild member
			result = @action.try_guild_remove(username, password)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::GuildRemoving.sub('PLAYER') {username}} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PasswordIncorrect
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGLE(.+)/ # leave guild
			password = $1
			# try to change the password
			result = @action.try_guild_leave(password)
			# get the appropriate message and color for the result
			case result
			when RMXOS::RESULT_SUCCESS
				message = "#{RMXOS::Data::GuildLeaving.sub('GUILD') {@player.guildname}} #{RMXOS::Data::AreYouSure}"
				color = RMXOS::Data::ColorInfo
			when RMXOS::RESULT_FAIL
				message = RMXOS::Data::PasswordIncorrect
				color = RMXOS::Data::ColorError
			end
			# send message
			self.send("CHT#{color}\t0\t#{message}")
			return true
		when /\AGME(.+)/ # guild message
			@sender.send_to_guild("CHT#{$1}", true)
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages during the saving process.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_saving
		case @message
		when /\ASCL\Z/ # clearing garbage save data
			# add the new query
			@saving_queries.push("DELETE FROM save_data WHERE user_id = #{@player.user_id}")
			return true
		when /\ASAV(.+)\t(.+)/ # saving data, $1 is the type hierarchy, $2 is the actual data, they are divided by a tab character
			# create saving query
			query = "REPLACE INTO save_data (user_id, data_name, data_value) VALUES (#{@player.user_id}, '#{$1}', '#{$2}')"
			# add the new query
			@saving_queries.push(query)
			return true
		when /\ASEN\Z/ # saving transaction end query
			@saving_queries.push('COMMIT')
			# execute all saving queries
			@saving_queries.each {|query| RMXOS.server.sql.query(query)}
			@saving_queries = ['START TRANSACTION']
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Checks messages for loading.
	# Returns: True or false whether to stop checking this message.
	#----------------------------------------------------------------------
	def check_loading
		case @message
		when /\ALRQ\Z/ #  load request
			# get all data for this user
			check = RMXOS.server.sql.query("SELECT * FROM save_data WHERE user_id = #{@player.user_id}")
			# for each entry
			check.num_rows.times {
				hash = check.fetch_hash
				# send user this data entry of his account
				self.send("LOA#{hash['data_name']}\t#{hash['data_value']}")
			}
			# end loading
			self.send('LEN')
			return true
		end
		return false
	end
	#----------------------------------------------------------------------
	# Sends the client that he's been disconnected.
	#----------------------------------------------------------------------
	def disconnect
		self.send('DCS')
	end
	#----------------------------------------------------------------------
	# Broadcasts disconnection of this client to all clients.
	#----------------------------------------------------------------------
	def terminate
		@sender.send_to_all("DCT#{@player.user_id}") if @player.user_id > 0
		@socket.close rescue nil
	end
	#----------------------------------------------------------------------
	# Sends a message to the actual connected client.
	#  message - message that will be sent
	#----------------------------------------------------------------------
	def send(message)
		@sender.send(message)
	end

end
