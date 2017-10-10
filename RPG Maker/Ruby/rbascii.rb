loop do
  print "Digite o caracter: "
  c = gets
  
  puts "ASCII: #{c[0]}"
  for i in 0..999
    code = eval('"\\' + i.to_s + '"')
    if code == c[0].chr
      puts "\\#{i}"
      break
    end
  end
  gets
  system("cls")
end