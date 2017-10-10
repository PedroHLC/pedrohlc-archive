#==============================================================================
# Nome: Encriptador de pacotes
# Descrição: Aqui se encripta os pacotes para que não haja como intercepta-los
#------------------------------------------------------------------------------
# Criado por: PedroHLC
# Versão: 1.0
#------------------------------------------------------------------------------
# Créditos à HugoLnx q me encinou a encriptar as coisas :P
#==============================================================================

$nil_encrypt_pass = 0.chr

class String
  def each_char
    if block_given?
      scan(/./m) do |x|
        yield(x)
      end
    else
      return scan(/./m)
    end
  end
end 

class SocketEncryptionClass
  def initialize
    @pass = 0
    @pass_str = $nil_encrypt_pass
  end
  
  def change_pass(pass)
    return if @pass_str == pass
    @pass_str = pass.downcase
    pass = 0
    return if pass.size <= 0
    @pass_str.each_char{|pass_chr| pass += pass_chr[0].to_i }
    @pass = pass.to_i
    puts "Senha final de encriptacao: #{@pass}"
  end
  
  def encrypt(msg)
    if !msg.is_a?(String)
      puts "Erro o pacote a ser encaminhado nao e uma string"
      exit
    end
    str = Marshal.dump(msg)
    pass = (((str.size/2)**2 + 1502) * @pass).to_s
    i = 0
    while i <= (str.size - 1)
      pass.each_char{|pass_chr|
        new_ascii = str[i] + pass_chr[0]
        new_ascii -= 256 if new_ascii > 255
        str[i] = new_ascii
        i += 1
        break if str[i] == nil
      }
      break if str[i] == nil
    end
    return str.to_s
  end
  
  def desencrypt(str)
    pass = (((str.size/2)**2 + 1502) * @pass).to_s
    i = 0
    while i <= (str.size - 1)
      pass.each_char{|pass_chr|
        new_ascii = str[i] - pass_chr[0]
        new_ascii += 256 if new_ascii < 0
        str[i] = new_ascii
        i += 1
        break if str[i] == nil
      }
      break if str[i] == nil
    end
    msg = Marshal.load(str)
    return msg.to_s
  end
end
SocketEncryption = SocketEncryptionClass.new
#SocketEncryption.change_pass(pass)
#SocketEncryption.encrypt(str)
#SocketEncryption.desencrypt(str)