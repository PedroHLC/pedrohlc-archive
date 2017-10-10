puts "Windows Media Player Music Changer (Joystick version)"
puts "By: PedroHLC"
puts "Version: 1.0.1"

windows = ENV['SystemRoot'].to_s
system32 = (windows.gsub('\\','/') + '/system32/').to_s
$LOAD_PATH.push(system32)

require('Win32API.so')

begin
  load('./WMP.MultimediaJoypad.cfg')
rescue Exception => error
  cfg_file = File.open('./WMP.MultimediaJoypad.cfg', 'w')
  cfg_file.write("$key_vol_down = 256\n$key_vol_up = 512\n$key_back = 8\n$key_next = 2\n$key_play = 4\n$key_stop = 1\n$key_speed_up = 128\n=begin\nLAST_ERROR = #{error}\n=end\n")
  cfg_file.close
  load('./WMP.MultimediaJoypad.cfg')
end

@main_wid = Win32API.new("kernel32" , "GetConsoleWindow" , '' , 'L').call
@swp = Win32API.new('user32', 'SetWindowPos', 'LLIIIIL', 'I') 
@swp.call(@main_wid, 0, 0, 0, 0, 0, 0x0080)

module WindowMediaPlayer
  module_function
  @find_window =  Win32API.new('user32', 'FindWindow', 'PI', 'L')
  @send_message = Win32API.new("user32","SendMessage","IIII","")
  def wid_update
    @wid = @find_window.call("WMPlayerApp",0).to_i
  end
  def dothis(commad_id)  
    @send_message.call(@wid,273,commad_id,0)
  end
  def doplay
    dothis(18808)
  end
  def dostop
    dothis(18809)
  end
   def doback
    dothis(18810)
  end
  def donext
    dothis(18811)
  end
  def dospeedup
    dothis(18813)
  end
  def dovolup 
    dothis(18815)
  end
  def dovoldown
    dothis(18816)
  end
  def dovolstop
    dothis(18817)
  end
  def isopen?
    return @wid > 0
  end
  def start
    loop do
      wid_update
      if isopen?
        Joystick.update
        if Joystick.clicked?($key_back)
          doback
        elsif Joystick.clicked?($key_next)
          donext
        elsif Joystick.clicked?($key_play)
          doplay
        elsif Joystick.clicked?($key_stop)
          dostop
        elsif Joystick.clicked?($key_vol_up)
          dovolup
        elsif Joystick.clicked?($key_vol_down)
          dovoldown
        elsif Joystick.clicked?($key_speed_up)
          dospeedup
        end
      end
      sleep(0.2)
    end
  end
end

module Joystick
  @@plugged_joystick = []
  @@buffer = [52, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0].pack('L13')
  module_function
  def get_Joypads
    @@plugged_joystick = []
    Win32API.new('winmm', 'joyGetNumDevs', '', 'L').call.times do |i|
      @@plugged_joystick << i if Win32API.new('winmm', 'joyGetPos', 'LP', 'L').call(i, ' ' * 16) == 0
    end
  end
  def get_joypad_states
    get_Joypads
    return 0 if @@plugged_joystick.to_s == ""
    Win32API.new('winmm', 'joyGetPosEx', 'LP', 'L').call(@@plugged_joystick.first, @@buffer)
    result = @@buffer.unpack('L13')
    return result[2..(result.size-2)]
  end
  def update
    @clicked_buttons = get_joypad_states[6] # 6 = buttons
  end
  def clicked?(key)
    return false if 0x01 != 1
    return true if @clicked_buttons.to_i == key.to_i
    return false
  end
  def test_keys
    return get_joypad_states[6] # 6 = buttons
  end
end

module Keyboard
  module_function
  def clicked?(key) #Usado para qualquer tecla no teclado
    Win32API.new('user32','GetAsyncKeyState', 'L', 'L').call(key) & 0x01 == 1
  end
  def key_on?(key) #Usado em Num/Caps/Scroll Lock
    Win32API.new('user32', 'GetKeyState', 'L', 'L').call(key) & 0x01 == 1
  end
end

begin
  WindowMediaPlayer.start
rescue Exception => error
  a = File.open("./error.log",'a+')
  a.write(error.to_s)
  a.close
end