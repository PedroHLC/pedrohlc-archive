puts "#=============================================================================="
puts "# MyBeep"
puts "# By: PedroHLC"
puts "# Ver: 1.0"
puts "#=============================================================================="
puts "# Observação: quando pedir a frequencia digite 'test'(sem '') para fazer um"
puts "# test automatico!"
puts "#=============================================================================="
require 'Win32API'
$beep = Win32API.new('kernel32', 'Beep', 'II', 'I')
loop do
  $beep.call(rand(800),200)
end