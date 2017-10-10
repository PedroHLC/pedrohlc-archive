puts "======================"
puts "HTML2TXT Inventory"
puts "Created by: PedroHLC"
puts "Version: 1.0"
puts "======================"
$input_folder = '.\\HTML\\'
$output_file = '.\\TXT\\'

def convert_file(filename)
  file = File.open(filename, 'rb').readlines
  finalfilename = filename.gsub!($input_folder,$output_file)
  finalfile = File.open(finalfilename, 'w')
  item_id = 0
  for line in file
    case line
    when /<tr>/
      item_id += 1
      finalfile.write("<i>#{item_id}</i>\n")
    when /File:(.*).gif" class=/
      finalfile.write("<v>icon=#{$1}</v>\n")
    when /<\/td><td><b><a href="\/wiki\/(.*)" title="(.*)">(.*)<\/a><\/b><br(.*)/
      finalfile.write("<v>title=#{$3}</v>\n")
    when /<\/td><td><b><a href="\/wiki\/(.*)" title="(.*)" class="mw-redirect">(.*)<\/a>&nbsp;/
      finalfile.write("<v>title=#{$3}</v>\n")
    when /<\/td><td><b><a href="\/wiki\/(.*)" title="(.*)">(.*)<\/a>&nbsp;/
      finalfile.write("<v>title=#{$3}</v>\n")
    when /<\/td><td><i>(.*)<\/i>/
      unless $1.include?('<a')
        finalfile.write("<v>description=#{$1}</v>\n")
      end
    when /<\/td><td><b>Attrib<\/b>: (.*)>(.*)<\/a><br(.*)/
      finalfile.write("<v>attribute=#{$2}</v>\n")
    when /<\/td><td><b>Attrib<\/b>: (.*)<br(.*)/
      finalfile.write("<v>attribute=#{$1}</v>\n")
    when /<\/td><td>ATK \+(.*), DEF \+(.*)<br(.*)/
      finalfile.write("<v>atk_plus=#{$1}</v>\n")
      finalfile.write("<v>def_plus=#{$2}</v>\n")
    when /<\/td><td>ATK \+(.*), DEF \-(.*)<br(.*)/
      finalfile.write("<v>atk_plus=#{$1}</v>\n")
      finalfile.write("<v>def_less=#{$2}</v>\n")
    when /<\/td><td>DEF \+(.*), ATK \+(.*)<br(.*)/
      finalfile.write("<v>atk_plus=#{$1}</v>\n")
      finalfile.write("<v>def_plus=#{$2}</v>\n")
    when /<\/td><td>ATT \+(.*) DEF \-(.*)<br(.*)/
      finalfile.write("<v>att_plus=#{$1}</v>\n")
      finalfile.write("<v>def_less=#{$2}</v>\n")
    when /<\/td><td>ATT \+(.*)<br(.*)/
      finalfile.write("<v>att_plus=#{$1}</v>\n")
    when /<\/td><td>ATK \+(.*)<br(.*)/
      finalfile.write("<v>atk_plus=#{$1}</v>\n")
    when /<\/td><td>DEF \+(.*)<br(.*)/
      finalfile.write("<v>def_plus=#{$1}</v>\n")
    end
  end
  finalfile.close
end

def convert_folder(path)
  for filename in Dir.entries(path)
    next if filename.nil?
    next if filename == '.'
    next if filename == '..'
    
    if File.directory?(path + filename)
      convert_folder(path + filename + '\\')
    else
      convert_file(path + filename)
    end
  end
end

convert_folder($input_folder)