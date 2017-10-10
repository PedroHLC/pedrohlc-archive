puts "================================================================="
puts " Screen Mode Changer"
puts " VersÃ£o: 0.7.4"
puts " Por: PedroHLC"
puts "================================================================="
require 'Win32API'
def clicked?(key)
  Win32API.new("user32","GetAsyncKeyState",['i'],'i').call(key) & 0x01 == 1
end
#Get Game Info
print "Largura da janela[Somente numeros, sem bordas]: "
@resolution_width = gets.to_i
print "Altura da janela[Somente numeros, sem bordas]: "
@resolution_height = gets.to_i
#Get 'SO&Game' Info
@can_set_so_resolution = false
loop do
  print "Alterar a resolução do Windows?[Use S(Sim),N(Não)]: "
  can_change_resolution = gets.to_s.strip.upcase
  case can_change_resolution[0]
  when "S"[0]
    @can_set_so_resolution = true
    break
  when "N"[0]
    @can_set_so_resolution = false
    break
  else
    puts "::Resposta desconhecida"
  end
end
puts "Abra a janela do jogo e pressione F9."
loop do
  if clicked?(120)
    @main_window = Win32API.new('user32', 'GetForegroundWindow', '', 'L').call
    break
  end
end
#Get APIs
@get_window = Win32API.new('user32', 'FindWindow', 'PP', 'I')
@get_system_metrics = Win32API.new('user32', 'GetSystemMetrics', 'I', 'I')
@get_client_rect = Win32API.new('user32', 'GetClientRect', 'LP', 'I')
@set_window_long = Win32API.new('user32', 'SetWindowLong', 'LIL', 'L')
@set_window_pos = Win32API.new('user32', 'SetWindowPos', 'LLIIIII', 'I')
#Get Sytem Info
@so_resolution_width = @get_system_metrics.call(0).to_i
@so_resolution_height = @get_system_metrics.call(1).to_i
@so_extra_width = @get_system_metrics.call(32).to_i - 2
@so_extra_height = @get_system_metrics.call(33).to_i + @get_system_metrics.call(4).to_i - 2
#Some functions
def set_so_resolution(width,height)
  return if @can_set_so_resolution != true
  system("dc.exe -width=#{width} -height=#{height} -force -quiet")
  sleep(2)
end
#Do the work
puts "Pressione:\nF10 (Janela)\nF11 (Tela Cheia)"
loop do
  if clicked?(120)
    @main_window = Win32API.new('user32', 'GetForegroundWindow', '', 'L').call#  @main_window = @get_window.call(@game_description, @game_title).to_i
  elsif clicked?(121)
    set_so_resolution(@so_resolution_width, @so_resolution_height)
    final_width = (@resolution_width + @so_extra_width)
    final_height = (@resolution_height + @so_extra_height)
    x = (@so_resolution_width / 2) - (final_width / 2)
    y = (@so_resolution_height / 2) - (final_height / 2)
    @set_window_pos.call(@main_window, 0, x, y, final_width, final_height, 64)
    @set_window_long.call(@main_window, -16, 0x14CA0000)
  elsif clicked?(122)
    set_so_resolution(@resolution_width, @resolution_height)
    @set_window_pos.call(@main_window, 0, 0, 0, @resolution_width, @resolution_height, 64)
    @set_window_long.call(@main_window, -16, 0x14000000)
  end
end