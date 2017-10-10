require "Win32API"
@gsm = Win32API.new('user32', 'GetSystemMetrics', 'I', 'I')
@swp = Win32API.new('user32', 'SetWindowPos', 'LLIIIIL', 'I') 
@gwd = Win32API.new('user32', 'GetForegroundWindow', '', 'L')#Win32API.new('user32', 'FindWindow', 'PI', 'L')
@gks = Win32API.new("user32","GetAsyncKeyState",['i'],'i')
def clicked?(key)
  @gks.call(key) & 0x01 == 1
end
print "Insira a WID da janela que deseja fechar(0: para pesquisar): "
wid = gets.to_i
if wid <= 0
  puts "Va ate a janela entao pressione F9"
  loop do
    if clicked?(120)
      @window = @gwd.call
      puts "Sua WID e: #{@window}"
      break
    end
  end
else
  @window = wid
end
loop do
  puts "Digte 1: para mostrar, 0: para esconder"
  swt = gets.to_i
  if swt == 0
    @swp.call(@window, 0, 0, 0, 0, 0, 0x0080)
  elsif swt == 1
    @swp.call(@window, 0, 0, 0, @gsm.call(0).to_i,@gsm.call(1).to_i, 0x0040)
  end
end