def get_note(id)
  x = (id - 1) * 66
  print("Rect.new(#{x},0,65,56), ")
end
for i in 1..5
  get_note(i)
end
puts ""
puts ""
def get_frets(type,id)
  x = (id - 1) * 69
  y = (type - 1) * 67
  print("Rect.new(#{x},#{y},68,66), ")
end
for l in 1..3
for i in 1..5
  get_frets(l,i)
end
puts ""
end
puts ""
def get_bars(type, id)
  x = (id - 1) * 69
  y = (type - 1) * 185
  print("Rect.new(#{x},#{y},68,185), ")
end
for l in 1..3
for i in 1..5
  get_bars(l,i)
end
puts ""
end