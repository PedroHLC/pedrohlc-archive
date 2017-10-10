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

server = RMXOS::Server.new
server.connect_to_database

puts '> Extracting IPs...'
check = server.sql.query("SELECT users.username AS 'username', ips.ip AS 'ip' FROM users JOIN ips ON users.user_id = ips.user_id")
matches = {}
ips = {}
check.num_rows.times {
	hash = check.fetch_hash
	username = hash['username']
	ip = hash['ip']
	ips[username] = [] if !ips.has_key?(username)
	matches[ip] = [] if !matches.has_key?(ip)
	ips[username].push(ip)
	matches[ip].push(username)
}
puts '> Closing database connection...'
server.sql.close rescue nil

# remove duplicate entries
ips.each_key {|key| ips[key] |= ips[key]}
matches.each_key {|key| matches[key] |= matches[key]}
puts ''

keys = ips.keys.sort
keys.each_index {|i|
	# show 20 users "per page"
	if i % 20 == 0 && i != 0
		puts 'Press ENTER for the next 20 users.'
		gets
	end
	username = keys[i]
	puts "- #{username}"
	puts "    used IP addresses:"
	matching = []
	ips[username].each {|ip|
		matching += matches[ip]
		puts "      #{ip}"
	}
	matching |= matching
	matching.delete(username)
	if matching.size > 0
		puts "    other users with same IP:"
		matching.each {|name| puts "      #{name}"}
	end
	2.times {puts ''}
}

puts 'Press ENTER to continue.'
gets
puts 'Please wait...'
