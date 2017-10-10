puts "================================================================="
puts " Aspect ratio discovery"
puts " By: PedroHLC"
puts " Version: 1.2 (03/2010)"
puts " 37 Modelos de aspect ratio registrados"
puts "================================================================="
puts "Diga-me a largura da resolucao"
$width = gets.to_s.strip.to_i
puts "Diga-me a a altura da resolucao"
$height = gets.to_s.strip.to_i
puts "Iniciando testes..."
#*:1
print "Resultado: "
if ($width / 4.00).to_f == ($height / 1).to_f #1
  puts "4:1"
elsif ($width / 3.00).to_f == ($height / 1).to_f #2
  puts "3:1"
elsif ($width / 2.76).to_f == ($height / 1).to_f #3
  puts "2.76:1"
elsif ($width / 2.66).to_f == ($height / 1).to_f #4
  puts "2.66:1"
elsif ($width / 2.59).to_f == ($height / 1).to_f #5
  puts "2.59:1"
elsif ($width / 2.55).to_f == ($height / 1).to_f #6
  puts "2.55:1"
elsif ($width / 2.39).to_f == ($height / 1).to_f #7
  puts "2.39:1"
elsif ($width / 2.35).to_f == ($height / 1).to_f #8
  puts "2.35:1"
elsif ($width / 2.20).to_f == ($height / 1).to_f #9
  puts "2.2:1"
elsif ($width / 2.00).to_f == ($height / 1).to_f #10
  puts "2:1"
elsif ($width / 1.85).to_f == ($height / 1).to_f #11
  puts "1.85:1"
elsif ($width / 1.78).to_f == ($height / 1).to_f #12
  puts "1.78:1"
elsif ($width / 1.75).to_f == ($height / 1).to_f #13
  puts "1.75:1"
elsif ($width / 1.66).to_f == ($height / 1).to_f #14
  puts "1.6:1"
elsif ($width / 1.56).to_f == ($height / 1).to_f #15
  puts "1.56:1"
elsif ($width / 1.50).to_f == ($height / 1).to_f #16
  puts "1.5:1"
elsif ($width / 1.43).to_f == ($height / 1).to_f #17
  puts "1.43:1"
elsif ($width / 1.37).to_f == ($height / 1).to_f #18
  puts "1.37:1"
elsif ($width / 1.33).to_f == ($height / 1).to_f #19
  puts "1.33:1"
elsif ($width / 1).to_f == ($height / 1).to_f  #20
  puts "1:1"
#*:*
elsif ($width / 17).to_f == ($height / 9).to_f #1
  puts "17:9"
elsif ($width / 16).to_f == ($height / 10).to_f #17
  puts "16:10"
elsif ($width / 16).to_f == ($height / 9).to_f #2
  puts "16:9"
elsif ($width / 11).to_f == ($height / 14).to_f #3
  puts "11:14"
elsif ($width / 8).to_f == ($height / 10).to_f #4
  puts "8:10"
elsif ($width / 8).to_f == ($height / 5).to_f #5
  puts "8:5"
elsif ($width / 6).to_f == ($height / 4.5).to_f #6
  puts "6:4.5"
elsif ($width / 6).to_f == ($height / 9).to_f #7
  puts "6:9"
elsif ($width / 6).to_f == ($height / 7).to_f #8
  puts "6:7"
elsif ($width / 6).to_f == ($height / 6).to_f #9
  puts "6:6"
elsif ($width / 5).to_f == ($height / 7).to_f #10
  puts "5:7"
elsif ($width / 5).to_f == ($height / 4).to_f #11
  puts "5:4"
elsif ($width / 5).to_f == ($height / 3).to_f #12
  puts "5:3"
elsif ($width / 4).to_f == ($height / 6).to_f #13
  puts "4:6"
elsif ($width / 4).to_f == ($height / 5).to_f #14
  puts "4:5"
elsif ($width / 4).to_f == ($height / 3).to_f #15
  puts "4:3"
elsif ($width / 3).to_f == ($height / 2).to_f #16
  puts "3:2"
#elsif ($width / i).to_f == ($height / i).to_f
#  puts "i:i"
else
  puts "Aspect Ratio Desconhecido"
  loop do
    print "Deseja iniciar o localizador bruto?[S,N]: "
    result = gets.to_s.downcase.strip
    if result == "s"
      value1 = 1
      value2 = 1
      founded = false
      loop do
        loop do
          if ($width / value1).to_f == ($height / value2).to_f
            print "Resultado: "
            puts "#{value1}:#{value2}"
            founded = true
            break
          end
          value2 += 1
          if value2.to_i > 3200
            break
          end
        end
        if founded == true
          break
        end
        value1 += 1
        value2 = 1
        if value1.to_i > 3200
          puts "Impossivel de localizar"
          break
        end
      end
      break
    elsif result == "n"
      break
    end
  end
end
puts "Pressione ENTER para finalizar."
gets