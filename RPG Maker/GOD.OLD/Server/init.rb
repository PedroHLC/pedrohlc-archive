#===============================================================================================#
# PedroHLC's Ruby Server
# By: Pedro Henrique Lara Campos (PedroHLC, plaracampos@hotmail.com)
# Version: 1.0a
# 
# Special Thanks for HugoLnx(HugoLinux)
#===============================================================================================#
# Include:
#  In a easy interface yo can use :
#  MySQL
#  Simple Socket Messages
#  Easy Edit Configs
#  Turn On/Off Server, easy
#------------------------------------------------------------------------------------------------------------------#
$log = {}
$log['error'] = "./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/ERROR.txt"
$log['socket'] = "./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/SOCKET.txt"
$log['messages'] = "./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/MSGLOG.txt"
$log['server'] = "./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/SERVER.txt"
$log['neo_puts'] = "./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/PUTS.txt"
$log['chat'] = "./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/CHAT.txt"
require 'fileutils'
FileUtils.mkdir("./Debug") if !FileTest.exist?("./Debug")
FileUtils.mkdir("./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/") if !FileTest.exist?("./Debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/")
begin
  #Lê todas as informações necessarias
  require 'gtk2'
  require 'I18n'
  require 'socket'
  require 'Win32API'
  require './mysql_api.so'
  load './Ruby-mod.rb'
  #load './Encryption.rb'
  load "./Config.cfg"
  load './Client_Regular.rb'
  load './Client_Event.rb'
  load './Server.rb'
  #Cria algumas funções necessarias 
  $debug_text = ""
  def neo_puts(value)
    $debug_text += value.to_s
    puts value
  end
  #Cria a janela principal
  load './MainWindow.rb'
  #Inicializa a janela principal
  Gtk.init
  I18n.load_path = Dir['./languages.yml']
  I18n.default_locale = eval(":"+$LANGUAGE.to_s)
  $window = MainWindow.new
  Gtk.main
rescue Exception => error
  file = File.open($log['server'], "a+")
  file.write("#{Time.now.to_s}:\n #{error.to_s}\n #{error.backtrace.inspect }\n\n")
  file.close()
end