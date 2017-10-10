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
      str[i] -= pass_chr[0]
      i += 1
      break if str[i] == nil
    }
    break if str[i] == nil
  end
  return str.to_s
end
def load_data(path)
  file = File.open(path, 'rb')
  data = file.readlines.to_s
  file.close
  return Marshal.load(rgssp_desencrypt(data))
end