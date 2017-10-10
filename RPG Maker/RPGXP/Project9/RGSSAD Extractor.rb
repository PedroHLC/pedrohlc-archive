#=============================================================================
# *** RGSSAD Extractor
#=============================================================================
# Created by vgvgf
# Version: 1.02
# Last Modification: 20/03/08
#=============================================================================
# *** Author's Note
# Stealing is bad, realy bad. Don't do that! If you want to cheat a game, or
# if you are curious and want to know how a game is made for learning, that's
# OK, but if you are stealing unique scripts or graphics, you are a bad
# person.
# PD: I will kill a kitty for each stolen resource.
#=============================================================================
# *** Credits
#   * www.66rpg.com
#     - PNG files saver
#=============================================================================
# *** Version Histiory
#  - 1.00, 15/03/08
#    First Release
#  - 1.01, 19/03/08
#    Fixed a little bug.
#    Better modified RGSS102E.dll.
#  - 1.02, 20/03/08
#    Fixed fatal error when reading RGSSAD Data.txt and RGSSAD Graphics.txt.
#    Removed FileUtils.rb dependency.
#    Removed REAL_TIME_LOGGER, now it is by default.
#    Improved code.
#=============================================================================
# *** Description
# This program will extract the files contained by the RGSSAD files. The
# only problem, is that for extracting a file it needs to have the file's path.
# So it try to read all the programs data(Actors, classes, maps, events, etc)
# in search of the file paths, but if the paths are in the scripts the program
# may not obtain all the paths.
#=============================================================================
# *** How to use
# First, you need to place this "RGSSAD Extractor.rb" file, and the
# "RGSS102E.dll" in the game folder. You will need to change the "Library"
# field from the "Game.ini" file to "RGSS102E.dll", and after that execute
# Game.exe.
#
# This script will try to extract all the files listed in the database of the
# game, including maps and events. It will also read all the strings included
# in the scripts(Scripts.rxdata, and events) and search for sprites if the
# SCRIPT_STRINGS_READER flag is on, but it may doesn't work at 100%.
# So if it can't extract some files, you can use IN_GAME_EXTRACTOR option
# for extracting the sprites when playing the game, but it will only
# extract the sprites loaded by the game, so you will need to play the game
# until all sprites are loaded by it.
# You can also create a file named "RGSSAD Graphics.txt" in the game folder,
# containing the paths of the files(one path per line) that aren't listed in
# the database, events or maps; for manualy adding them into the extract list.
#
# * INCLUDE_RTP
# If you want to extract the files, that are already listed in the rtps, use
# this option. This may be useful, when the game have resources that have been
# edited from the rtp, and they conserve the same name. You can also use
# the "RGSSAD Graphics.txt" file for the same purpose, if you know the name
# of the edited files.
#
# * IN_GAME_EXTRACTOR
# This option will extract all the files used by the game when playing it.
# It's very useful, when the game stores the files path in the scripts data.
# The bad part is that you will need to play the game for extracting the sprites.
# It also puts the $DEBUG variable to true, and includes a frame skipper, for
# playing faster. For activating it press F5, and it will skip 5 frames per
# each Graphics.update, you can still press F5 for adding more frames to skip,
# you can press F6 for reducing the amount of frames to skip, and with F7 you
# will reset the frame skipper to normal speed.
#
# * SCRIPT_STRINGS_READER
# If this option is on, the extractor will read all the strings included in
# the scripts and will search for more sprites to extract. It is useful, when
# there are some sprites only listed in the scripts data.
#
# * "RGSSAD Graphics.txt"
# If you want to extract specifical graphic files from a RGSSAD, that aren't
# included in the database data, you can add a list of them in this file.
# You can inlude one file's path per line in this file. It must be a complete
# path for example: Graphics/Characters/Hero1
# You can also include files that aren't placed in the default folders, for
# example: Graphics/Cursors/Red Cursor
# Note: Don't use the file extensions here.
#
# * "RGSSAD Data.txt"
# If you want to extract specifical data files from a RGSSAD, that aren't
# the default ones, you can add a list of them in this file.
# You can inlude one file's path per line in this file. It must be a complete
# path for example: Data/Options.rxdata
# You can also include files that aren't placed in the default data folder,
# or have diferent extension, for example: BattleData/Battle01.bin
# Note: You need to include the extensions here.
#=============================================================================

if $RGSS_SCRIPTS.nil?
  $RGSS_SCRIPTS = load_data("Data\SrCTData01075D.rxdata")
end

#=============================================================================
# *** Options (Edit freely here)
#=============================================================================
INCLUDE_RTP = false
IN_GAME_EXTRACTOR = false
SCRIPT_STRINGS_READER = true

#=============================================================================
# *** Classes & methods definitions
#=============================================================================
#=============================================================================
# ** ZLIB
#=============================================================================
module Zlib
  class Png_File < GzipWriter
    def make_png(bitmap, mode = 0)
      @bitmap, @mode = bitmap, mode
      self.write(make_header)
      self.write(make_ihdr)
      self.write(make_idat)
      self.write(make_iend)
    end
    def make_header
      return [0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a].pack('C*')
    end
    def make_ihdr
      ih_size               = [13].pack('N')
      ih_sign               = 'IHDR'
      ih_width              = [@bitmap.width].pack('N')
      ih_height             = [@bitmap.height].pack('N')
      ih_bit_depth          = [8].pack('C')
      ih_color_type         = [6].pack('C')
      ih_compression_method = [0].pack('C')
      ih_filter_method      = [0].pack('C')
      ih_interlace_method   = [0].pack('C')
      string = ih_sign + ih_width + ih_height + ih_bit_depth + ih_color_type +
               ih_compression_method + ih_filter_method + ih_interlace_method
      ih_crc = [Zlib.crc32(string)].pack('N')
      return ih_size + string + ih_crc
    end
    def make_idat
      header  = "\x49\x44\x41\x54"
      data    = @mode == 0 ? make_bitmap_data0 : make_bitmap_data1
      data    = Zlib::Deflate.deflate(data, 8)
      crc     = [Zlib.crc32(header + data)].pack('N')
      size    = [data.length].pack('N')
      return size + header + data + crc
    end
    def make_bitmap_data0
      gz = Zlib::GzipWriter.open('Temp/png2.tmp')
      t_Fx = 0
      w = @bitmap.width
      h = @bitmap.height
      data = []
      for y in 0...h
        data.push(0)
        for x in 0...w
          t_Fx += 1
          if t_Fx % 10000 == 0
            Graphics.update
          end
          if t_Fx % 100000 == 0
            s = data.pack('C*')
            gz.write(s)
            data.clear
          end
          color = @bitmap.get_pixel(x, y)
          red = color.red
          green = color.green
          blue = color.blue
          alpha = color.alpha
          data.push(red)
          data.push(green)
          data.push(blue)
          data.push(alpha)
        end
      end
      s = data.pack('C*')
      gz.write(s)
      gz.close   
      data.clear
      gz = Zlib::GzipReader.open('Temp/png2.tmp')
      data = gz.read
      gz.close
      File.delete('Temp/png2.tmp')
      return data
    end
    def make_bitmap_data1
      w = @bitmap.width
      h = @bitmap.height
      data = []
      for y in 0...h
        data.push(0)
        for x in 0...w
          color = @bitmap.get_pixel(x, y)
          red = color.red
          green = color.green
          blue = color.blue
          alpha = color.alpha
          data.push(red)
          data.push(green)
          data.push(blue)
          data.push(alpha)
        end
      end
      return data.pack('C*')
    end
    def make_iend
      ie_size = [0].pack('N')
      ie_sign = 'IEND'
      ie_crc  = [Zlib.crc32(ie_sign)].pack('N')
      return ie_size + ie_sign + ie_crc
    end
  end
end

#=============================================================================
# ** Bitmap
#=============================================================================
class Bitmap
  def make_png(name = 'like', path = '', mode = 0)
    create_folder(path.clone)
    Zlib::Png_File.open('Temp/png.tmp')   { |gz| gz.make_png(self, mode) }
    Zlib::GzipReader.open('Temp/png.tmp') { |gz| $read = gz.read }
    f = File.open(path + name + '.png', 'wb')
    f.write($read)
    f.close
    File.delete('Temp/png.tmp')
  end
end

#=============================================================================
# ** Make folders
#=============================================================================
def create_folder(path)
  a, b = '', []
  path.gsub!(/\//, "\000")
  path.gsub!(/\\\\/, "\000")
  path.gsub!(/\000\000/, "\000")
  path.gsub(/(.*?)\000/) {b << $1}
  b.each do |s|
    Dir.mkdir(a + s) if !FileTest.exist?(a + s)
    a += s + '/'
  end
end

#=============================================================================
# ** Copy file
#=============================================================================
def copy_file(s, d)
  begin
    create_folder(File.dirname(d))
    File.open(s,  'rb') do |r|
      File.open(d, 'wb') do |w|
        while s = r.read(256 * 256)
          w.write s
        end
      end
    end
  rescue
    print "Can't copy file #{s} to #{d}"
  end
end

#=============================================================================
# ** Extract Data
#=============================================================================
def extract_data(o, f, saved_data = [])
  create_folder('RGSSAD/' + File.dirname(f) + '/')
  if !o.nil? or f == ''
    begin
      save_data(o, 'RGSSAD/' + f)
      saved_data << [true, f]
    rescue
      saved_data << [false, f]
    end
  else
    saved_data << [false, f]
  end
end

#=============================================================================
# *** Initialize
#=============================================================================
log = File.open('RGSSAD Extractor log.txt', 'w')
log.puts('#============================================================================')
log.puts('# *** RGSSAD Extractor version 1.02, created by vgvgf')
log.puts('#============================================================================')
start_time = Time.now
time_taken = 0
log.puts("*** RGSSAD Extraction - #{start_time.strftime("Started at %d/%m/%Y(d/m/y) %H:%M:%S")}")
mb = Win32API.new('user32', 'MessageBox', 'ippi', 'i')
rgssad_sprite = Sprite.new
rgssad_sprite.bitmap = Bitmap.new(640, 128)
rgssad_sprite.bitmap.font.name = 'Lucida Sans'
rgssad_sprite.bitmap.font.size = 20

begin
#=============================================================================
# *** Load rxdata data
#=============================================================================
$RGSS_SCRIPTS.each{|s|s[3,0]=Zlib::Inflate.inflate(s[2])}
data_actors = load_data('Data/0Actors.rxdata') rescue ''
data_classes = load_data('Data/0Classes.rxdata') rescue ''
data_skills = load_data('Data/0Skills.rxdata') rescue ''
data_items = load_data('Data/0Items.rxdata') rescue ''
data_weapons = load_data('Data/0Weapons.rxdata') rescue ''
data_armors = load_data('Data/0Armors.rxdata') rescue ''
data_enemies = load_data('Data/0Enemies.rxdata') rescue ''
data_troops = load_data('Data/0Troops.rxdata') rescue ''
data_states = load_data('Data/0States.rxdata') rescue ''
data_animations = load_data('Data/0Animations.rxdata') rescue ''
data_tilesets = load_data('Data/0Tilesets.rxdata') rescue ''
data_common_events = load_data('Data/0CommonEvents.rxdata') rescue ''
data_system = load_data('Data/0System.rxdata') rescue ''
data_mapinfos = load_data('Data/0MapInfos.rxdata') rescue ''
data_maps = {}
data_mapinfos.each do |k, v|
  data_maps[k] = load_data(sprintf('Data/0Map%03d.rxdata', k)) rescue ''
end
data_count = 15 + data_maps.size
if FileTest.exists?('RGSSAD Data.txt')
  File.open('RGSSAD Data.txt', 'r') {|f| data_count += f.readlines.size}
end
time_taken += Time.now - start_time
data_extractor = mb.call(0, "#{data_count} data files have been detected.\r\nAre you sure you want to extract them?", 'Confirm Extraction', 36) != 7
start_time = Time.now

#=============================================================================
# *** Script's strings reader
#=============================================================================
string_reader = false
if SCRIPT_STRINGS_READER
  scripts = ''
  strings = []
  $RGSS_SCRIPTS.each {|s| scripts += s[3]}
  ObjectSpace.each_object(RPG::MoveCommand) do |i|
    scripts += i.parameters[0] + "\r\n" if i.code == 45
  end
  ObjectSpace.each_object(RPG::EventCommand) do |i|
    scripts += i.parameters[0] + "\r\n" if i.code == 355 or i.code == 655
  end
  scripts.gsub(/\"(.*?)\"/) {strings << $1}
  scripts.gsub(/'(.*?)'/) {strings << $1}
  strings.delete('')
  strings.uniq! if !strings.uniq.nil?
  if strings.size > 0
    time_taken += Time.now - start_time
    string_reader = mb.call(0, "#{strings.size} strings have been detected inside the scripts.\r\nDo you want to test them?", 'Confirm Script Testing', 36) != 7
    start_time = Time.now
  end
end

#=============================================================================
# *** Search graphics files
#=============================================================================
sprites = {}
sprites['Graphics/Characters/'] = []
sprites['Graphics/Battlers/'] = []
sprites['Graphics/Icons/'] = []
sprites['Graphics/Animations/'] = []
sprites['Graphics/Tilesets/'] = []
sprites['Graphics/Autotiles/'] = []
sprites['Graphics/Panoramas/'] = []
sprites['Graphics/Fogs/'] = []
sprites['Graphics/Battlebacks/'] = []
sprites['Graphics/Windowskins/'] = []
sprites['Graphics/Titles/'] = []
sprites['Graphics/Gameovers/'] = []
sprites['Graphics/Transitions/'] = []
sprites['Graphics/Battlebacks/'] = []
sprites['Graphics/Pictures/'] = []
ObjectSpace.each_object(RPG::Event::Page::Graphic) do |i|
  sprites['Graphics/Characters/'] << i.character_name
end
ObjectSpace.each_object(RPG::Actor) do |i|
  sprites['Graphics/Characters/'] << i.character_name
  sprites['Graphics/Battlers/'] << i.battler_name
end
ObjectSpace.each_object(RPG::Skill) do |i|
  sprites['Graphics/Icons/'] << i.icon_name
end
ObjectSpace.each_object(RPG::Item) do |i|
  sprites['Graphics/Icons/'] << i.icon_name
end
ObjectSpace.each_object(RPG::Weapon) do |i|
  sprites['Graphics/Icons/'] << i.icon_name
end
ObjectSpace.each_object(RPG::Armor) do |i|
  sprites['Graphics/Icons/'] << i.icon_name
end
ObjectSpace.each_object(RPG::Enemy) do |i|
  sprites['Graphics/Battlers/'] << i.battler_name
end
ObjectSpace.each_object(RPG::Animation) do |i|
  sprites['Graphics/Animations/'] << i.animation_name
end
ObjectSpace.each_object(RPG::Tileset) do |i|
  sprites['Graphics/Tilesets/'] << i.tileset_name
  i.autotile_names.each do |a|
    sprites['Graphics/Autotiles/'] << a
  end
  sprites['Graphics/Panoramas/'] << i.panorama_name
  sprites['Graphics/Fogs/'] << i.fog_name
  sprites['Graphics/Battlebacks/'] << i.battleback_name
end
ObjectSpace.each_object(RPG::System) do |i|
  sprites['Graphics/Windowskins/'] << i.windowskin_name
  sprites['Graphics/Titles/'] << i.title_name
  sprites['Graphics/Gameovers/'] << i.gameover_name
  sprites['Graphics/Transitions/'] << i.battle_transition
  sprites['Graphics/Battlebacks/'] << i.battleback_name
  sprites['Graphics/Battlers/'] << i.battler_name
end
ObjectSpace.each_object(RPG::MoveCommand) do |i|
  sprites['Graphics/Characters/'] << i.parameters[0] if i.code == 41
end
ObjectSpace.each_object(RPG::EventCommand) do |i|
  case i.code
  when 131
    sprites['Graphics/Windowskins/'] << i.parameters[0]
  when 204
    case i.parameters[0]
    when 0
      sprites['Graphics/Panoramas/'] << i.parameters[1]
    when 1
      sprites['Graphics/Fogs/'] << i.parameters[1]
    when 2
      sprites['Graphics/Battlebacks/'] << i.parameters[1]
    end
  when 222
    sprites['Graphics/Transitions/'] << i.parameters[0]
  when 231
    sprites['Graphics/Pictures/'] << i.parameters[1]
  when 322
    sprites['Graphics/Characters/'] << i.parameters[1]
  end
end

#=============================================================================
# *** Script's strings test
#=============================================================================
if string_reader
  folders = {'Graphics/' => ['Animations',  'Autotiles',  'Battlebacks',  'Battlers', 'Characters', 'Fogs', 'Gameovers', 'Icons', 'Panoramas', 'Pictures', 'Tilesets', 'Titles', 'Transitions', 'Windowskins']}
  script_spr, path_strings, usprites = [], [], []
  sprites.each {|k, v| v.each {|v2| usprites << (k + v2).upcase}}
  strings.each do |s|
    next if File.extname(s) == '.rxdata' or s['Audio/']
    path_strings << ['', s] if !usprites.include?(s.upcase)
    folders.each do |k, v|
      path_strings << [k, s] if !usprites.include?((k + s).upcase)
      v.each do |f|
        path_strings << [k + f + '/', s] if !usprites.include?((k + f + '/' + s).upcase)
      end
    end
  end
  path_strings.uniq! if path_strings.uniq.nil?
  path_strings.each do |s2|
    begin
      bitmap = Bitmap.new(s2[0] + s2[1])
      script_spr << s2
      bitmap.dispose
    rescue
      next
    end
  end
  if script_spr.size == 0
    time_taken += Time.now - start_time
    mb.call(0, 'No sprites founded inside the scripts.', 'RGSSAD Extractor', 64)
    start_time = Time.now
  else
    time_taken += Time.now - start_time
    mb.call(0, "Founded #{script_spr.size} sprites inside the scripts.", 'RGSSAD Extractor', 64)
    log.puts("* Sprites founded inside the scripts - Total #{script_spr.size}")
    start_time = Time.now
    script_spr.each do |spr|
      log.puts(spr[0] + spr[1])
      sprites[spr[0]] = [] if sprites[spr[0]].nil?
      sprites[spr[0]] << spr[1]
    end
    log.puts('')
  end
end
sprites.each do |k, v|
  v.delete('')
  v.uniq! if !v.uniq.nil?
end

#=============================================================================
# *** RTP check
#=============================================================================
if !INCLUDE_RTP
  gppsa = Win32API.new('kernel32', 'GetPrivateProfileStringA', 'PPPPLP', 'L')
  dll = "\0" * 255
  gppsa.call('Game', 'Library', '', dll, 255, '.\\Game.ini')
  dll.delete!("\0")
  rgaagetrtppath = Win32API.new(dll, 'RGSSGetRTPPath', 'L', 'L')
  rgaagetpathwithrtp = Win32API.new(dll, 'RGSSGetPathWithRTP', 'L', 'P')
  rtps = []
  for i in 0..99
    rtps << rgaagetpathwithrtp.call(rgaagetrtppath.call(i))
  end
  rtps.delete('')
  rtps.delete(nil)
  rtps.each do |r|
    dirs = Dir.entries(r + '/Graphics')
    dirs.delete('.')
    dirs.delete('..')
    dirs.each do |d|
      dirs.delete(d) if !FileTest.directory?(r + '/Graphics/' + d)
    end
    dirs.each do |d|
      next if sprites['Graphics/' + d + '/'].nil?
      files = Dir.entries(r + '/Graphics/' + d)
      files.delete('.')
      files.delete('..')
      files.each do |f|
        files.delete(f) if !FileTest.file?(r + '/Graphics/' + d + '/' + f)
      end
      for i in 0...files.size
        files[i] = File.basename(files[i], '.*')
      end
      files.each {|f| sprites['Graphics/' + d + '/'].delete(f)}
    end
  end
end

#=============================================================================
# ** Graphics List check
#=============================================================================
if FileTest.exists?('RGSSAD Graphics.txt')
  File.open('RGSSAD Graphics.txt', 'r') do |f|
    files = f.readlines
    files.each {|i| i.gsub!(/\r\n/, '')}
    list_spr = []
    files.each {|i| i.gsub(/(.*\/)?(.*)/) {list_spr << [$1, $2]}}
    list_spr.each do |i|
      next if i[1].nil?
      i[0] = '' if i[0].nil?
      sprites[i[0]] = [] if sprites[i[0]].nil?
      sprites[i[0]] << i[1]
    end
  end
end
sprites.each do |k, v|
  v.delete('')
  v.uniq! if !v.uniq.nil?
end
sprites_count = 0
sprites.each {|k, v| sprites_count += v.size}
time_taken += Time.now - start_time
sprites_extractor = mb.call(0, "#{sprites_count} graphic files have been detected.\r\nAre you sure you want to extract them?", 'Confirm Extraction', 36) != 7
start_time = Time.now

#=============================================================================
# ** Extract data files
#=============================================================================
saved_data = []
total_saved_data = 0
if data_extractor
  extract_data($RGSS_SCRIPTS, 'Data/Scripts.rxdata', saved_data)
  extract_data(data_actors, 'Data/Actors.rxdata', saved_data)
  extract_data(data_classes, 'Data/Classes.rxdata', saved_data)
  extract_data(data_skills, 'Data/Skills.rxdata', saved_data)
  extract_data(data_items, 'Data/Items.rxdata', saved_data)
  extract_data(data_weapons, 'Data/Weapons.rxdata', saved_data)
  extract_data(data_armors, 'Data/Armors.rxdata', saved_data)
  extract_data(data_enemies, 'Data/Enemies.rxdata', saved_data)
  extract_data(data_troops, 'Data/Troops.rxdata', saved_data)
  extract_data(data_states, 'Data/States.rxdata', saved_data)
  extract_data(data_animations, 'Data/Animations.rxdata', saved_data)
  extract_data(data_tilesets, 'Data/Tilesets.rxdata', saved_data)
  extract_data(data_common_events, 'Data/CommonEvents.rxdata', saved_data)
  extract_data(data_system, 'Data/System.rxdata', saved_data)
  extract_data(data_mapinfos, 'Data/MapInfos.rxdata', saved_data)
  data_maps.each do |k, v|
    extract_data(v, sprintf('Data/Map%03d.rxdata', k), saved_data)
  end
  if FileTest.exists?('RGSSAD Data.txt')
    File.open('RGSSAD Data.txt', 'r') do |f|
      files = f.readlines
      files.each {|i| i.gsub!(/\r\n/, '')}
      files.each do |i|
        data = load_data(i) rescue ''
        extract_data(data, i, saved_data)
      end
    end
  end
  saved_data.each {|i| total_saved_data += i[0] ? 1 : 0}
  log.puts("* Data extraction - #{total_saved_data} of #{saved_data.size}")
  saved_data.each do |f|
    if f[0]
      log.puts("Succesfuly extracted #{f[1]}")
    else
      log.puts("Failed extracting #{f[1]}")
    end
  end
  log.puts('')
end

#=============================================================================
# *** Extract graphic files
#=============================================================================
saved, not_saved_error, not_saved_notfound, not_saved_existing, not_saved = [], [], [], [], []
sprites_count = 0
all_sprites = []
sprites.each {|k, v| sprites_count += v.size; v.each {|v2| all_sprites << k + v2}}
if sprites_extractor
  Dir.mkdir('Temp') if !FileTest.exist?('Temp')
  rgssad_sprite.bitmap.clear
  rgssad_sprite.bitmap.draw_text(0,0,640,32,"Extracting graphics")
  sprites.each do |k, v|
    v.each do |s|
      begin
        if !FileTest.exists?('RGSSAD/' + k + s + '.png')
          rgssad_sprite.bitmap.fill_rect(0,32,640,96,Color.new(0,0,0,0)) 
          rgssad_sprite.bitmap.draw_text(0,32,640,32,"Current file #{k + s}")
          rgssad_sprite.bitmap.draw_text(0,96,640,32,"File #{saved.size + not_saved_existing.size + not_saved_error.size + not_saved_notfound.size + 1} of #{sprites_count}")
          Graphics.transition(0)
          begin
            bitmap = Bitmap.new(k + s)
          rescue
            not_saved_notfound << k + s
            next
          end
          rgssad_sprite.bitmap.draw_text(0,64,640,32,"Graphic's width: #{bitmap.width} pxs - Graphic's height: #{bitmap.height} pxs")
          bitmap.make_png(s, 'RGSSAD/' + k)
          saved << k + s
          bitmap.dispose
        else
          not_saved_existing << k + s
        end
      rescue
        not_saved_error << k + s
      end
    end
  end
end
rgssad_sprite.bitmap.dispose
rgssad_sprite.dispose
rgssad_sprite = nil
not_saved = all_sprites - saved - not_saved_existing - not_saved_notfound - not_saved_error
time_taken += Time.now - start_time
if saved.size > 0
  log.puts("* Extracted graphics - #{saved.size} of #{sprites_count}")
  log.puts(saved.join("\r\n"))
  log.puts('')
end
if not_saved_existing.size > 0
  log.puts("* Already existing graphics - #{not_saved_existing.size} of #{sprites_count}")
  log.puts(not_saved_existing.join("\r\n"))
  log.puts('')
end
if not_saved_notfound.size > 0
  log.puts("* Not founded graphics - #{not_saved_notfound.size} of #{sprites_count}")
  log.puts(not_saved_notfound.join("\r\n"))
  log.puts('')
end
if not_saved_error.size > 0
  log.puts("* Error at extracting graphics - #{not_saved_error.size} of #{sprites_count}")
  log.puts(not_saved_error.join("\r\n"))
  log.puts('')
end
if not_saved.size > 0
  log.puts("* Not extracted graphics - #{not_saved.size} of #{sprites_count}")
  log.puts(not_saved.join("\r\n"))
  log.puts('')
end
ts = [time_taken.to_i, 1].max
h = ts / 3600
m = (ts - ts / 3600 * 3600) / 60
s = ts - (ts - ts / 3600 * 3600) / 60 * 60 - ts / 3600 * 3600

#=============================================================================
# *** Finalize
#=============================================================================
log.puts("*** RGSSAD Extraction - #{Time.now.strftime("Finished at %d/%m/%Y(d/m/y) %H:%M:%S")} - Extraction time #{sprintf("%02d", h)}:#{sprintf("%02d", m)}:#{sprintf("%02d", s)}")
Dir.mkdir('RGSSAD') if !FileTest.exists?('RGSSAD')
copy_file('Game.exe', 'RGSSAD/Game.exe')
copy_file('Game.ini', 'RGSSAD/Game.ini')
File.open("RGSSAD/Game.rxproj", "wb") {|f| f.puts("RPGXP 1.00")}
print "Data files extracted: #{total_saved_data} of #{saved_data.size}\r\n" +
"Sprites founded: #{sprites_count}\r\n" +
"Sprites extracted: #{saved.size}\r\n" +
"Already existing sprites: #{not_saved_existing.size}\r\n" +
"Not founded sprites: #{not_saved_notfound.size}\r\n" +
"Fatal errors when extracting sprites: #{not_saved_error.size}\r\n" +
"Total not extracted sprites: #{not_saved.size}\r\n" +
"Total extracted files: #{total_saved_data + saved.size} of #{saved_data.size + sprites_count}"

if !IN_GAME_EXTRACTOR
  if FileTest.exists?('Temp')
    Dir.delete('Temp') if Dir.entries('Temp').size == 2
  end
  exit
end

rescue
  print "Exception: #{$!.exception}\r\nMessage: #{$!.message}\r\nBacktrace: #{$!.backtrace}"
  exit
end

#=============================================================================
# ** In Game Extraction
#=============================================================================
log.puts('')
log.puts("*** RGSSAD In Game Extraction - #{Time.now.strftime("Started at %d/%m/%Y(d/m/y) %H:%M:%S")}")
log.close
log = nil
$rtp_files = []
$rgssad_sprite = Sprite.new
$rgssad_sprite.bitmap = Bitmap.new(640, 64)
$rgssad_sprite.z = 99999
$rgssad_sprite.visible = false
if !INCLUDE_RTP
  gppsa = Win32API.new('kernel32', 'GetPrivateProfileStringA', 'PPPPLP', 'L')
  dll = "\0" * 255
  gppsa.call('Game', 'Library', '', dll, 255, '.\\Game.ini')
  dll.delete!("\0")
  rgaagetrtppath = Win32API.new(dll, 'RGSSGetRTPPath', 'L', 'L')
  rgaagetpathwithrtp = Win32API.new(dll, 'RGSSGetPathWithRTP', 'L', 'P')
  rtps = []
  for i in 0..99
    rtps << rgaagetpathwithrtp.call(rgaagetrtppath.call(i))
  end
  rtps.delete('')
  rtps.delete(nil)
  rtps.each do |r|
    dirs = Dir.entries(r + '/Graphics')
    dirs.delete('.')
    dirs.delete('..')
    dirs.each do |d|
      dirs.delete(d) if !FileTest.directory?(r + '/Graphics/' + d)
    end
    dirs.each do |d|
      next if sprites['Graphics/' + d + '/'].nil?
      files = Dir.entries(r + '/Graphics/' + d)
      files.delete('.')
      files.delete('..')
      files.each do |f|
        files.delete(f) if !FileTest.file?(r + '/Graphics/' + d + '/' + f)
      end
      for i in 0...files.size
        files[i] = File.basename(files[i], '.*')
      end
      files.each do |f|
        $rtp_files << 'Graphics/' + d + '/' + f
      end
    end
  end
end

module Graphics
  @frame_skip_rate = 0
  @frame_skip_count = 0
  class << self
    alias_method(:rgssad_update, :update)
    def update
      $DEBUG = true
      if Input.trigger?(Input::F5)
        @frame_skip_rate += 5
      end
      if Input.trigger?(Input::F6)
        @frame_skip_rate = [@frame_skip_rate - 5, 0].max
      end
      if Input.trigger?(Input::F7)
        @frame_skip_rate = 0
      end
      if @frame_skip_rate > 0
        Graphics.frame_rate = 120
        @frame_skip_count += 1
        if @frame_skip_count >= @frame_skip_rate
          @frame_skip_count = 0
        else
          return
        end
      end
      rgssad_update
    end
  end
end

class Bitmap
  alias_method(:rgssad_initialize, :initialize)
  def initialize(*args)
    rgssad_initialize(*args)
    if args.size == 1
      if args[0].is_a?(String)
        rgssad_save_bitmap(args[0])
      end
    end
  end
  def rgssad_save_bitmap(file)
    dir = File.dirname(file) + '/'
    name = File.basename(file, '.*')
    if !FileTest.exists?('RGSSAD/' + dir + name + '.png') and !$rtp_files.include?(dir + name)
      begin
        if !FileTest.exists?('Temp')
          Dir.mkdir('Temp')
        end
        if !$rgssad_sprite.is_a?(Sprite)
          $rgssad_sprite = Sprite.new
          $rgssad_sprite.bitmap = Bitmap.new(640, 64)
          $rgssad_sprite.z = 99999
        elsif $rgssad_sprite.bitmap.nil?
          $rgssad_sprite.bitmap = Bitmap.new(640, 64)
        elsif $rgssad_sprite.bitmap.disposed?
          $rgssad_sprite.bitmap = Bitmap.new(640, 64)
        end
        $rgssad_sprite.bitmap.fill_rect(0,0,640,64,Color.new(0,0,0))
        $rgssad_sprite.bitmap.font.name = 'Lucida Sans'
        $rgssad_sprite.bitmap.font.size = 20
        $rgssad_sprite.bitmap.font.color = Color.new(255,255,255,255)
        $rgssad_sprite.bitmap.draw_text(0,0,640,32,"Extracting #{dir + name}")
        $rgssad_sprite.bitmap.draw_text(0,32,640,32,"Graphic's width: #{self.width} pxs - Graphic's height: #{self.height} pxs")
        $rgssad_sprite.visible = true
        Graphics.transition(0)
        make_png(name, 'RGSSAD/' + dir, 0)
        log = File.open('RGSSAD Extractor log.txt', 'a')
        log.puts("Successfuly extracted #{dir + name}")
        log.close
      rescue
      end
      $rgssad_sprite.visible = false
    end
  end
end
