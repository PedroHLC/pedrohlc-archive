system('title "Passoword Brutal Kill - By: PedroHLC"')
puts 'Passoword Brutal Kill'
puts 'By: PedroHLC'
puts '-------------------------------'

require 'Win32API'

$Kbe = Win32API.new('user32', 'keybd_event', 'LLLL', '')
def press_key(code)
  $Kbe.call(code, 0, 0, 0)
  sleep(0.1)
  $Kbe.call(code, 0, 2, 0)
end

sleep(2)

def get_num_key(num)
  return 0x30 + num.to_i
end

def get_let_key(code)
  ascii_code = (code.upcase.to_s[0].to_i - "A"[0].to_i).to_i
  return 0x41 + ascii_code
end

def discover_key(key)
  return nil if key < 0
  if key > 9
    letter = "A"
    letter[0] += (key - 10)
    result = get_let_key(letter)
  else
   letter = "0"
   letter[0] += key
   result = get_num_key(letter)
  end
  return [letter, result]
end

digits_limit = 20

digits = Array.new(digits_limit + 1, (-1))
last_one = ""

loop do
  digits[digits_limit] += 1
  #Cria o tamanho do resultado
  for digit_size in 0..digits_limit 
    #Para cada digito
    for digit in 0..(digit_size - 1)
      realdigit = (digits_limit - digit)
      #Seo digito for > 35
      if digits[realdigit] > 35
        #Aumentar o digito anterior
        digits[(realdigit - 1)] += 1
        #Retorna esse digito ao nada
        digits[realdigit] = (-1)
      end
    end
    # Se o digito final for > 35, então para
    if digits[digit_size] > 35
      digits[digit_size - 1] += 1
      digits[digit_size] = 0
      break
    else
      trying_now = ""
      for digit in (digits_limit - digit_size)..(digits_limit)
        if digits[digit] >= 0
          key = discover_key(digits[digit])
          if !key[1].nil?
            trying_now += (key[0])
            #press_key(key[1])
          end
        end
      end
      if trying_now.size >= last_one.size
        if last_one != trying_now
          last_one = trying_now
          press_key(0x0D)
          #system("cls")
          puts trying_now
          sleep(0.25)
        end
      end
    end
  end
  break if digits[0] > 35
end
#press_key(get_num_key(3))
#press_key(get_let_key('k'))
#press_key(0x0D) #=Enter/Return