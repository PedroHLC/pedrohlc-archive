Dir.chdir('..')

# loading settings
load 'cfg.ini'

# loading classes
load 'Data/Data.rb'
load 'Data/Options.rb'
load 'Data/Server.rb'

# loading external libraries
require './mysql'

#======================================================================
# module RMXOS
#======================================================================

module RMXOS

	#----------------------------------------------------------------------
	# Fixes strings for SQL queries and eval expressions.
	#  string - string to be converted
	# Returns: Converted string.
	#----------------------------------------------------------------------
	def self.fix_string(string)
		return string.gsub('\'') {'\\\''}
	end
	
end

# create server instance
server = RMXOS::Server.new
# optimize the database
server.connect_to_database
server.optimize_database
server.sql.close rescue nil

puts 'Press ENTER to continue.'
gets
puts 'Please wait...'
