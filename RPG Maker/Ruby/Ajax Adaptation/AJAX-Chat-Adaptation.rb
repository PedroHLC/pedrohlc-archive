puts "#################################################"
puts "AJAX CHAT Adaptation 4 Ruby"
puts "By: PedroHLC"
puts "Version: 1.0 - 28/11/09"
puts "#################################################"
puts "\n"
#==================================================================
require 'net/http'
require 'socket'
#==================================================================
def connect
  $host = 'mundorpgmaker.com'
  puts "Loading server..."
  $http = Net::HTTP.new($host)
  #loop do
    headers, body = $http.get("/forum/chat/index.php?logout=true")
    puts body
    gets
  #end
  $socket.close
end
#==================================================================
begin
  connect
rescue
  @logfile = File.open("log.txt", "a+")
  @logfile.write("Error[#{Time.now}]: #{$!}\n")
  @logfile.close
end