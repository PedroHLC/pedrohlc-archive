begin
  dir = Dir.entries('.')
  rbs = []
  for file in dir
    rbs.push file if file.include?('.rb')
  end
  for i in 0..(rbs.size - 1)
    puts "#{i}. #{rbs[i]}"
  end
  rbcode = gets.to_i
  system('cls')
  eval(File.open('./' + rbs[rbcode].to_s).read)
rescue Exception => error
  puts error
  gets
end