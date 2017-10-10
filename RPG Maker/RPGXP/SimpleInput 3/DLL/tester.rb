require("Win32API")

puts "Keyboard(DLL):"
x = Win32API.new('SimpleInput3.dll', 'getKeyboard', '', 'P')
before_dll = Time.now.to_f
test = x.call
puts (Time.now.to_f - before_dll).to_s

puts "Keyboard(Win32API):"
x = Win32API.new('user32','GetAsyncKeyState','l','i')
before_winapi = Time.now.to_f
for key in 0..255
	test = x.call(key)
end
puts (Time.now.to_f - before_winapi).to_s

puts "Mouse(DLL):"
x = Win32API.new('SimpleInput3.dll', 'getMouse', 'I', 'I')
before_dll = Time.now.to_f
test = x.call(0)
puts (Time.now.to_f - before_dll).to_s

puts "Mouse(Win32API):"
x = Win32API.new('user32', 'GetCursorPos', 'p', 'i')
before_winapi = Time.now.to_f
pos = [0, 0].pack('ll')
test = x.call(pos)
pos.unpack('ll')
puts (Time.now.to_f - before_winapi).to_s

puts "Joypad(DLL):"
x = Win32API.new('SimpleInput3.dll', 'getJoypad', '', 'I')
before_dll = Time.now.to_f
test = x.call
puts (Time.now.to_f - before_dll).to_s