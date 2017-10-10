puts "======================"
puts "RMXP2GM Weapons"
puts "Created by: PedroHLC"
puts "Version: 1.1"
puts "======================"
puts "OBS sobre o conversor:"
puts "Game Maker = RMXP"
puts "*Defesa = Defesa Fisica"
puts "*CON = Agilidade"
puts "*Sorte = Defesa Magica/Mistica"
puts "======================"
$weapons_input_file = '.\\Data\\Weapons.rxdata'
$weapons_output_file = '.\\rpg_weapons.txt'

class NilClass
  def size
    return (-1)
  end
end

module RPG
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
puts "Lendo: #{$weapons_input_file}"
$data_weapons = load_data($weapons_input_file)
puts "Criando: #{$weapons_output_file}"
$gm_weapons = File.open($weapons_output_file,'w')
def write(value)
  $gm_weapons.write(value.to_s + "\n")
end
puts "Escrevendo cabecalho"
write("globalvar rpg_weapons_name")
write("globalvar rpg_weapons_icon_name")
write("globalvar rpg_weapons_description")
write("globalvar rpg_weapons_price")
write("globalvar rpg_weapons_atk")
write("globalvar rpg_weapons_def") #Antiga PDEF
write("globalvar rpg_weapons_str")
write("globalvar rpg_weapons_dex")
write("globalvar rpg_weapons_con") #Antiga agilidade
write("globalvar rpg_weapons_int")
write("globalvar rpg_weapons_lck") #Antiga MDEF
write('') #Cria uma linha
puts "Iniciando conversao..."
i = 0 
for weapon in $data_weapons
  next if weapon.name.size <= 0 and weapon.icon_name.size <= 0 and weapon.description.size <= 0
  i += 1 
  write("global.rpg_weapons_name[#{i}] = " + '"' + weapon.name.to_s + '"')
  write("global.rpg_weapons_icon_name[#{i}] = " + '"' + weapon.icon_name.to_s + '"')
  write("global.rpg_weapons_description[#{i}] = " + '"' + weapon.description.to_s + '"')
  write("global.rpg_weapons_price[#{i}] = #{weapon.price}")
  write("global.rpg_weapons_atk[#{i}] = #{weapon.atk}")
  write("global.rpg_weapons_def[#{i}] = #{weapon.pdef}")
  write("global.rpg_weapons_str[#{i}] = #{weapon.str_plus}")
  write("global.rpg_weapons_dex[#{i}] = #{weapon.dex_plus}")
  write("global.rpg_weapons_con[#{i}] = #{weapon.agi_plus}")
  write("global.rpg_weapons_int[#{i}] = #{weapon.int_plus}")
  write("global.rpg_weapons_lck[#{i}] = #{weapon.mdef}")
end
puts "Fim da conversao, pressione ENTER para sair!"
gets