file = File.open('Dll.rb','rb')
lines_a = file.readlines
file.close
(lines_a.size - 1).times{|i|
 lines_a[i].strip!
 lines_a[i] += ';'
}

file = File.open('Dll;.rb','wb')
file << lines_a.to_s
file.write(';')
file.close