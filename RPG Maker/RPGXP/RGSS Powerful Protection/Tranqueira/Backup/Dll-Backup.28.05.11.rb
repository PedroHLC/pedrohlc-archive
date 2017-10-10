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
def load_data(path)
  file = File.open(path, 'rb')
  data = file.readlines.to_s
  file.close
  i = 0
  while i <= (data.size - 1)
    (((data.size/2)**2 + File.open('key.cfg','rb').read.to_i + 12)/2).to_s.each_char{|pass_chr|
      Graphics.update if i % 100000 == 0
      data[i] -= pass_chr[0]
      i += 1
      break if data[i] == nil
    }
    break if data[i] == nil
  end
  return Marshal.load(data)
end