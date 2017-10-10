#================================================================================================================================================================================================================================================
puts 'Tecle ENTER para iniciar o aplicativo!'
gets
puts '-------------------------------------------------------------------------------'
puts 'Log do processo:'
puts '-------------------------------------------------------------------------------'
#================================================================================================================================================================================================================================================
module RGSSPP
  module_function 
  def encrypt_img(path, file)
    original_filepath = File.open(file,'rb')
    original_file = original_filepath.readlines.to_s
    original_filepath.close
    compiled_file = File.open(path + '/' + File.basename(file, ".*") + '.rmi','wb')
    original_file[0] += 1
    original_file[1] += 5
    original_file[2] += 4
    original_file[3] += 3
    compiled_file.write(original_file)
    compiled_file.close
  end
  def encrypt_aud(path, file)
    original_filepath = File.open(file,'rb')
    original_file = original_filepath.readlines.to_s
    original_filepath.close
    compiled_file = File.open(path + '/' + File.basename(file, ".*") + '.rma','wb')
    original_file[0] += 3
    original_file[1] += 4
    original_file[2] += 5
    original_file[3] += 1
    compiled_file.write(original_file)
    compiled_file.close
  end
end
#================================================================================================================================================================================================================================================
def encrypt_img_from(path)
  folder = Dir.entries(path)
  for i in 2..(folder.size - 1)
    file = path + '/' + folder[i]
    if File.directory?(file)
      encrypt_img_from(file)
    elsif File.exist?(file)
      if file.include?('.rmi')
        next
      else
        file = (file.gsub('/','\\')).to_s
        puts "Encriptando: '#{file}'"
        begin
          RGSSPP.encrypt_img(path, file)
          File.delete(file)
          puts 'Encriptado com sucesso'
        rescue Exception => error
          puts "Erro durante a encriptacao de '#{file}':"
          puts error.to_s
          return false
        end
        puts '-------------------------------------------------------------------------------'
      end
    end
  end
  return true
end
#================================================================================================================================================================================================================================================
def encrypt_aud_from(path)
  folder = Dir.entries(path)
  for i in 2..(folder.size - 1)
    file = path + '/' + folder[i]
    if File.directory?(file)
      encrypt_aud_from(file)
    elsif File.exist?(file)
      if file.include?('.rma')
        next
      else
        file = (file.gsub('/','\\')).to_s
        puts "Encriptando: '#{file}'"
        begin
          RGSSPP.encrypt_aud(path, file)
          File.delete(file)
          puts 'Encriptado com sucesso'
        rescue Exception => error
          puts "Erro durante a encriptacao de '#{file}':"
          puts error.to_s
          return false
        end
        puts '-------------------------------------------------------------------------------'
      end
    end
  end
  return true
end
#================================================================================================================================================================================================================================================
begin
  final_result = true
  result = encrypt_img_from('./Graphics')
  final_result = false if result == false
  result = encrypt_aud_from('./Audio') if final_result == true
  final_result = false if result == false
  puts 'Game encriptado com sucesso!' if final_result == true
  puts 'Tecle ENTER para finalizar o aplicativo!'
  gets
rescue Exception => error
  puts '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
  puts 'Ocorreu um erro, e o game nao foi encriptado corretamente:'
  puts error.to_s
  puts '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
  puts 'Prescione ENTER para finalizar o aplicativo!'
  gets
end