#===============================================================================
# Advanced Ruby Audio
# Por: PedroHLC
# Ver: 1.0
#===============================================================================
# OBS: O autor do script original é desconhecido
# A DLL tem direitos autorais para: "(C) 2008 Peter O."
# "Peter O." também é conhecido como "Poccil"
#===============================================================================
module Audio
  DLL = "Audio.dll"
 
  AUDIO_EXTENSIONS = [".mid",".mmf",".mpc",".mp3",".wma",".ogg",".wav",".acc",".ac3",".amr"]

  ACP = Win32API.new(DLL, "AudioContextPlay", "lpllll","")
  LOOPPLAY = Win32API.new(DLL, "AudioContextSEPlay", "lpllll","")
  STOP = Win32API.new(DLL, "AudioContextStop", "l", "")
  FADE_OUT = Win32API.new(DLL, "AudioContextFadeOut", "ll","")
  FADE_IN = Win32API.new(DLL, "AudioContextFadeOut", "ll","")
  POSITION = Win32API.new(DLL,"AudioContextGetPosition","l","l")
  FREE = Win32API.new(DLL,"AudioContextFree", 'l', '')
  VOLUME = Win32API.new(DLL,"AudioContextGetVolume","l","l")
  INIALIZE = Win32API.new(DLL, "AudioContextInitialize", '', 'l')
  ISACTIVE = Win32API.new(DLL, "AudioContextIsActive", 'l', 'l')
  SETPOSTION = Win32API.new(DLL, "AudioContextSetPosition", 'll', '')
  SETVOLUME = Win32API.new(DLL, "AudioContextSetVolume", 'll', '')
  BEEP = Win32API.new('kernel32', 'Beep', 'LL', 'I')
 
  BGM_DATA = INIALIZE.call()
  BGS_DATA = INIALIZE.call()
  ME_DATA = INIALIZE.call()
  SE_DATA = INIALIZE.call()
 
  if BGM_DATA == 0
    raise("Falha ao inicializar Audio")
  end
  if BGS_DATA == 0
    raise("Falha ao inicializar Audio")
  end
  if ME_DATA == 0
    raise("Falha ao inicializar Audio")
  end
  if SE_DATA == 0
    raise("Falha ao inicializar Audio")
  end
 
  def self.play_beep(frequency=410, duration= 800)
    BEEP.call(frequency,duration)
  end
 
  def self.bgm_play(filename="", volume=100, pitch=100)
    return if filename == ""
    if !FileTest.exist?(filename)
      file = self.get_filename(filename)
      return if !FileTest.exist?(file)
    else
      file = filename
      return if !FileTest.exist?(file)
    end
    ACP.call(BGM_DATA, file, volume, pitch, 0, 1)
  end
 
  def self.bgs_play(filename="", volume=100, pitch=100)
    return if filename == ""
    if !FileTest.exist?(filename)
      file = self.get_filename(filename)
      return if !FileTest.exist?(file)
    else
      file = filename
    end
    ACP.call(BGS_DATA, file, volume, pitch, 0, 1)
  end
 
  def self.me_play(filename="", volume=100, pitch=100)
    return if filename == ""
    if !FileTest.exist?(filename)
      file = self.get_filename(filename)
      return if !FileTest.exist?(file)
    else
      file = filename
    end
    ACP.call(ME_DATA, file, volume, pitch, 0, 1)
  end
 
  def self.se_play(filename="", volume=100, pitch=100)
    return if filename == ""
    if !FileTest.exist?(filename)
      file = self.get_filename(filename)
      return if !FileTest.exist?(file)
    else
      file = filename
    end
    LOOPPLAY.call(SE_DATA, file, volume, pitch, 0, 1)
  end
 
  def self.bgm_stop
    STOP.call(BGM_DATA)
  end
 
  def self.bgs_stop
    STOP.call(BGS_DATA)
  end
 
  def self.me_stop
    STOP.call(ME_DATA)
  end
 
  def self.se_stop
    STOP.call(SE_DATA)
  end
 
  def self.bgm_fade(time=800000)
    FADE_OUT.call(BGM_DATA,time)
  end
 
  def self.bgs_fade(time=800000)
    FADE_OUT.call(BGS_DATA,time)
  end
 
  def self.me_fade(time=800000)
    FADE_OUT.call(ME_DATA,time)
  end
 
  def self.se_fade(time=800000)
    FADE_OUT.call(SE_DATA,time)
  end
 
  def self.bgm_free
    FREE.call(BGM_DATA)
  end
 
  def self.bgs_free
    FREE.call(BGS_DATA)
  end
 
  def self.me_free
    FREE.call(ME_DATA)
  end
 
  def self.se_free
    FREE.call(SE_DATA)
  end
 
  def self.bgm_get_position
    return POSITION.call(BGM_DATA)
  end
 
  def self.bgs_get_position
    return POSITION.call(BGS_DATA)
  end
 
  def self.me_get_position
    return POSITION.call(ME_DATA)
  end
 
  def self.se_get_position
    return POSITION.call(SE_DATA)
  end
 
  def self.bgm_get_volume
    return VOLUME.call(BGM_DATA)
  end
 
  def self.bgs_get_volume
    return VOLUME.call(BGS_DATA)
  end
 
  def self.me_get_volume
    return VOLUME.call(ME_DATA)
  end
 
  def self.se_get_volume
    return VOLUME.call(SE_DATA)
  end
 
  def self.bgm_set_position(position=0)
    SETPOSTION.call(BGM_DATA, position)
  end
 
  def self.bgs_set_position(position=0)
    SETPOSTION.call(BGS_DATA, position)
  end
 
  def self.me_set_position(position=0)
    SETPOSTION.call(ME_DATA, position)
  end
 
  def self.se_set_position(position=0)
    SETPOSTION.call(SE_DATA, position)
  end
 
  def self.bgm_set_volume(volume=100)
    SETVOLUME.call(BGM_DATA, volume)
  end
 
  def self.bgs_set_volume(volume=100)
    SETVOLUME.call(BGS_DATA, volume)
  end
 
  def self.me_set_volume(volume=100)
    SETVOLUME.call(ME_DATA, volume)
  end
 
  def self.se_set_volume(volume=100)
    SETVOLUME.call(SE_DATA, volume)
  end
 
  def self.get_filename(filename)
    return get_extension('./'+filename.to_s)
  end
  
  def self.get_extension(filename)
    for i in 0..(AUDIO_EXTENSIONS.size - 1)
      path = filename + AUDIO_EXTENSIONS[i]
      if FileTest.exist?(path)
        return path
      end
    end
    return filename
  end
end

class AudioData
  attr_reader :data
 
  def initialize
    @data = Audio::INIALIZE.call()
    if @data == 0
      raise("Falha ao inicializar Audio")
    end
  end
 
  def dispose
    if @data != 0
      Audio::FREE.call(@data)
      @data = 0
    end
  end
end