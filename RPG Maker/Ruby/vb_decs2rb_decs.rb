lines_list = File.open('vb_decs.txt','rb').readlines
final_file =  File.open('rb_decs.txt','w')

for line in lines_list
  case line
  when /Public Const (.*) = &H(.*)/
    final_file.write("  #{$1} = 0x#{$2.to_s.strip}\n")
  when /Public Const (.*) = (.*)/
    final_file.write("  #{$1} = #{$2.to_s.strip}\n")
  else
    final_file.write("  \n")
  end
end

final_file.close