puts "======================"
puts "TXT2GM Inventory"
puts "Created by: PedroHLC"
puts "Version: 1.0"
puts "======================"
$input_folder = '.\\TXT\\'
$output_folder = '.\\RMXP2GM\\Data\\'
$def_less_filepath = '.\\RMXP2GM\\def_less.txt'
$cache = []
$armors = []
$weapons = []
$item_id = 0
$type_id = 0

$def_less_file = File.open($def_less_filepath,'w')

module RPG
class Armor
  def initialize
    @id = 0
    @name = ''
    @icon_name = ''
    @description = ''
    @kind = 0
    @auto_state_id = 0
    @price = 0
    @pdef = 0
    @mdef = 0
    @eva = 0
    @str_plus = 0
    @dex_plus = 0
    @agi_plus = 0
    @int_plus = 0
    @guard_element_set = []
    @guard_state_set = []
  end
  attr_accessor :id
  attr_accessor :name
  attr_accessor :icon_name
  attr_accessor :description
  attr_accessor :kind
  attr_accessor :auto_state_id
  attr_accessor :price
  attr_accessor :pdef
  attr_accessor :mdef
  attr_accessor :eva
  attr_accessor :str_plus
  attr_accessor :dex_plus
  attr_accessor :agi_plus
  attr_accessor :int_plus
  attr_accessor :guard_element_set
  attr_accessor :guard_state_set
end
class Weapon
  def initialize
    @id = 0
    @name = ''
    @icon_name = ''
    @description = ''
    @animation1_id = 0
    @animation2_id = 0
    @price = 0
    @atk = 0
    @pdef = 0
    @mdef = 0
    @str_plus = 0
    @dex_plus = 0
    @agi_plus = 0
    @int_plus = 0
    @element_set = []
    @plus_state_set = []
    @minus_state_set = []
  end
  attr_accessor :id
  attr_accessor :name
  attr_accessor :icon_name
  attr_accessor :description
  attr_accessor :animation1_id
  attr_accessor :animation2_id
  attr_accessor :price
  attr_accessor :atk
  attr_accessor :pdef
  attr_accessor :mdef
  attr_accessor :str_plus
  attr_accessor :dex_plus
  attr_accessor :agi_plus
  attr_accessor :int_plus
  attr_accessor :element_set
  attr_accessor :plus_state_set
  attr_accessor :minus_state_set
end
end

def convert_armor(armor_value, kind)
  armor = RPG::Armor.new
  armor.id = $armors.size
  armor.icon_name = armor_value[0]
  armor.name = armor_value[1]
  armor.description = armor_value[2]
  armor.str_plus = armor_value[3]
  armor.pdef = armor_value[4]
  armor.kind = kind
  $armors.push(armor)
end

def convert_weapon(weapon_value)
  weapon = RPG::Weapon.new
  weapon.id = $weapons.size
  weapon.icon_name = weapon_value[0]
  weapon.name = weapon_value[1]
  weapon.description = weapon_value[2]
  weapon.atk = weapon_value[3]
  weapon.pdef = weapon_value[4]
  if weapon_value[4].to_i < 0
    $def_less_file.write("<i>w,#{weapon.id}</i>\n")
  end
  $weapons.push(weapon)
end

def complete_item
  return if $item_id == 0
  if $cache[$type_id][$item_id][0].nil?
    $cache[$type_id][$item_id][0] = ''
  end
  if $cache[$type_id][$item_id][1].nil?
    $cache[$type_id][$item_id][1] = ''
  end
  if $cache[$type_id][$item_id][2].nil?
    $cache[$type_id][$item_id][2] = ''
  end
  if $cache[$type_id][$item_id][3].nil?
    $cache[$type_id][$item_id][3] = 0
  end
  if $cache[$type_id][$item_id][4].nil?
    $cache[$type_id][$item_id][4] = 0
  end
end

def convert_file(filename)
  $item_id = 0
  $type_id += 1
  $cache[$type_id] = []
  $cache[$type_id][$item_id] = []
  file = File.open(filename, 'rb').readlines
  for line_orig in file
    line = line_orig.strip!
    case line
    when /<i>(.*)<\/i>/
      complete_item
      $item_id += 1
      $cache[$type_id][$item_id] = []
    when /<v>icon=(.*)<\/v>/
      $cache[$type_id][$item_id][0] = $1.to_s
    when /<v>title=(.*)<\/v>/
      $cache[$type_id][$item_id][1] = $1.to_s
    when /<v>description=(.*)<\/v>/
      $cache[$type_id][$item_id][2] = $1.to_s
    when /<v>atk_plus=(.*)<\/v>/
      $cache[$type_id][$item_id][3] = $1.to_i
    when /<v>att_plus=(.*)<\/v>/
      $cache[$type_id][$item_id][3] = $1.to_i
    when /<v>def_plus=(.*)<\/v>/
      $cache[$type_id][$item_id][4] = $1.to_i
    when /<v>def_less=(.*)<\/v>/
      $cache[$type_id][$item_id][4] = (0 - $1.to_i).to_i
    end
  end
end

def convert_folder(path)
  for filename in Dir.entries(path)
    next if filename.nil?
    next if filename == '.'
    next if filename == '..'
    
    if File.directory?(path + filename)
      convert_folder(path + filename + '\\')
    else
      convert_file(path + filename)
    end
  end
end

puts "Inciando conversao"

convert_folder($input_folder)

type_i = -1
for type in $cache
  puts "======="
  type_i += 1
  puts type_i
  next if type.nil?
  for item in type
    next if item.nil?
    puts "------"
    puts item
    case type_i
    when 1
      convert_weapon(item)
    when 2
      convert_weapon(item)
    when 3
      convert_weapon(item)
    when 4
      convert_armor(item, 0)
    when 5
      convert_weapon(item)
    when 6
      convert_weapon(item)
    end
  end
end

$def_less_file.close

puts "======="
puts "Salvando..."
file = File.open($output_folder + 'Armors.rxdata', "wb")
Marshal.dump($armors, file)
file.close
file = File.open($output_folder + 'Weapons.rxdata', "wb")
Marshal.dump($weapons, file)
file.close
puts "Salvo com sucesso!"
puts "======="
puts "Fim da conversao, pressione ENTER para sair!"
gets