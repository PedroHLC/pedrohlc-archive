require 'Win32API'
@window = Win32API.new('user32', 'FindWindow', 'PI', 'I').call("RGSS Player", 0)
if @window < 1
  @set_window_long = Win32API.new('user32', 'SetWindowLong', 'LIL', 'L')
  @set_window_pos  = Win32API.new('user32', 'SetWindowPos', 'LLIIIII', 'I')  
  @set_window_long.call(@window, -16, 0x14000000)
  @set_window_pos.call(@window, -1, 1360, 0, 640, 480, 64)
end