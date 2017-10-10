require "Win32API"
require "win32ole"

#$swp = Win32API.new('user32', 'SetWindowPos', 'LLIIIIL', 'I') 
#$gfw = Win32API.new('user32', 'GetForegroundWindow', '', 'L')
#$main_wid = $gfw.call
#$swp.call($main_wid, 0, 0, 0, 0, 0, 0x0080)

$wmi = WIN32OLE.connect("winmgmts://")

  processes = $wmi.ExecQuery("select * from win32_process")
  for process in processes
    puts "Name: #{process.Name}"
    puts "CommandLine: #{process.CommandLine}"
    puts "CreationDate: #{process.CreationDate}"
    puts "WorkingSetSize: #{process.WorkingSetSize}"
    puts
    gets
  end