$file_list = {}

def list_folder(path)
  for item in Dir.entries(path)
    next if item.nil?
    next if !item.is_a?(String)
    next if item == '.'
    next if item == '..'
    item_path = path + '/' + item.to_s
    next if item_path == './list_this_folder.rb'
    if File.directory?(item_path)
      list_folder(item_path)
    else
      $file_list[item_path] = File.size(item_path).to_s
    end
  end
end

loop do
  puts "Expandir caminho?[S,N]: "
  result = gets.to_s.strip.downcase
  case result
    when 's'
      puts "Listando arquivos."
      list_folder(File.expand_path('.'))
      break
    when 'n'
      puts "Listando arquivos."
      list_folder('.')
      break
    else
      puts "Resposta desconhecida, respoda S para sim ou N para não!..."
      sleep(2)
      system('cls')
    end
end

puts "Salvando resultado."
output_file = File.open('folder_list.txt', 'w')
for file in $file_list
  output_file.write("#{file[0]} :> #{file[1]}\n")
end
output_file.close