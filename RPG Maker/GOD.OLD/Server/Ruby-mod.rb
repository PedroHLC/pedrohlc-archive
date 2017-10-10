#by PedroHLC
class TrueClass
  def to_i
    return 1
  end
  def to_tf
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
class Numeric
  def to_tf
    if self > 0
      return true
    else
      return false
    end
  end
end
class String
  def to_tf
    if self.include?("true") or self.to_i = 1
      return true
    else
      return false
    end
  end
end

class Array
  def to_s
    return_value = ""
    if self.size >= 2
      for i in 0..(self.size-2)
        return_value += self[i].to_s + ","
      end
    end
    return_value += self[(self.size-1)].to_s
    return return_value
  end
end