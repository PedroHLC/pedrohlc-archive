class String
  def each_char
    if block_given?
      scan(/./m) do |x|
        yield x
      end
    else
      scan(/./m)
    end
  end
end
def rgssp_desencrypt(str)
  i = 0
  while i <= (str.size - 1)
    (((str.size/2)**2 + 135689)/2).to_s.each_char{|pass_chr|
      Graphics.update if i % 100000 == 0
      new_ascii = str[i] - pass_chr[0]
      new_ascii += 256 if new_ascii < 0
      str[i] = new_ascii
      i += 1
      break if str[i] == nil
    }
    break if str[i] == nil
  end
  return str.to_s
end
def load_data(path)
  file = File.open(path, 'rb').readlines.to_s
  return file if path.to_s.downcase.include?('prescripts')
  if file[0] != 4
    return Marshal.load(rgssp_desencrypt(file))
  else
    return Marshal.load(file)
  end
end
def load_rgss_scripts(scripts_fname='Data/Scripts.rvdata')
  $game_loading = Sprite.new
  $game_loading.bitmap = Bitmap.new(544,416)
  cx = $game_loading.bitmap.text_size('Loading...').width
  $game_loading.bitmap.draw_text(272 - (cx / 2), 192, cx, 32, 'Loading...', 2)
  begin
    $PRE_SCRIPTS = Marshal.load(rgssp_desencrypt(File.open('Data/PreScripts.rvdata', 'rb').readlines.to_s))
    $PRE_SCRIPTS.each { |s| eval(Zlib::Inflate.inflate(s[2])) }
    $RGSS_SCRIPTS = load_data(scripts_fname)
    $RGSS_SCRIPTS.each { |s| s[3,0] = Zlib::Inflate.inflate(s[2]) }
    $RGSS_SCRIPTS.size
  rescue Exception => error
    log = File.open('ErrorLog.txt','a+')
    log.write(error.to_s)
    log.write("\n")
    log.close
  end
end