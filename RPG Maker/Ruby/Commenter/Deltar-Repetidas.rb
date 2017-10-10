#print "Arquivo do Bimestre anterior: "
oldfilepath = "L:\\Tranqueira\\Cpp+Rb\\Commenter\\LP-COMMENTED.BACKUP.CPP"#gets
#print "Pasta com todos os arquivos: "
filefolderpath = "C:\\Users\\PedroHLC\\Desktop\\LP-Comentado"#gets

$DEBUG = false
if $DEBUG == true
  begin
    oldfilelines = File.open(oldfilepath, "rb").readlines
    oldfilelines.each{ |line|
      if line =~ /arquivo: (.*).cpp/
        if File.exist?(filefolderpath + "\\" + $1.strip + ".cpp")
          File.delete(filefolderpath + "\\" + $1.strip + ".cpp")
        end
      end
    }
  rescue Exception => error
    puts error
  end
  gets
else
  oldfilelines = File.open(oldfilepath, "rb").readlines
  oldfilelines.each{ |line|
    if line =~ /arquivo: (.*).cpp/
      if File.exist?(filefolderpath + "\\" + $1.strip + ".cpp")
        File.delete(filefolderpath + "\\" + $1.strip + ".cpp")
      end
    end
  }
end