require "Win32API"
API = Win32API.new('kernel32', 'Beep', 'LL', 'I')
loop do
  a = rand(900)
  API.call(a,100)
end