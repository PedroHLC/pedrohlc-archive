#==============================================================================
# Adicionados:
# -Object.to_db #Converte para a Database
# -Object.to_tf #Converte o objeto para verdadeiro(true) ou falso(false)
# -Array.to_fs #Converte para uma string formatada(Ex: "['valor1',2,[3,3],0.4]")
# -Numeric.between? #Verifica se o numero está entre...
# -ecit #Sai corretamente do aplicativo
#==============================================================================

class Array
  def to_fs#Convert to a Formated String
    data = self.dup
    final_data = '['
    for i in 0..(data.size-2)
      if data[i].is_a?(Array)
        final_data += data[i].to_fs
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
end

class TrueClass
  def to_i
    return 1
  end
  def to_tf#Convert to true/false
    return self
  end
end

class FalseClass
  def to_i
    return 0
  end
  def to_tf
    return self
  end
end

class NilClass
  def to_a
    return []
  end
  def to_s
    return ''
  end
  def to_i
    return 0
  end
  def to_f
    return 0
  end
  def to_tf
    return false
  end
end


class Numeric
  def to_tf
    if self > 0
      return true
    else
      return false
    end
  end
  def self.between?(what,to) #By: DarkD.Vicious
    return true if self >= what and self <= to
    return false
  end
end

class String
  def to_tf
    if self.downcase.include?("true") or self.to_i == 1
      return true
    else
      return false
    end
  end
end

class Fixnum
  def to_tf
    if self.to_i > 0
      return true
    else
      return false
    end
  end
end