require "Win32API"
#================================================================================================================================================================================================================================================
dll = 'Projeto1.dll'
Win32API.new(dll,'test','','i').call
$encrypt = Win32API.new(dll,'slower','pii','p')
$decrypt = Win32API.new(dll,'faster','pii','p')
#================================================================================================================================================================================================================================================
print 'Digite uma frase: '
var = gets#"AAAAA\0AAAAAAA\0\0B\0\0\0AAA"
puts "\t" + var.size.to_s

a = $encrypt.call(var, var.size - 2, 1520).gsub("\\0", "\0")
puts 'Encriptado: ' + a.to_s
puts "\t" + a.size.to_s

b = $decrypt.call(a, a.size - 2, 1520).gsub("\\0", "\0")
puts 'Desencriptado: ' + b.to_s
puts "\t" + b.size.to_s

gets