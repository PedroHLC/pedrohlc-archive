#Cabeçalho
system("title PedroHLC's Ruby Server Lite")
puts "#=============================================================================#"
puts "# PedroHLC's Ruby Server Lite"
puts "# 100% Criado por: PedroHLC, pedrohlc@hotmail.com.br"
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
#Gems
require('./lib/Win32API.so')
require('./lib/socket.so')
require('./lib/etc.so')
require('./lib/fileutils.rb')
require("./lib/mysql_api.so")
#Read Basic Files
load('./config.rb')
load('./rubyedit.rb')
load('./logsystem.rb')
#Start
begin
  load('./mysql.rb')
  load('./client.rb')
  load('./server.rb')
rescue Exception => error
  log('error', 'Unknow', error.to_s)
  puts "Um erro ocorreu, e o aplicativo foi finalizado!\n"
  exit
end