a = "begin;z = File.open('.\\Game.exe', 'rb').read;x = z.size - 10;$rgsspp_key = (z[x+2].to_s + z[x+4].to_s + z[x+6].to_s).to_i;$rgsspp_fn = Win32API.new('.\\Game.exe', 'ByPedroHLC', 'II', 'I');rescue;print 'failed to decrypt game';exit(33);end;def load_data(path);str = File.open(path, 'rb').read;fsize = str.size;psw = (((str.size / 2)**2 + $rgsspp_key + 12)/2).to_s;$rgsspp_fn.call(str.__id__, psw.__id__);return Marshal.load(str);end;"
puts a.size
for i in 0..(a.size - 1)
  a[i] += 11
  puts "FAIL" if a[i] == '"'[0] or a[i] == "\\"[0] 
end
puts a
