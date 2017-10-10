original_file = File.open('keys.htm','rb').readlines
new_file = File.open('keys.txt','w')
unknow = 0
for i in 0..(original_file.size - 1)
  case original_file[i].to_s
  when /VK_(.*)/
    new_file.write("\n  " + $1.to_s.strip + ' = ')
  when /0x(.*)/
    new_file.write(original_file[i].to_s.strip)
  else
    line = original_file[i].to_s.strip
    if line == '-'
      new_file.write("\n  UNKNOW" + unknow.to_s + ' = ')
      unknow += 1
    elsif line.size > 0
      new_file.write(' #' + line)
    end
  end
end
new_file.close