class String
  def each_char
    if block_given?
      scan(/./m) do |x|
        yield x
      end
    else
      scan(/./m)
    end
  end
end

begin
  @serial_base = "ABCDEFGHJKLMNOPQ"
  
  loop do
    print "Diga-me seu nome: "
    @name = gets.to_s.strip
    if @name.size < 10
      puts "O seu nome deve ter mais de 10 letras"
    else
      break
    end
  end
  
  @encrypted_lines = []
  
  pass_chr = 0
  for name_i in 0..(@name.size - 1)
    pass_chr += @name[name_i]
  end
  @pass_chr = (pass_chr / @name.size - 1).to_i
  
  for serial_i in 0..(@serial_base.size - 1)
    new_ascii = (@serial_base[serial_i] + @pass_chr)
    if new_ascii > 90
      loop do
        new_ascii -= (3 * (@pass_chr / 9))
        break if new_ascii <= 90
      end
    end
    if new_ascii < 65
      loop do
        new_ascii += (3 * (@pass_chr / 13))
        break if new_ascii >= 65
      end
    end
    @encrypted_lines[serial_i] = new_ascii.chr
  end
  puts @encrypted_lines.to_s
  
rescue Exception => error
  puts error
end
gets