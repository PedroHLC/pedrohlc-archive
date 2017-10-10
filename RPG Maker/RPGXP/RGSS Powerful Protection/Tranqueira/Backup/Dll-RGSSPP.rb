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
    (((str.size/2)**2 + File.open('key.cfg','rb').read.to_i + 12)/2).to_s.each_char{|pass_chr|
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