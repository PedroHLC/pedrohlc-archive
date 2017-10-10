require 'Win32API'

RT_ICON         =  3
DIFFERENCE      = 11
RT_GROUP_ICON   = RT_ICON + DIFFERENCE

NIF_MESSAGE = 1
NIF_ICON    = 2
NIF_TIP     = 4
NIM_ADD     = 0
NIM_MODIFY  = 1
NIM_DELETE  = 2


ExtractIcon  = Win32API.new('shell32',  'ExtractIcon', 'LPI', 'L')
Shell_NotifyIcon  = Win32API.new('shell32',  'Shell_NotifyIconA', 'LP', 'I')


hicoY = ExtractIcon.call(0, 'C:\WINDOWS\SYSTEM\INETCPL.CPL', 21)
hicoN = ExtractIcon.call(0, 'C:\WINDOWS\SYSTEM\INETCPL.CPL', 22)

tiptxt = 'test icon (ruby)'
pnid = [6*4+64, 0, 'ruby'.hash, NIF_ICON | NIF_TIP, 0, hicoY].pack('LLIIIL') << tiptxt << "\0"*(64 - tiptxt.size)
ret = Shell_NotifyIcon.call(NIM_ADD, pnid)
p 'Err: NIM_ADD' if ret == 0

sleep(1)   #  <----<<

pnid = [6*4+64, 0, 'ruby'.hash, NIF_ICON | NIF_TIP, 0, hicoN].pack('LLIIIL') << tiptxt << "\0"*(64 - tiptxt.size)
ret = Shell_NotifyIcon.call(NIM_MODIFY, pnid)
p 'Err: NIM_MODIFY' if ret == 0

sleep(1)   #  <----<<

pnid = [6*4+64, 0, 'ruby'.hash, 0, 0, 0].pack('LLIIIL') << "\0"
ret = Shell_NotifyIcon.call(NIM_DELETE, pnid)
p 'Err: NIM_DELETE' if ret == 0

sleep(2)

#-------------------------------------------------------------------------------