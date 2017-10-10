require 'Win32API'
require 'win32/process'
def process_exist?(pid)
  begin
      Process.kill(0, Integer(pid))
      return true
  rescue
      return false
  end
end
puts process_exist?(Process.pid)
Win32API.new("kernel32", "OutputDebugString", ['P'], 'V').call("Hello, World\n")
#Process.setrlimit(Process::LIMIT_MEMLOCK, Process::HIGH_PRIORITY_CLASS , Process::LIMIT_INFINITY)
#Process.getrlimit(Process::LIMIT_MEMLOCK)
gets