begin
  rbs = ['simple-client.rb', 'simple.server.rb']
  for i in 0..(rbs.size - 1)
    puts "#{i}. #{rbs[i]}"
  end
  rbcode = gets.to_i
  system('cls')
  load('./' + rbs[rbcode].to_s)
rescue Exception => error
  puts error
  gets
end