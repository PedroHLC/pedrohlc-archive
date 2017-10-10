puts '#=============================================================================='
puts "# Project RMSusano'o"
puts '# By: PedroHLC'
puts '# Ver: 0.6.3 27/06/11'
puts '#------------------------------------------------------------------------------'
puts '# Agradecimentos a HugoLnx'
puts '#=============================================================================='
puts 'Log do processo:'
puts '-------------------------------------------------------------------------------'
#================================================================================================================================================================================================================================================
$password = 135689
#================================================================================================================================================================================================================================================
def encrypt_str(str)
  pass = (((str.size/2)**2 + $password + 12)/2).to_s
  i = 0
  while i <= (str.size - 1)
    pass.each_byte{|pass_chr|
      str[i] += pass_chr
      i += 1
      break if str[i] == nil
    }
    break if str[i] == nil
  end
  return str.to_s
end
#================================================================================================================================================================================================================================================
def password_create
  pass = ''
  while(pass.size < 6)
    print 'Digite uma senha(minimo 6 caracteres):'
    pass = encrypt_str(gets.to_s.strip)
  end
  puts '-------------------------------------------------------------------------------'
  fpass = []
  for i in 0..(pass.size - 1)
    fpass[i] = pass[i]
  end
  return fpass.to_s.to_i
end
#================================================================================================================================================================================================================================================
def password_save
  file = File.open('key.cfg','wb')
  file.write($password.to_s)
  file.close
  return true
end
#================================================================================================================================================================================================================================================
def encrypt_data_from(path)
  system "mkdir #{path}_Compiled" if !FileTest.exist?(path.to_s+"_Compiled")
  rxdata_names = Dir.entries(path).find_all{|filename| filename.downcase.include?('.rxdata')}
  rxdata_names.each{|filename|
    filepath = (path + "\\" + filename).to_s
    puts "Encriptando: '#{filepath}'"
    loadfile = File.open(filepath,'rb').readlines.to_s
    savefile = File.open((path + "_Compiled\\" + filename).to_s,'wb')
    begin
      savefile.write(encrypt_str(loadfile))
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
def encrypt_graphics_from(mpath, spath="")
  system "mkdir #{mpath}_Compiled" if !FileTest.exist?(mpath.to_s+"_Compiled")
  path = mpath + "\\" + spath
  #
  Dir.entries(path).each{|filename|
    next if filename == '.' or filename == '..'
    filepath = (path + "\\" + filename).to_s
    if File.directory?(filepath)
      encrypt_graphics_from(mpath, spath + "\\" + filename)
    elsif File.exist?(filepath) and (filename.downcase.include?('.bmp') or filename.downcase.include?('.png') or filename.downcase.include?('.jpg') )
      puts "Encriptando: '#{filepath}'"
      loadfile = File.open(filepath,'rb').readlines.to_s
      system "mkdir #{mpath}_Compiled\\#{spath}" if !File.exist?("#{mpath}_Compiled\\#{spath}")
      savefile = File.open((mpath + "_Compiled\\" + spath + "\\" + File.basename(filename, ".*") + '.rmi').to_s,'wb')
      begin
        savefile.write(encrypt_str(loadfile))
        savefile.close
        puts 'Encriptado com sucesso'
      rescue Exception => error
        savefile.close
        puts "Erro durante a encriptacao de '#{(path + "\\" + filename).to_s}':"
        puts error.to_s
        return false
      end
      puts '-------------------------------------------------------------------------------'
    end
  }
  return true
end
#================================================================================================================================================================================================================================================
def encrypt_audios_from(mpath, spath="")
  system "mkdir #{mpath}_Compiled" if !FileTest.exist?(mpath.to_s+"_Compiled")
  path = mpath + "\\" + spath
  #
  Dir.entries(path).each{|filename|
    next if filename == '.' or filename == '..'
    filepath = (path + "\\" + filename).to_s
    if File.directory?(filepath)
      encrypt_audios_from(mpath, spath + "\\" + filename)
    elsif File.exist?(filepath) and (filename.downcase.include?('.mid') or filename.downcase.include?('.wav') or filename.downcase.include?('.mp3')  or filename.downcase.include?('.ogg'))
      puts "Encriptando: '#{filepath}'"
      loadfile = File.open(filepath,'rb').readlines.to_s
      system "mkdir #{mpath}_Compiled\\#{spath}" if !File.exist?("#{mpath}_Compiled\\#{spath}")
      savefile = File.open((mpath + "_Compiled\\" + spath + "\\" + File.basename(filename, ".*") + '.rma').to_s,'wb')
      begin
        savefile.write(encrypt_str(loadfile))
        savefile.close
        puts 'Encriptado com sucesso'
      rescue Exception => error
        savefile.close
        puts "Erro durante a encriptacao de '#{(path + "\\" + filename).to_s}':"
        puts error.to_s
        return false
      end
      puts '-------------------------------------------------------------------------------'
    else
    end
  }
  return true
end
#================================================================================================================================================================================================================================================
begin
  $password = password_create
  result = password_save
  system("mkdir .\\Backup") if !FileTest.exist?(".\\Backup")
  
  system('move .\\Data Backup\\Data')
  puts '-------------------------------------------------------------------------------'
  result = encrypt_data_from('.\\Backup\\Data') if result == true
  system('move .\\Backup\\Data_Compiled .\\Data')
  puts '-------------------------------------------------------------------------------'
  
  system('move .\\Graphics .\\Backup\\Graphics')
  puts '-------------------------------------------------------------------------------'
  result = encrypt_graphics_from('.\\Backup\\Graphics') if result == true
  system('move .\\Backup\\Graphics_Compiled .\\Graphics')
  puts '-------------------------------------------------------------------------------'
  
  system('move .\\Audio .\\Backup\\Audio')
  puts '-------------------------------------------------------------------------------'
  result = encrypt_audios_from('.\\Backup\\Audio') if result == true
  File.open('.\\Backup\\Audio_Compiled\\Empty.rma', 'wb').close  if result == true
  system('move .\\Backup\\Audio_Compiled .\\Audio')
  puts '-------------------------------------------------------------------------------'
  
  puts 'Game encriptado com sucesso!' if result == true
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