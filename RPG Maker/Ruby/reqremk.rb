#2228950

require 'Win32API'
LoadLibrary = Win32API.new('kernel32', 'LoadLibrary', 'p', 'l')
GetProcAddress = Win32API.new('kernel32', 'GetProcAddress', 'lp', 'l')

class Void
  def initialize(proc_addr)
    @proc_addr = proc_addr
  end
  def call
  end
end

def dln_load(fname)
  raise("filename too long") if fname.size > 1024
  winfile = fname.dup
  buf = winfile + "\0"
  handle = LoadLibrary.call(winfile)
  raise("failed") if handle.nil?
  raise("startfunction non existe") if((init_fct = Void.new(GetProcAddress.call(handle, buf))) == 0)
  init_fct.call
  return handle
end
dln_load('socket.so')