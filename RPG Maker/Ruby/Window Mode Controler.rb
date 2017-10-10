puts "================================================================="
puts " Window Mode Controler"
puts " Version: 0.7.1"
puts " By: PedroHLC"
puts "================================================================="
require 'Win32API'
def clicked?(key)
  Win32API.new("user32","GetAsyncKeyState",['i'],'i').call(key) & 0x01 == 1
end
puts "Digite a largura da janela(sem as bordas)"
$window_width = gets.to_s.strip.to_i
puts "Digite a altura da janela(sem as bordas)"
$window_height = gets.to_s.strip.to_i
puts "Digite 1 para indicar a descricaoo e titulo da janela,"
puts "digite qualquer outra tecla para o modo automatico!"
$type = gets.to_s.strip.to_i
if $type == 1
  puts "Digite a descricao do aplicativo"
  @description = gets.to_s.strip
  puts "Digite o titulo da janela"
  @title = gets.to_s.strip
end
puts "Quando o jogo acabar de carregar pressione F9\nLogo apos presione:\nF10 (Janela)\nF11 (Tela Cheia)"
loop do
  if clicked?(120)
    @get_system_metrics  = Win32API.new('user32', 'GetSystemMetrics', 'I', 'I')
    @set_window_long = Win32API.new('user32', 'SetWindowLong', 'LIL', 'L')
    @set_window_pos  = Win32API.new('user32', 'SetWindowPos', 'LLIIIII', 'I')  
    #@set_resolution = Win32API.new('Display.dll', 'SetResolution', 'III', 'I')
    if $type == 1
      @window = Win32API.new('user32', 'FindWindow', 'PP', 'I').call(@description, @title)
    else
      @window = Win32API.new('user32', 'GetForegroundWindow', '', 'L').call#Win32API.new('user32', 'GetActiveWindow', '', 'L').call
    end
    puts("Id da janela: #{@window}")
    @gsm = Win32API.new('user32', 'GetSystemMetrics', 'I', 'I')
    @pc_resolution = [@gsm.call(0).to_i,@gsm.call(1).to_i]
    @default_size = [$window_width, $window_height]
  end
  if clicked?(121)
    x = @pc_resolution[0] / 2 - @default_size[0] / 2
    y = @pc_resolution[1] / 2 - @default_size[1] / 2
    @set_window_long.call(@window, -16, 0x14CA0000)
    @set_window_pos.call(@window, 0, x, y, (@default_size[0]+6), (@default_size[1]+30), 0)
    #@set_resolution.call(@pc_resolution[0], @pc_resolution[1], 4)
  end
  if clicked?(122)
    @set_window_long.call(@window, -16, 0x14000000)
    @set_window_pos.call(@window, -1, 0, 0, @pc_resolution[0], @pc_resolution[1], 64)
    #@set_resolution.call(@default_size[0], @default_size[1], 4)
  end
end