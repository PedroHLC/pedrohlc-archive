require "Win32API"
Keyboard = Win32API.new('user32', 'GetKeyboardState', 'P','')
def testallkeys
  keys = ("\0" * 256)
  Keyboard.call(keys)
  return keys
end

loop do
  system('cls')
  keys = testallkeys
  for i in 0..255
    if keys[i] > 0 and 0x01 == 1
      puts "Pressionou: #{i} : #{keys[i]}"
    end
  end
  sleep(0.5)
end