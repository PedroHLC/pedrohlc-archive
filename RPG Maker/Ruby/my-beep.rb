puts "#=============================================================================="
puts "# MyBeep"
puts "# By: PedroHLC"
puts "# Ver: 1.0"
puts "#=============================================================================="
puts "# Observacao: quando pedir a frequencia digite 'test'(sem '') para fazer um"
puts "# test automatico!"
puts "#=============================================================================="
require 'Win32API'
$beep = Win32API.new('kernel32', 'Beep', 'LL', 'I')
loop do
  print "Digite a frequencia: "
  frequency = gets
  if frequency.to_s.strip == 'test'
    for i in 370..9999
      $beep.call(i, 200)
    end
    puts "#=============================================================================="
    next
  elsif frequency.to_s.strip == 'exit'
    break
  end
  frequency = (frequency.to_i)
  print "Digite a Duracao: "
  duration =gets.to_i
  $beep.call(frequency, duration)
  puts "#=============================================================================="
end