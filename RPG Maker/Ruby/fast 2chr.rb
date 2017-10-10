file = File.open("./Numeric.fast_chr.rb","a+")
file.write("class Numeric\n")
file.write("  def fast_chr\n")
file.write("    case self\n")
for i in (0..255)
  file.write("    when #{i}\n")
  file.write("      return '#{i.chr}'\n")
end
  file.write("    else\n")
  file.write("      return self.chr\n")
file.write("    end\n")
file.write("  end\n")
file.write("end\n")

file.close