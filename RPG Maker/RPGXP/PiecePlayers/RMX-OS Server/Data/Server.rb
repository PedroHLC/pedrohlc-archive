class Thread
	public :sleep
end

#======================================================================
# module RMXOS
#----------------------------------------------------------------------
# This is the container for RMXOS.
#======================================================================

module RMXOS
	
	#==================================================================
	# RMXOS::Server
	#------------------------------------------------------------------
	# Serves as main processing server for RMX-OS.
	#==================================================================

	class Server
		
		# setting all accessible variables
		attr_reader   :tcp
		attr_reader   :sql
		attr_reader   :options
		attr_reader   :running
		
		#----------------------------------------------------------------------
		# Initialization.
		#----------------------------------------------------------------------
		def initialize
			# restarting server
			@running = true
			@options = RMXOS::Options.new
			@options.ip = HOST
			@options.port = PORT
			@options.sql_hostname = SQL_HOSTNAME
			@options.sql_username = SQL_USERNAME
			@options.sql_password = SQL_PASSWORD
			@options.sql_database = SQL_DATABASE
			@options.log_messages = LOG_MESSAGES
			@options.log_errors = LOG_ERRORS
			@options.log_actions = LOG_ACTIONS
			@prompt_thread = nil
		end
		#----------------------------------------------------------------------
		# Starts the server and sets up all connections
		#----------------------------------------------------------------------
		def start
			RMXOS.log(RMXOS::Debug::MainThread, 'Debug', RMXOS::Debug::ServerStarting)
			puts RMXOS::Data::Delimiter
			# server startup message
			self.start_socket
			self.connect_to_database
			self.optimize_database if OPTIMIZE_DATABASE_ON_STARTUP
			@start_time = Time.now
			# main thread for server self-maintenance
			self.run_thread_maintenance
			# anti-zombie thread if zombie client prevention option is on
			self.run_thread_anti_zombie_client if PREVENT_ZOMBIE_CLIENTS
			# run thread for extension update
			self.run_thread_extensions
			# show startup messages
			puts RMXOS::Data::Delimiter
			puts RMXOS::Data::StartSuccess.sub('TIME') {@start_time.getutc.to_s}
			puts "#{RMXOS::Data::Host}: #{@options.ip}:#{@options.port}"
			puts RMXOS::Data::CTRLC
			# ruby prompt thread if Ruby prompt optionis on
			run_thread_ruby_prompt if RUBY_PROMPT
			RMXOS.log(RMXOS::Debug::MainThread, 'Debug', RMXOS::Debug::ServerStarted)
		end
		#----------------------------------------------------------------------
		# Starts a TCP socket server.
		#  notify - whether to notify the server about this action or not
		#----------------------------------------------------------------------
		def start_socket(notify = true)
			puts RMXOS::Data::SocketStarting.sub('IP') {@options.ip}.sub('PORT') {@options.port} if notify
			@tcp = TCPServer.new(@options.ip, @options.port)
		end
		#----------------------------------------------------------------------
		# Connects to the database.
		#  notify - whether to notify the server about this action or not
		#----------------------------------------------------------------------
		def connect_to_database(notify = true)
			# connect to MySQL
			puts RMXOS::Data::MySQLConnecting.sub('DATABASE') {@options.sql_database} if notify
			@sql = Mysql.new(@options.sql_hostname, @options.sql_username, @options.sql_password, @options.sql_database)
		end
		#----------------------------------------------------------------------
		# Optimizes database tables.
		#  notify - whether to notify the server about this action or not
		#----------------------------------------------------------------------
		def optimize_database(notify = true)
			puts RMXOS::Data::MySQLOptimizing if notify
			check = @sql.query("SHOW TABLES")
			tables = []
			check.num_rows.times {tables |= check.fetch_hash.values}
			tables.each {|table|
				puts RMXOS::Data::TableOptimizing.sub('TABLE') {table}
				@sql.query("OPTIMIZE TABLE #{RMXOS.fix_string(table)}")
			}
		end
		#----------------------------------------------------------------------
		# Runs the thread
		#----------------------------------------------------------------------
		def run_thread_maintenance
			# needed for CTRL+C, client login timeout disconnection and reconnection to MySQL to prevent a connection timeout crash
			t = Thread.start {
				while @running
					time = Time.now
					# reconnection to MySQL every X minutes
					if Time.now - @start_time > DATABASE_CONNECTION_TIMEOUT * 60
						RMXOS.log(RMXOS::Debug::MaintenanceThread, 'Debug', RMXOS::Debug::DbConnectionBusy)
						@start_time = Time.now
						# store old connection
						sql = @sql
						# reconnect seemlessly
						self.connect_to_database(false)
						# close old connection
						sql.close rescue nil
						RMXOS.log(RMXOS::Debug::MaintenanceThread, 'Debug', RMXOS::Debug::DbConnectionOk)
					end
					# for every client
					$clients.each {|client|
						# if client in login screen
						if client.player.user_id < 0
							client.login_timeout -= Time.now - time
							# if timeout has expired
							if client.login_timeout < 0
								# disconnect
								client.disconnect
								# prevent multiple disconnections
								client.player.user_id = 0
							end
						end
					}
					sleep(0.01)
				end
			}
			t.priority = -10
		end
		#----------------------------------------------------------------------
		# Runs the thread that prevents zombie clients.
		#----------------------------------------------------------------------
		def run_thread_anti_zombie_client
			# deletion of zombie clients
			t = Thread.start {
				while @running
					Thread.exclusive {
						# for every client
						$clients.each {|client|
							# attempt a simple ping
							begin
								client.send('PNG')
							rescue
								RMXOS.log(client, 'Debug', RMXOS::Debug::PingFailed)
								# client side crashed, remove zombie client on server
								$clients.delete(client)
								client.socket.close rescue nil
							end
						}
					}
					sleep(5)
				end
			}
			t.priority = -10
		end
		#----------------------------------------------------------------------
		# Runs the thread that handles Ruby prompt.
		#----------------------------------------------------------------------
		def run_thread_ruby_prompt
			puts RMXOS::Data::CommandPrompt
			@prompt_thread = Thread.start {
				@lines = []
				while @running
					# start prompt
					print RMXOS::Data::CommandPromptSign
					script = gets.gsub("\n") {''}
					begin
						# attempt to combine multiple lines
						@lines.push(script)
						if script == '' || @lines.size == 1
							@lines.delete('')
							# execute script
							eval(@lines.join("\n"))
							@lines.clear
							puts ''
						end
					rescue SyntaxError
						# single/multiple line syntax error
						if script == ''
							puts RMXOS::Data::InvalidSyntax
							puts $!.message
							puts @lines.join("\n")
							@lines.clear
						end
					rescue
						puts $!.message
						@lines.clear
					end
				end
			}
			@prompt_thread.priority = -10
		end
		#----------------------------------------------------------------------
		# Runs the thread that handles extension update.
		#----------------------------------------------------------------------
		def run_thread_extensions
			# for each extension
			RMXOS.extensions.each_value {|extension|
				# if server thread needs to be running
				if extension::SERVER_THREAD
					# run it
					Thread.start(extension) {|ext|
						begin
							ext.main
						rescue
							# unexpected extension error
							name = RMXOS.extensions.key?(ext)
							RMXOS.log(name, 'Debug', RMXOS::Debug::ExtensionFailed)
							message = RMXOS::Data::ExtensionRunError.sub('FILE') {name} + "\n"
							message += $!.message + "\n"
							message += $!.backtrace.join("\n").sub(Dir.getwd) {'.'}
							RMXOS.log(name, 'Extension', message) if @options.log_errors
							puts message
							# shut down server, extension crash must not allow server to continue
							RMXOS.server.shutdown
						end
					}
				end
			}
		end
		#----------------------------------------------------------------------
		# Runs the server and handles connections.
		#----------------------------------------------------------------------
		def run
			# while the server is running
			while @running
				# accept connection
				begin
					connection = @tcp.accept_nonblock
				rescue
					# no connection in this iteration
					sleep(0.1)
					next
				end
				RMXOS.log(RMXOS::Debug::MainThread, 'Debug', RMXOS::Debug::ConnectionReceived)
				# start a thread for new client
				Thread.start(connection) {|socket|
					RMXOS.log(Thread.current.inspect, 'Debug', RMXOS::Debug::ThreadStart)
					# create new client for this socket connection
					client = Client.new(socket)
					RMXOS.log(client, 'Debug', RMXOS::Debug::ClientConnect + ' ' + socket.inspect)
					# store the client
					$clients.push(client)
					begin
						# as long as the server keeps receiving messages from this client
						while @running && !client.socket.closed?
							begin
								break if !client.socket.gets("\n")
							rescue
								break
							end
							# get the actual message
							message = $_
							# log this message if message log is turned on
							if @options.log_messages
								msg = message
								msg = msg[0, msg.size - 1] while msg[msg.size - 1] == "\n"
								RMXOS.log(client.player, 'Incoming Message', msg)
							end
							# let the client handle the received message
							client.handle(message)
						end
					rescue
						RMXOS.log(client, 'Debug', RMXOS::Debug::ClientFailed + ' ' + socket.inspect)
						# something went wrong
						error = $!
						# internal Ruby error message
						errorMessage = error.message + "\n"
						errorMessage += error.backtrace.join("\n").sub(Dir.getwd) {'.'}
						# if this connection has a corresponding client
						if $clients.include?(client)
							# log this client's error message if error log is turned on
							RMXOS.log(client.player, 'Error', errorMessage) if @options.log_errors
							# if client logged in
							if client.player.user_id > 0
								# show the error message
								message = RMXOS::Data::ClientError.sub('ID') {client.player.user_id.to_s}
								message = message.sub('NAME') {client.player.username}
								message = message.sub('TIME') {Time.now.getutc.to_s}
								# this client has been disconnected, everybody else needs to know
								client.terminate
								# client not regarded as connected anymore
								client.player.user_id = 0
							else
								# an unknown client has caused an error
								message = RMXOS::Data::UnknownClientError.sub('TIME') {Time.now.getutc.to_s}
							end
						else
							# an unknown client has caused an error
							message = RMXOS::Data::UnknownClientError.sub('TIME') {Time.now.getutc.to_s}
						end
						# RMX-OS error message
						puts message
						# show internal Ruby error message
						puts errorMessage
					end
					RMXOS.log(client, 'Debug', RMXOS::Debug::ClientDisconnect)
					# remove this client completely from the server
					$clients.delete(client) if $clients.include?(client)
					# try a soft disconnection
					begin
						client.disconnect
						sleep(1)
					rescue
						RMXOS.log(client, 'Debug', RMXOS::Debug::ClientError)
						# reqiures hard disconnection
						client.terminate rescue nil
					end
					# forcebly close the connection
					socket.close rescue nil
					RMXOS.log(Thread.current.inspect, 'Debug', RMXOS::Debug::ThreadStop)
				}
			end
			# execute soft shutdown
			self.execute_shutdown
		end
		#----------------------------------------------------------------------
		# Executes a soft shut down of the server.
		#----------------------------------------------------------------------
		def execute_shutdown
			RMXOS.log(RMXOS::Debug::MainThread, 'Debug', RMXOS::Debug::ServerStopping)
			# shutting down message
			puts "\n" + RMXOS::Data::ShuttingDown
			# for every connected client
			$clients.each {|client|
				# if connection still exists
				if !client.socket.closed?
					# attempt clean disconnect
					begin
						begin
							client.disconnect
						rescue
							client.terminate rescue nil
						end
						# forcible terminataton of all connections (because threads could be sleeping while waiting for client messages)
						client.socket.close
					rescue
						# zombie client; already disconnected
					end
				end
			}
			Thread.kill(@prompt_thread) if @prompt_thread != nil
			# wait for all threads to finish, should be immediately since all connections were terminated
			(Thread.list - [Thread.current]).each {|thread| thread.join}
			# close TCP server connection
			@tcp.close rescue nil
			# close database connection
			@sql.close rescue nil
			# done
			puts RMXOS::Data::Shutdown
			RMXOS.log(RMXOS::Debug::MainThread, 'Debug', RMXOS::Debug::ServerStopped)
		end
		#----------------------------------------------------------------------
		# Executes a hard shut down of the server.
		#----------------------------------------------------------------------
		def force_shutdown
			RMXOS.log(RMXOS::Debug::MainThread, 'Debug', RMXOS::Debug::ServerForceStopping)
			# shutting down message
			puts "\n" + RMXOS::Data::ShuttingDownForced
			# for every connected client
			$clients.each {|client|
				# if connection still exists
				if !client.socket.closed?
					# attempt clean disconnect
					client.disconnect
					# forcibly terminate connection (because thread could be sleeping while waiting for client messages)
					client.socket.close
				end
			}
			# terminate all other threads
			(Thread.list - [Thread.current]).each {|thread| Thread.kill(thread)}
			# close TCP server connection
			@tcp.close rescue nil
			# close database connection
			@sql.close rescue nil
			# done
			puts RMXOS::Data::ShutdownForced
			RMXOS.log(RMXOS::Debug::MainThread, 'Debug', RMXOS::Debug::ServerForceStopped)
		end
		#----------------------------------------------------------------------
		# Prepares the server for a soft shut down.
		#----------------------------------------------------------------------
		def shutdown
			@running = false
		end
		
	end
	
end
