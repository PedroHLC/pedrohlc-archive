puts "#GodOnline's Window Controler #By PedroHLC #Ver. 1.0"
require 'Win32API'
def clicked?(key)
  Win32API.new("user32","GetAsyncKeyState",['i'],'i').call(key) & 0x01 == 1
end
loop do
  print "Diga-me a resolução de seu monitor(1024x768): "
  resolution = gets.to_s.strip
  if resolution =~/(.*)x(.*)/
    @pc_resolution = [$1.to_i,$2.to_i]
    break if @pc_resolution[0] >= 1024 and @pc_resolution[0] >= 768
  end
end
puts "\nQuando o jogo acabar de carregar pressione F9\nLogo apos presione F10 para alterar o estado da janela!"
loop do
  if clicked?(120)
    @get_system_metrics  = Win32API.new('user32', 'GetSystemMetrics', 'I', 'I')
    @set_window_long = Win32API.new('user32', 'SetWindowLong', 'LIL', 'L')
    @set_window_pos  = Win32API.new('user32', 'SetWindowPos', 'LLIIIII', 'I')  
    @set_resolution = Win32API.new('Display.dll', 'SetResolution', 'III', 'I')
    @window = Win32API.new('user32', 'FindWindow', 'PP', 'I').call("RGSS Player", "GOD Online")
    @state = "full"
  end
  a = clicked?(121)
  if a and @state == "full"
    x = (@pc_resolution[0] / 2) - 512
    y = (@pc_resolution[1] / 2) -384
    @set_window_long.call(@window, -16, 0x14CA0000)
    @set_window_pos.call(@window, 0, x, y, 1030, 798, 0)
    @set_resolution.call(@pc_resolution[0], @pc_resolution[1], 4)
    @state = "window"
  elsif a and @state == "window"
    @set_window_long.call(@window, -16, 0x14000000)
    @set_window_pos.call(@window, -1, 0, 0, 1024, 768, 64)
    @set_resolution.call(1024, 768, 4)
    @state = "full"
  end
end