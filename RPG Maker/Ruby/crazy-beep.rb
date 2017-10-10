puts "#By PedroHLC"
require "Win32API"
module Beep_Melody
  def self.loosing_sound
    for i in 0..2
      a = 1800
      b = 120
      Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
      sleep(0.1 * (b / 100))
      a = 1700     
      b = 120
      Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
      sleep(0.1 * (b / 100))
      a = 1600
      b = 120
      Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
      sleep(0.1 * (b / 100))
      a = 1500
      b = 120
      Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
      sleep(0.1 * (b / 100))
    end
    a = 1500
    b = 120
    Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
    sleep(0.1 * (b / 100))
    a = 1400     
    b = 120
    Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
    sleep(0.1 * (b / 100))
    a = 1300
    b = 120
    Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
    sleep(0.1 * (b / 100))
    a = 1200
    b = 120
    Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
    sleep(0.1 * (b / 100))
    a = 800
    b = 200
    Win32API.new('kernel32', 'Beep', 'LL', 'I').call(a,b)
  end
end
Beep_Melody.loosing_sound