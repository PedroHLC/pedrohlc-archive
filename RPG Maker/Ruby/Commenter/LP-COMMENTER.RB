def comment_file(file_path)
  return unless file_path.include?('.cpp')
  return unless File.exist?($MAIN_PATH + file_path)
  file = File.open($MAIN_PATH + file_path, 'r')
  nfile = File.open('./COMMENTED.CPP', 'a+')
  #nfile.write("//????NewLine\n//****Inicío do arquivo: #{file_path.downcase}\n")
  filemtime = File::mtime($MAIN_PATH + file_path)
  #nfile.write("//****Ultima Modificação: #{filemtime.day}/#{filemtime.month}/2011\n")
  lines = file.readlines
  file.close
  i = 0
  lines.each{|line|
    while(line.include?("\n"))
      line.gsub!("\n", '')
    end
    nfile.write('')
    case line
    when /for(int(.*))/
      #nfile.write('')
    when /#include<(.*).h>/
      #nfile.write(line + ' //inclui a biblioteca ' + $1.strip.upcase)
    when /#include <(.*).h>/
      #nfile.write(line + ' //inclui a biblioteca ' + $1.strip.upcase)
    when /\/\//
      #nfile.write(line)
    when /printf((.*));/
      nfile.write("\texibe '#{$1}' mensagem na tela")
    when /scanf((.*), &(.*));/
      nfile.write('\tcaptura a variável ' + $3.strip.gsub(')',''))
    when /if((.*))\{/
      nfile.write('\tse ' + $1.strip.upcase)
    when /main()/
      #nfile.write(line.gsub('int ', '') + ' //função principal')
    when /int main()/
      #nfile.write(line.gsub('int ', '') + ' //função principal')
    when /float (.*);/
      nfile.write('\tdeclara as variáveis como reais: ' + $1.strip)
    when /int (.*);/
      nfile.write('\tdeclara as variáveis como inteiros: ' + $1.strip)
    when /char (.*);/
      nfile.write('\tdeclara as variáveis como caracter: ' + $1.strip)
    when /char* (.*);/
      nfile.write('\tdeclara as variáveis como texto: ' + $1.strip)
    when /system("color (.*)");/
      nfile.write('\tmuda a cor da janela')
    when /system("title (.*)");/
      nfile.write('\tmuda o título da janela para "' + $1.strip + '"')
      when /system("cls");/
      nfile.write('\tlimpa a tela')
    when /getsf(((.*)))/
      nfile.write('\tcaptura texto para a variável ' + $1.strip.gsub('(',''))
    when /getch/
      nfile.write('\tespera o usuario pressionar ENTER')
    when /return((.*));/
      #nfile.write(line + ' //retorna "' + $1.strip + '"')
    when /(.*):/
      nfile.write('\tdecora posição como ' + $1.strip)
	when /goto (.*);/
      nfile.write('\tvai para a posição ' + $1.strip)
    else
      if line.downcase.include?('pause')
        nfile.write('\tespera o usuario pressionar ENTER')
	elsif line.downcase.include?('cls')
		nfile.write('\tlimpa a tela')
	elsif line.downcase.include?('color')
		nfile.write('\tmuda a cor da janela')
      else
        nfile.write(line)
      end
    end
    i += 1
    nfile.write("\n")
  }
  #nfile.write("//****Fim do arquivo\n\n")
  nfile.close
end

$MAIN_PATH  = './LP-Comentado/'
files_list = Dir.entries($MAIN_PATH)
files_list.each{|file_path| comment_file(file_path)}