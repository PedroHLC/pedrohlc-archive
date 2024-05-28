=begin
RGSS200E )RPG Maker VX( Descompiled Data
by: PedroHLC
=end

module RPG
class AudioFile
  def initialize(name = '', volume = 100, pitch = 100)
    @name = name
    @volume = volume
    @pitch = pitch
  end
  attr_accessor :name
  attr_accessor :volume
  attr_accessor :pitch
end
class BGM < AudioFile
  @@last = BGM.new
  def play
    if @name.empty?
      Audio.bgm_stop
      @@last = BGM.new
    else
      Audio.bgm_play('Audio/BGM/' + @name, @volume, @pitch)
      @@last = self
    end
  end
  def self.stop
    Audio.bgm_stop
    @@last = BGM.new
  end
  def self.fade(time)
    Audio.bgm_fade(time)
    @@last = BGM.new
  end
  def self.last
    @@last
  end
end
class BGS < AudioFile
  @last = BGS.new
  def play
    if @name.empty?
      Audio.bgs_stop
      @@last = BGS.new
    else
      Audio.bgs_play('Audio/BGS/' + @name, @volume, @pitch)
      @@last = self
    end
  end
  def self.stop
    Audio.bgs_stop
    @@last = BGS.new
  end
  def self.fade(time)
    Audio.bgs_fade(time)
    @@last = BGS.new
  end
  def self.last
    @@last
  end
end
class ME < AudioFile
  def play
    if @name.empty?
      Audio.me_stop
    else
      Audio.me_play('Audio/ME/' + @name, @volume, @pitch)
    end
  end
  def self.fade(time)
    Audio.me_fade(time)
  end
  def self.stop
    Audio.me_stop
  end
end
class SE < AudioFile
  def play
    unless @name.empty?
      Audio.se_play('Audio/SE/' + @name, @volume, @pitch)
    end
  end
  def self.stop
    Audio.se_stop
  end
end
end