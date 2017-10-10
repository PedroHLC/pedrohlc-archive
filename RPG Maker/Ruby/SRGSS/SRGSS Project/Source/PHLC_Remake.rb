class Game_RPG
  def initialize
    @title = "\0" * 256 
    @scripts = "\0" * 256 
    @rtp1 = "\0" * 256 
    @rtp2 = "\0" * 256 
    @rtp3 = "\0" * 256 
    readini = Win32API.new('kernel32', 'GetPrivateProfileStringA', %w(p p p p l p), 'l')
    readini.call('Game','Title','',@title,255,".\\Game.ini")
    readini.call('Game','Scripts','',@scripts,255,".\\Game.ini")
    readini.call('Game','RTP1','',@rtp1,255,".\\Game.ini")
    readini.call('Game','RTP2','',@rtp2,255,".\\Game.ini")
    readini.call('Game','RTP3','',@rtp3,255,". \\Game.ini")
    readini = nil
    @title.delete!("\0")
    @scripts.delete!("\0")
    @rtp1.delete!("\0")
    @rtp2.delete!("\0")
    @rtp3.delete!("\0")
  end
  attr_accessor :title
  attr_accessor :scripts
  attr_accessor :rtp1
  attr_accessor :rtp2
  attr_accessor :rtp3
end
$game_rpg = Game_RPG.new

module Graphics
  @resolution_width = 640
  @resolution_height = 480
  @freeze_color = Color.new(0, 0, 0, 255)
  class << self
    
    def transition(frames=Graphics.frame_rate, bitmap="")
      return if @freezed != true
      @transition_image.bitmap = Bitmap.new(bitmap) if bitmap.to_s != ""
      for i in 0...frames
        self.update
        @transition_image.opacity = 255-((i / frames.to_f) *255)
      end
      @transition_image.dispose
      @transition_viewport.dispose
      @transition_image = @transition_viewport = nil
      @freezed = false
      return
    end
    
    def freeze
      @transition_viewport = Viewport.new(0, 0, @resolution_width, @resolution_height)
      @transition_viewport.z = 99999
      @transition_image = Sprite.new(@transition_viewport)
      @transition_image.bitmap = Bitmap.new(@resolution_width, @resolution_height)
      @transition_image.bitmap.fill_rect(0, 0, @resolution_width, @resolution_height, @freeze_color)
      @transition_image.opacity = 255
      @freezed = true
      return
    end
  end
end

class Bitmap
  alias old_initialize initialize
  alias old_dispose dispose
  def initialize(*args)
    @disposed = false
    old_initialize(*args)
  end
  def dispose
    @disposed = true
    old_dispose
  end
  def disposed?
    return @disposed
  end
end

class Rect
  def set(x,y,width,height)
    self.x = x
    self.y = y
    self.width = width
    self.height = height
  end
end

class Window
  attr_accessor :cursor_rect
  alias old_initialize initialize
  def initialize
    @cursor_rect = Rect.new(0,0,0,0)
    @cursor_rect.empty
    old_initialize
  end
end

module RPG
class Sprite
  attr_accessor :bush_depth 
  alias original_initialize initialize
  def initialize(*args)
    @bush_depth = nil
    original_initialize(*args)
  end
end
end

module PedroHLC_Scripts
  def exit
    $scene = nil
    return nil
  end
  def load_data(filename)
    file =  File.open(filename,'rb:utf-8')
    data = Marshal.load(file)
    file.close
    return data
  end
  def array2text(data)
    if data.is_a?(Array)
      final_data = '['
      for i in 0..(data.size-2)
        if data[i].is_a?(Array)
          final_data += array2text(data[i])
          final_data += ","
        elsif data[i].is_a?(String)
          final_data += "'#{data[i]}',"
        else
          final_data += "#{data[i]},"
        end
      end
      final_data += "#{data[(data.size-1)]}]"
      return final_data.to_s
    end
    return data
  end
  def print(msg)
    if msg.is_a?(Module) or msg.is_a?(Class)
      return Win32API.new('user32', 'MessageBox', 'ippi', 'i').call(0, "Module/Class: #{msg}",$game_rpg.title, 64)
    end
    if msg.is_a?(Array)
      return Win32API.new('user32', 'MessageBox', 'ippi', 'i').call(0, array2text(msg),$game_rpg.title, 64)
    end
    if msg.is_a?(String)
      return Win32API.new('user32', 'MessageBox', 'ippi', 'i').call(0, msg.to_s,$game_rpg.title, 64)
    end
    if msg == nil
      return Win32API.new('user32', 'MessageBox', 'ippi', 'i').call(0, 'nil',$game_rpg.title, 64)
    end
    return Win32API.new('user32', 'MessageBox', 'ippi', 'i').call(0, msg,$game_rpg.title, 64)
  end
end
include(PedroHLC_Scripts)