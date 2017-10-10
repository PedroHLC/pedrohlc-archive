$file = File.open('wma_list.txt', 'w')

def list_folder(path)
  folder = Dir.entries(path)
  for item in folder
    next if item.nil?
    next if !item.is_a?(String)
    next if item == '.'
    next if item == '..'
    item_path = path + '/' + item
    if File.directory?(item_path)
      list_folder(item_path)
    else
      if File.extname(item_path) == '.wma'
        path.gsub!('/','\\')
        item_path.gsub!('/','\\')
        puts item_path
        $file.write(item_path+"\n")
        system('explorer "' + path + '"')
      end
    end
  end
end

list_folder(File.expand_path('.'))

$file.close