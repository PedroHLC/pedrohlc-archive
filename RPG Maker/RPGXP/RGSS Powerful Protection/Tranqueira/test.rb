name = "aha"
if name != "" and File.exist?('./' + name + '.rma')
  puts "Aha1"
else
  puts "Aha2"
end