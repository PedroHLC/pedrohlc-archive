puts "Pedra, papéu, tesoura, lagarto, spock!"
puts "Desenvolvido por PedroHLC, baseado na série 'The Big Bang Theory'"

loop do

$item = []
$item[0] = ['Tesoura', [1,'corta'], [3,'decapita']]
$item[1] = ['Papeu', [2,'embrulha'], [4,'contesta']]
$item[2] = ['Pedra', [3,'esmaga'], [0,'esmaga']]
$item[3] = ['Lagarto', [4,'envenena'], [1,'come']]
$item[4] = ['Spock', [0,'esmaga'], [2,'vaporiza']]

for i in 0..4
  puts "#{i} = #{$item[i][0]}"
end

print "Sua escolha e...: "
playerc = gets.to_i
enemyc = rand(5)
puts "Seu inimigo escolheu: #{$item[enemyc][0]}\n\n"

win = nil
word = ''
for i in 1..2
  if $item[playerc][i][0] == enemyc
    win=true
    word = $item[playerc][i][1]
    break
  end
end
if win==nil
  for i in 1..2
    if $item[enemyc][i][0] == playerc
      win=false
      word = $item[enemyc][i][1]
      break
    end
  end
end

case win
when nil
  text = $item[playerc][0] + ' empata com ' + $item[enemyc][0]
  puts text
  puts "EMPATE"
when true
  text = $item[playerc][0] + ' ' + word + ' ' + $item[enemyc][0]
  puts text
  puts "GANHOU"
when false
  text = $item[enemyc][0] + ' ' + word + ' ' + $item[playerc][0]
  puts text
  puts "PERDEU"
end

puts"\nPressione ENTER para jogar novamente!"
gets

system('cls')
end