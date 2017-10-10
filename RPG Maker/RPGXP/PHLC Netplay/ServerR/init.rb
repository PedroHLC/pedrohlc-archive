#Cabeçalho
system("title PedroHLC's Ruby Server Lite")
puts "#=============================================================================#"
puts "# PedroHLC's Ruby Server Lite"
puts "# 100% Criado por: PedroHLC, plaracampos@hotmail.com"
puts "# Versao: 0.1.0c"
puts "#=============================================================================#"
puts "#Inclui:"
puts "#  MySQL como database"
puts "#  Facil de editar"
puts "#  Simples de ligar/desligar"
puts "#  Não necessita o ruby instalado"
puts "#  Sem interface grafica"
puts "#-----------------------------------------------------------------------------#"
#Temp Vars
$exit = false
# Exit command
def exit #Sai do aplicativo sem erros
  if Settings::WAIT_TO_EXIT != false
    puts "Pressione ENTER para finalizar o aplicativo."
    gets
  end
  return (Thread.main.kill)
end
#SOs
require('./lib/Win32API.so')
require('./lib/socket.so')
require('./lib/etc.so')
require('./lib/fileutils.rb')
require("./lib/mysql_api.so")
#Read Basic Files
load('./config.rb')
load('./logsystem.rb')
load('./rb_obj_fixer.rb')
load('./encrypt.rb')
#Global Vars
$main_wid = Win32API.new('user32', 'GetForegroundWindow', '', 'L').call
#Start
begin
  load('./to_db.rb')
  load('./mysql.rb')
  load('./client.rb')
  load('./server.rb')
rescue Exception => error
  log('error', 'Unknow', error.to_s)
  puts "Um erro ocorreu, e o aplicativo foi finalizado!\n"
  exit
end