# Sistema para vrificar as teclas pressionadas por um Joypad
# criado por PedroHLC

require "Win32API"

module Joystick
  KEY_1 = 1 #Triangulo
  KEY_2 = 2 #Bola
  KEY_3 = 4 #X
  KEY_4 = 8 #Quadrado
  KEY_5 = 16 #L2
  KEY_6 = 32 #R2
  KEY_7 = 64 #L1
  KEY_8 = 128 #R1
  KEY_9 = 256 #Select
  KEY_10 = 512 #Start
  KEY_11 = 1024 #L3
  KEY_12 = 2048 #R3
  
  @plugged_joystick = []
  @keys = [0]
  @buffer = [52, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0].pack('L13')
  module_function
  
  def get_joypads
    @plugged_joystick = []
    Win32API.new('winmm', 'joyGetNumDevs', '', 'L').call.times do |i|
      @plugged_joystick << i if Win32API.new('winmm', 'joyGetPos', 'LP', 'L').call(i, ' ' * 16) == 0
    end
  end
  
  def update
    get_joypads if @plugged_joystick[1] == nil
    Win32API.new('winmm', 'joyGetPosEx', 'LP', 'L').call(@plugged_joystick.first, @buffer)
    result = @buffer.unpack('L13')
    @keys = (result[2..(result.size-2)])[6]
  end
  
  def clicked?(key)
    return false if 0x01 != 1
    key = ([key]) if !key.is_a?(Array)
    for i in 0..(key.size-1)
      return true if @keys.to_s.strip == key[i].to_s
    end
    return false
  end
  
  def multi_clicked(key_array)
    key = 0
    for i in 0..(key_array.size - 1)
      key += key_array[i].to_i
    end
    return clicked?(key)
  end
  
  def test_keys
    return @keys
  end
end

Joystick.get_joypads

loop do
  Joystick.update
  temp = Joystick.test_keys
  puts temp if temp.to_i > 0
end