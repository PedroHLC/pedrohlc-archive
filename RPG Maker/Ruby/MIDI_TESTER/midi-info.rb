$DELTA_TIMES = {
  0x7F => 127,
  0x81 => 127, 
  0x7F => 255,
  0x82 => 255,
  0x80 => 255,
  0x00 => 32768
};

class String
  def clean_nul
    self.delete!(0.chr)
    return self
  end
  def h2i
    x = 0
    for i in 0..(self.size - 1)
      x += self[i]
    end
    puts x
    return x
  end
end

class MidiTrackEvent
  def initialize(data)
    x = data[0]
    if x == 0xFF.chr
      @type = 0
      @meta_type = [1]
      @v_lenght = [2..5]
    elsif x == 0xF0.chr or x == 0xF7.chr
      @type = 1
      #fim = 0xF7.chr
    end
  end
end

class MidiInfo
  attr_reader('file_lenght', 'format', 'n', 'division', 'track_event', 'extra_data')
  def initialize(file_path)
    @file_lenght = File.size(file_path)
    file = File.open(file_path, 'rb')
    #Header Chunk
    return -1 if  file.read(4) != "MThd"
    header_length = file.read(4).h2i
    @format = file.read(2).h2i
    @n = file.read(2).h2i
    @division = file.read(2).h2i
    #Track Chunk
    @track_event = []
    for i in 0..(@n - 1)
      return -2 unless file.read(4) == "MTrk"
      track_lenght = file.read(4).h2i
      @track_event[i] = MidiTrackEvent.new(file.read(track_lenght))
    end
    @extra_data = file.read
    file.close
  end
end

mid_test = MidiInfo.new('teste.mid')
case mid_test
  when -1
    puts '-1'
  when -2
    puts '-2'
  when -3
    puts '-3'
  else
    puts 'OK!'
    puts "File Lenght: #{mid_test.file_lenght}"
    puts "Format: #{mid_test.format}"
    puts "Track Numbers: #{mid_test.n}"
    puts "Division: #{mid_test.division}"
    total_size = mid_test.file_lenght.to_s.size + mid_test.format.to_s.size + mid_test.n.to_s.size + mid_test.division.to_s.size + mid_test.track_event.to_s.size + mid_test.extra_data.to_s.size
    puts "Total Size: #{total_size}"
end