require('Win32API')
load('dir_fixer.rb')

$file_list = []

def list_folder(path)
  for item in Dir.entries(path)
    next if item.nil?
    next if !item.is_a?(String)
    next if item == '.'
    next if item == '..'
    item_path = path + '/' + item.to_s#Dir.UnicodeToAnsi(item.to_s)
    next if item_path == './list_this_folder.rb'
    if File.directory?(item_path)
      list_folder(item_path)
    else
      $file_list.push(item_path.to_s) if item_path.include?('.mp3')
    end
  end
end

main_path = File.expand_path('.')
puts "Listando arquivos."
list_folder(main_path)

puts "Salvando resultado."
output_file = File.open('music.asx', 'wb')

output_file.write('<ASX Version="3.0">' + "\n")
for file in $file_list
  file.to_s.gsub!(main_path , 'http://pedrohlc.dlinkddns.com:8090/Music')
  output_file.write('  <entry><ref href="' + file.to_s + '" /></entry>' + "\n")
end
output_file.write('</ASX>' + "\n")

output_file.close