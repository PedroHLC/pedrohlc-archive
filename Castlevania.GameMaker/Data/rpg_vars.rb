file = File.open('./rpg_vars.txt','rb').readlines
file2 = File.open('./rpg_vars2.txt','a+')
for i in 0..(file.size - 1)
case file[i]
when /globalvar rpg_(.*); \/\/Array/
file2.write("global.rpg_#{$1}[0] = 0;\n")
when /globalvar rpg_(.*);/
file2.write("global.rpg_#{$1} = 0;\n")
end
end
flie2.close