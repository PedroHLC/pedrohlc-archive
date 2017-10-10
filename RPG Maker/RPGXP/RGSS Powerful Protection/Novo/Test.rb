require("Win32API")

require "Dll.rb"
before = Time.now.to_f
load_data('Data_Compiled/Scripts.rxdata')
after = Time.now.to_f
puts (after - before).to_s