puts "======================"
puts "RMXP2GM Armors"
puts "Created by: PedroHLC"
puts "Version: 1.0"
puts "======================"
puts "OBS sobre o conversor:"
puts "Game Maker = RMXP"
puts "*Defesa = Defesa Fisica"
puts "*CON = Agilidade"
puts "*Sorte = Defesa Magica/Mistica"
puts "*Forca = Fuga/Evasiva"
puts "======================"
$armors_input_file = '.\\Data\\Armors.rxdata'
$armors_output_file = '.\\rpg_armors.txt'

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
end

def load_data(filename)
  file =  File.open(filename,'r')
  data = Marshal.load(file)
  file.close
  return data
end
puts "Lendo: #{$armors_input_file}"
$data_armors = load_data($armors_input_file)
puts "Criando: #{$armors_output_file}"
$gm_armors = File.open($armors_output_file,'w')
def write(value)
  $gm_armors.write(value.to_s + "\n")
end
puts "Escrevendo cabecalho"
write("globalvar rpg_armors_name")
write("globalvar rpg_armors_icon_name")
write("globalvar rpg_armors_description")
write("globalvar rpg_armors_price")
write("globalvar rpg_armors_kind")
write("globalvar rpg_armors_str") #Antiga Fuga
write("globalvar rpg_armors_def") #Antiga PDEF
write("globalvar rpg_armors_dex")
write("globalvar rpg_armors_con") #Antiga agilidade
write("globalvar rpg_armors_int")
write("globalvar rpg_armors_lck") #Antiga MDEF
write('') #Cria uma linha
puts "Iniciando conversao..."
i = 0
for armor in $data_armors
  next if armor.name.size <= 0 and armor.icon_name.size <= 0 and armor.description.size <= 0
  i += 1 
  write("global.rpg_armors_name[#{i}] = " + '"' + armor.name.to_s + '"')
  write("global.rpg_armors_icon_name[#{i}] = " + '"' + armor.icon_name.to_s + '"')
  write("global.rpg_armors_description[#{i}] = " + '"' + armor.description.to_s + '"')
  write("global.rpg_armors_price[#{i}] = #{armor.price}")
  write("global.rpg_armors_kind[#{i}] = #{armor.kind}")
  write("global.rpg_armors_def[#{i}] = #{armor.pdef}")
  write("global.rpg_armors_str[#{i}] = #{armor.eva}")
  write("global.rpg_armors_dex[#{i}] = #{armor.dex_plus}")
  write("global.rpg_armors_con[#{i}] = #{armor.agi_plus}")
  write("global.rpg_armors_int[#{i}] = #{armor.int_plus}")
  write("global.rpg_armors_lck[#{i}] = #{armor.mdef}")
end
puts "Fim da conversao, pressione ENTER para sair!"
gets