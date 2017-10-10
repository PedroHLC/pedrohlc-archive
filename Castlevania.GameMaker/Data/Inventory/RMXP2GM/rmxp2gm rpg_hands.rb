puts('======================')
puts('RMXP2GM Hands Items')
puts('Created by: PedroHLC')
puts('Version: 1.0')
puts('======================')
puts('OBS sobre o conversor:')
puts('Game Maker = RMXP')
puts('*Defesa = Defesa Fisica')
puts('*CON = Agilidade')
puts('*Sorte = Defesa Magica/Mistica (Somente nos escudos)')
puts('======================')
puts('')
puts('')
puts('')
puts('Criando as variaveis e funcoes')
$armors_input_file = '.\\Data\\Armors.rxdata'
$weapons_input_file = '.\\Data\\Weapons.rxdata'
$defless_filename = '.\\Data\\Weapons.rxdata'
$output_file = '.\\rpg_hands.txt'
$defless = []

class NilClass
  def size
    return (-1)
  end
end

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

def load_data(filename)
  file =  File.open(filename,'r')
  data = Marshal.load(file)
  file.close
  return data
end

def write(str)
  $gm_hands.write(str.to_s + "\n")
end

def convert_defless(value)
  case value.to_s
  when /<i>w,(.*)<\/i>/
    return $1.to_i
  else
    return nil
  end
end

def convert_armor(new_id, armor)
  write("global.rpg_hands_name[#{new_id}] = " + '"' + armor.name.to_s + '";')
  write("global.rpg_hands_icon_name[#{new_id}] = " + '"' + armor.icon_name.to_s + '";')
  write("global.rpg_hands_description[#{new_id}] = " + '"' + armor.description.to_s + '";')
  write("global.rpg_hands_price[#{new_id}] = #{armor.price};")
  write("global.rpg_hands_kind[#{new_id}] = #{armor.kind+1};")
  write("global.rpg_hands_atk[#{new_id}] = 0;")
  write("global.rpg_hands_def[#{new_id}] = #{armor.pdef};")
  write("global.rpg_hands_str[#{new_id}] = #{armor.eva};")
  write("global.rpg_hands_dex[#{new_id}] = #{armor.dex_plus};")
  write("global.rpg_hands_con[#{new_id}] = #{armor.agi_plus};")
  write("global.rpg_hands_int[#{new_id}] = #{armor.int_plus};")
  write("global.rpg_hands_lck[#{new_id}] = #{armor.mdef};")
end

def convert_weapon(new_id, weapon)
  write("global.rpg_hands_name[#{new_id}] = " + '"' + weapon.name.to_s + '";')
  write("global.rpg_hands_icon_name[#{new_id}] = " + '"' + weapon.icon_name.to_s + '";')
  write("global.rpg_hands_description[#{new_id}] = " + '"' + weapon.description.to_s + '";')
  write("global.rpg_hands_price[#{new_id}] = #{weapon.price};")
  write("global.rpg_hands_kind[#{new_id}] = 0;")
  write("global.rpg_hands_atk[#{new_id}] = #{weapon.atk};")
  if $defless_file[new_id] == true and weapon.pdef.to_i > 0
    write("global.rpg_hands_def[#{new_id}] = #{(0 - weapon.pdef.to_i)};")
  end
  write("global.rpg_hands_def[#{new_id}] = #{weapon.pdef.to_i};")
  write("global.rpg_hands_str[#{new_id}] = #{weapon.str_plus};")
  write("global.rpg_hands_dex[#{new_id}] = #{weapon.dex_plus};")
  write("global.rpg_hands_con[#{new_id}] = #{weapon.agi_plus};")
  write("global.rpg_hands_int[#{new_id}] = #{weapon.int_plus};")
  write("global.rpg_hands_lck[#{new_id}] = #{weapon.mdef};")
end
puts('Completo!')

begin
  puts('======================')
  puts('Lendo as databases')
  $data_armors = load_data($armors_input_file)
  $data_weapons = load_data($weapons_input_file)
  $defless_file = File.open($defless_filename, 'rb').readlines if File.exist?($defless_filename)
  puts('Completo!')
  
  unless $defless_file.nil?
    puts('======================')
    puts('Indexando as armas de defesa inferior a 0')
    for defless in $defless
      next if defless.to_s.size < 1
      result = convert_defless(defless)
      $defless[result] = true if result > 0
    end
    puts('Completo!')
  end
  
  puts('======================')
  puts('Criando o arquivo final')
  $gm_hands = File.open($output_file,'w')
  puts('Completo!')
  
  puts('======================')
  puts('Escrevendo cabecalho')
  write("globalvar rpg_hands_name;")
  write("globalvar rpg_hands_icon_name;")
  write("globalvar rpg_hands_description;")
  write("globalvar rpg_hands_price;")
  write("globalvar rpg_hands_kind;")
  write("globalvar rpg_hands_atk;")
  write("globalvar rpg_hands_def;")
  write("globalvar rpg_hands_str;")
  write("globalvar rpg_hands_dex;")
  write("globalvar rpg_hands_con;")
  write("globalvar rpg_hands_int;")
  write("globalvar rpg_hands_lck;")
  write("globalvar rpg_hands_size;")
  write('') #Cria uma linha
  puts('Completo!')
  
  puts('======================')
  puts('Iniciando conversao das armaduras')
  new_id = 0
  for armor in $data_armors
    next if armor.name.size <= 0 and armor.icon_name.size <= 0 and armor.description.size <= 0
    new_id += 1
    convert_armor(new_id, armor)
  end
  write('') #Cria uma linha
  puts('Completo!')
  
  puts('======================')
  puts('Iniciando conversao das armas') 
  for weapon in $data_weapons
    next if weapon.name.size <= 0 and weapon.icon_name.size <= 0 and weapon.description.size <= 0
    new_id += 1
    convert_weapon(new_id, weapon)
  end
  write('') #Cria uma linha
  write("global.rpg_hands_size = #{new_id};")
  puts('Completo!')
  
  puts('======================')
  puts "Fim da conversao, pressione ENTER para sair!"
  gets
rescue Exception => error
  puts('======================')
  puts('Um erro occoreu, indetificacao:')
  puts(error)
  puts('======================')
  puts "Fim da conversao, pressione ENTER para sair!"
  gets
end