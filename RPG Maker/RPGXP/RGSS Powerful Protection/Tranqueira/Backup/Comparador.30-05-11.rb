require("Win32API")

module Graphics
  def self.update
    sleep(0.025)
  end
end

puts("Meta")
before = Time.now.to_f
Marshal.load(File.open('Data/Scripts.rxdata', 'rb').readlines.to_s)
after = Time.now.to_f
puts (after - before).to_s

puts("Versao: 0.5.0")
require "Dll-Backup/Dll-Backup.28.05.11.rb"
before = Time.now.to_f
load_data('Data_Compiled/Scripts.rxdata')
after = Time.now.to_f
puts (after - before).to_s

puts("Versao: 0.5.2")
require "Dll-Backup/Dll-Backup.28.05.11-2.rb"
before = Time.now.to_f
load_data('Data_Compiled/Scripts.rxdata')
after = Time.now.to_f
puts (after - before).to_s

puts("Versao: 0.5.3")
require "Dll-Backup/Dll.29.05.11.rb"
before = Time.now.to_f
load_data('Data_Compiled/Scripts.rxdata')
after = Time.now.to_f
puts (after - before).to_s


puts("Versao: 0.6.0")
require "Dll.rb"
before = Time.now.to_f
load_data('Data_Compiled/Scripts.rxdata')
after = Time.now.to_f
puts (after - before).to_s

puts("Versao: 0.0.0")
require "Dll-Backup/Dll-RGSSPP.rb"
before = Time.now.to_f
load_data('Data_Compiled/Scripts.rxdata')
after = Time.now.to_f
puts (after - before).to_s