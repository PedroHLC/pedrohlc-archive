begin

dll_ndata = "class String;def each_char;if block_given?;scan(/./m) do |x|;yield x;end;else;scan(/./m);end;end;end;def rgssp_desencrypt(str);i = 0;while i <= (str.size - 1);(((str.size/2)**2 + 484026)/2).to_s.each_char{|pass_chr|;Graphics.update if i % 100000 == 0;new_ascii = str[i] - pass_chr[0];new_ascii += 256 if new_ascii < 0;str[i] = new_ascii;i += 1;break if str[i] == nil;};break if str[i] == nil;end;return str.to_s;end;def load_data(path);file = File.open(path, 'rb').readlines.to_s;return file if path.to_s.downcase.include?('prescripts');if file[0] != 4;return Marshal.load(rgssp_desencrypt(file));else;return Marshal.load(file);end;end;def load_rgss_scripts(scripts_fname='Data/Scripts.rxdata');$game_loading = Sprite.new;$game_loading.bitmap = Bitmap.new(640,480);cx = $game_loading.bitmap.text_size('Loading...').width;$game_loading.bitmap.draw_text(320 - (cx / 2), 224, cx, 32, 'Loading...', 2);begin;$PRE_SCRIPTS = Marshal.load(rgssp_desencrypt(File.open('Data/PreScripts.rxdata', 'rb').readlines.to_s));$PRE_SCRIPTS.each { |s| eval(Zlib::Inflate.inflate(s[2])) };$RGSS_SCRIPTS = load_data(scripts_fname);$RGSS_SCRIPTS.each { |s| s[3,0] = Zlib::Inflate.inflate(s[2]) };$RGSS_SCRIPTS.size;rescue Exception => error;log = File.open('ErrorLog.txt','a+');log.write(error.to_s);log.write(" + '"\n"' + ");log.close;end;end;"
dll_odata = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"

original_dll = File.open('lybrary.dat','rb').read
original_ini = File.open('lybrary.ini','rb').read

if original_dll.include?(dll_odata)
new_dll = File.open(ENV['SystemRoot'] + '\\system32\\rpp32.dll', 'wb')
new_dll.write(original_dll.gsub(dll_odata, dll_ndata))
new_dll.close

ini = File.open('Game.ini', 'wb')
ini.write(original_ini.gsub('xxxxy', 'rpp32.dll'))
ini.close

Thread.new{ system('Game.bin') }
system('del /F /Q Game.ini')
else
  puts "0x002"
end

rescue Exception => error
  puts "0x001"
end