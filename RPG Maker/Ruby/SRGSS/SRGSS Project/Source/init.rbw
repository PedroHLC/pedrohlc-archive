# encoding: utf-8
require './Win32API.rb'
def exit
  return 0
end
begin
  $KCODE = "UTF-8"
  #load required ruby files
  require "./zlib.so"
  require "./socket.so"
  require "./freergss.so"
  #load required remakes scripts
  require "./RPG.rb"
  require "./Tilemap.rb"
  require "./Audio.rb"
  require "./PHLC_Remake.rb"
  require "./cursor.rb"
  #some configs
  Graphics.resize_screen(640,480)
  Graphics.frame_rate = 50 # like SNES
  $DEBUG = ''
  #laod game script
  $RGSS_SCRIPTS = load_data($game_rpg.scripts)
  #run game scripts
  $RGSS_SCRIPTS.each_with_index{|script,index|
    begin
      zstream = Zlib::Inflate.new
      script = zstream.inflate(script[2].to_s).to_s
      eval(script)
    rescue Exception => error
      if $scene != nil
        print("Erro na scene #{$scene}: #{error}")
      else
        print("Erro no script #{script[1]}(#{index}): #{error}")
      end
      logfile = File.open("log.txt","a+")
      logfile.write("#{Time.now.to_s}:\n#{error.to_s}\n#{error.backtrace.inspect}\n\n")
      logfile.close
      exit
      break
    end
  }
  #end game
  exit
rescue Exception => error
  if error.to_s != 'exit'
    result = Win32API.new('user32', 'MessageBox', 'ippi', 'i').call(0, "#{error}","Error Log", 64)
    file = File.open("./srgss-errorlog.txt", "a+")
    file.write("#{Time.now.to_s}:\n#{error.to_s}\n#{error.backtrace.inspect}\n\n")
    file.close()
  end
end