# loading Ruby's libraries
require 'socket'
# loading external libraries
require './mysql.so'

# loading classes
begin
	load './Data/Action.rb'
	load './Data/Action_Handler1.rb'
	load './Data/Action_Handler2.rb'
	load './Data/Action_Handler3.rb'
	load './Data/Action_Handler4.rb'
	load './Data/Client.rb'
	load './Data/Data.rb'
	load './Data/Options.rb'
	load './Data/Player.rb'
	load './Data/Sender.rb'
	load './Data/Server.rb'
rescue SyntaxError
	puts $!.message
	gets
	exit
end

# loading settings
begin
	load './cfg.ini'
rescue SyntaxError
	puts RMXOS::Data::ConfigurationError
	puts RMXOS::Data::PressEnter
	gets
	exit
end
# in case somebody messed up the config of extensions
EXTENSIONS.compact!

#======================================================================
# module RMXOS
#----------------------------------------------------------------------
# This is the container for RMXOS.
#======================================================================

module RMXOS
	
	# Logging files
	Logs = {}
	Logs['Error'] = 'logs/errors.log'
	Logs['Incoming Message'] = 'logs/messages.log'
	Logs['Outgoing Message'] = 'logs/messages.log'
	Logs['Action'] = 'logs/actions.log'
	Logs['Extension'] = 'logs/extension_errors.log'
	Logs['Debug'] = 'logs/debug.log'
	#----------------------------------------------------------------------
	# RMX-OS Main Loop.
	#----------------------------------------------------------------------
	def self.main
		while true
			# clear clients
			$clients = []
			begin
				# try to create a server
				@server = Server.new
				# try to start it
				@server.start
				# try to keep it running
				@server.run
			rescue Interrupt
				@server.shutdown
				@server.execute_shutdown
				return
			rescue
				# error during server start or while running
				puts RMXOS::Data::UnexpectedError
				puts $!.message
				puts $!.backtrace.join("\n").gsub(Dir.getwd) {'.'}
			end
			@server.shutdown
			@server.force_shutdown
			# stop everything if no auto-restart
			break if !AUTO_RESTART
			# wait for N seconds
			print RMXOS::Data::Restart
			(0...RESTART_TIME).each {|i|
				print " #{RESTART_TIME - i}"
				sleep(1)
			}
			puts "\n\n"
			@extensions.each_value {|ext| ext.initialize}
		end
	end
	#----------------------------------------------------------------------
	# Gets all extensions.
	#----------------------------------------------------------------------
	def self.extensions
		return @extensions
	end
	#----------------------------------------------------------------------
	# Loads all extensions.
	#----------------------------------------------------------------------
	def self.load_extensions
		@extensions = {}
		puts RMXOS::Data::ExtensionsLoading
		# if there are any extensions defined
		if EXTENSIONS.size > 0
			# for every extension filename
			EXTENSIONS.each {|file|
        puts "Extension loaded: #{file}"
				file += '.rb' if file[file.size - 3, 3] != '.rb'
				filepath = "./Extensions/#{file}"
				begin
					# try to load the file
					require filepath
					# try to load the actual extension
					@extensions[file] = self.load_current_extension
					# if version is ok
					if RMXOS_VERSION >= @extensions[file]::RMXOS_VERSION
						# try to activate it
						@extensions[file].initialize
						puts RMXOS::Data::ExtensionLoaded.sub('FILE') {file}.sub('VERSION') {@extensions[file]::VERSION}
					else
						# version error
						puts RMXOS::Data::ExtensionVersionError.sub('FILE') {file}.sub('VERSION') {@extensions[file]::RMXOS_VERSION}
					end
				rescue SyntaxError
					puts RMXOS::Data::ExtensionLoadError.sub('FILE') {file}
					puts $!.message
				rescue Errno::ENOENT
					puts RMXOS::Data::ExtensionFileError.sub('FILE') {file}
				rescue
					puts RMXOS::Data::ExtensionInitError.sub('FILE') {file}
					puts $!.message
					puts $!.backtrace.join("\n")
				end
			}
		else
			puts RMXOS::Data::NoExtensions
		end
	end
	#----------------------------------------------------------------------
	# Gets the currently running TCP Server.
	# Returns: Server Instance.
	#----------------------------------------------------------------------
	def self.server
		return @server
	end
	#----------------------------------------------------------------------
	# Gets a string representing the time for SQL queries.
	#  time - Time instance
	# Returns: String in SQL time format.
	#----------------------------------------------------------------------
	def self.get_sqltime(time)
		return time.strftime('%Y-%m-%d %H-%M-%S')
	end
	#----------------------------------------------------------------------
	# Gets a string of numbers that can be used to instantiate a Time object.
	#  time - SQL time string
	# Returns: Time string separated by commas.
	#----------------------------------------------------------------------
	def self.get_rubytime(time)
		return time.gsub('-') {','}.gsub(':') {','}.gsub(' ') {','}.gsub(/,0(\d)/) {",#{$1}"}
	end
	#----------------------------------------------------------------------
	# Fixes strings for SQL queries and eval expressions.
	#  string - string to be converted
	# Returns: Converted string.
	#----------------------------------------------------------------------
	def self.fix_string(string)
		return string.gsub('\'') {'\\\''}
	end
	#----------------------------------------------------------------------
	# Logs a message into a file.
	#  data - the data that created this log
	#  type - what kind of log
	#  message - message to be logged
	#----------------------------------------------------------------------
	def self.log(data, type, message)
		return if type == 'Debug' && !DEBUG_MODE
		return if !RMXOS::Logs.has_key?(type)
		# use user ID and username if data is player
		data = "#{data.user_id} (#{data.username})" if data.is_a?(Player)
		# has 100 attempts to write down the data;
		# this part is necessary to avoid usage of Thread.exclusive,
		# yet prevent problem with concurrent file access
		count = 100
		while count > 0
			begin
				# open log file in append mode
				file = File.open(Logs[type], 'a+')
				# write time, data type and message
				file.write("#{Time.now.getutc.to_s}; #{data} - #{type}:\n#{message}\n") rescue nil
				file.close()
				break
			rescue
				count -= 1
				sleep(0.01)
			end
		end
	end
	
end

puts RMXOS::Data::Header
puts RMXOS::Data::Version.sub('VERSION') {RMXOS_VERSION.to_s}
puts RMXOS::Data::Header
begin
	# load extensions
	RMXOS.load_extensions
	# RMX-OS main
	RMXOS.main
rescue Interrupt # CTRL + C
end
begin
	# last message
	puts ''
	puts RMXOS::Data::PressEnter
	gets
rescue Interrupt # CTRL + C
end
