puts '#=============================================================================='
puts '# RPG Maker VX Powerful Protection [Custom:666743]'
puts '# By: PedroHLC'
puts '# Ver: 0.6.1 03/02/11 (D/M/A)'
puts '#------------------------------------------------------------------------------'
puts '# Agradecimentos a HugoLnx'
puts '# Essa versao do produto e pouco protegida, porem e rapida e mais compativel.'
puts '#------------------------------------------------------------------------------'
puts '# Incompativel com netplays'
puts '#=============================================================================='
puts 'Tecle ENTER para iniciar o aplicativo!'
gets
puts '-------------------------------------------------------------------------------'
puts 'Log do processo:'
puts '-------------------------------------------------------------------------------'
#================================================================================================================================================================================================================================================
class String
  def each_char
    if block_given?
      scan(/./m) do |x|
        yield(x)
      end
    else
      return scan(/./m)
    end
  end
end 
#================================================================================================================================================================================================================================================
module RGSSPP
  module_function 
  def encrypt_str(str)
    pass = (((str.size/2)**2 + 666743)/2).to_s
    i = 0
    while i <= (str.size - 1)
      pass.each_char{|pass_chr|
        new_ascii = str[i] + pass_chr[0]
        new_ascii -= 256 if new_ascii > 255
        str[i] = new_ascii
        i += 1
        break if str[i] == nil
      }
      break if str[i] == nil
    end
    return str.to_s
  end
  def encrypt_img(path, file)
    original_filepath = File.open(file,'rb')
    original_file = original_filepath.readlines.to_s
    original_filepath.close
    compiled_file = File.open(path + '/' + File.basename(file, ".*") + '.rmi','wb')
    original_file[1] += 3
    original_file[2] += 3
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
    original_file[1] += 3
    original_file[2] += 3
    original_file[3] += 3
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
def encrypt_from(path)
  if !FileTest.exist?(path.to_s+"_Compiled")
    puts "Atencao: A pasta '#{path}_Compiled' nao foi encontrada."
    puts "Para poder continuar crie ela manualmente."
    return false
  end
  rxdata_names = Dir.entries(path).find_all{|filename| filename.include?('.rvdata')}
  rxdata_names.each{|filename|
    filepath = (path + "\\" + filename).to_s
    puts "Encriptando: '#{filepath}'"
    loadfile = File.open(filepath,'rb').readlines.to_s
    savefile = File.open((path + "_Compiled\\" + filename).to_s,'wb')
    begin
      savefile.write(RGSSPP.encrypt_str(loadfile))
      savefile.close
      puts 'Encriptado com sucesso'
    rescue Exception => error
      savefile.close
      puts "Erro durante a encriptacao de '#{(path + "\\" + filename).to_s}':"
      puts error.to_s
      return false
    end
    puts '-------------------------------------------------------------------------------'
  }
  return true
end
#================================================================================================================================================================================================================================================
begin
  final_result = true
  result = encrypt_from('.\\Data')
  final_result = false if result == false
  result = encrypt_img_from('./Graphics') if final_result == true
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