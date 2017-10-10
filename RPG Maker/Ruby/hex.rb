def i2t(value)
  case value.to_i
  when 0
    return "A"
  when 1
    return "B"
  when 2
    return "C"
  when 3
    return "D"
  when 4
    return "E"
  when 5
    return "F"
  end
end

@pre_index = [0,0,0,0,0]

def pre
  for i in 0..4
    print i2t(@pre_index[i])
  end
end

loop do
  for i1 in 0..5
    pre
    puts i2t(i1)
  end
  @pre_index[4] += 1 
  if @pre_index[4] > 5
    @pre_index[3] += 1 
    @pre_index[4] = 0
  end
  if @pre_index[3] > 5
    @pre_index[2] += 1 
    @pre_index[3] = 0
  end
  if @pre_index[2] > 5
    @pre_index[1] += 1 
    @pre_index[2] = 0
  end
  if @pre_index[1] > 5
    @pre_index[0] += 1 
    @pre_index[1] = 0
  end
  if @pre_index[0] > 5
    break
  end
end