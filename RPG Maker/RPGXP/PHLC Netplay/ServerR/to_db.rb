class Array
  def to_db
    return "'#{to_fs}'"
  end
end

class TrueClass
  def to_db
    return "'1'"
  end
end

class FalseClass
  def to_db
    return "'0'"
  end
end

class NilClass
  def to_db
    return "''"
  end
end

class Numeric
  def to_db
    return "'#{to_s}'"
  end
end

class String
  def to_db
    return "'#{self}'"
  end
end

class Fixnum
  def to_db
    return "'#{to_s}'"
  end
end