class GlobalEvents
  def initialize
    @connection = TCPServer.new("localhost",PORT.to_i+1)
  end
end