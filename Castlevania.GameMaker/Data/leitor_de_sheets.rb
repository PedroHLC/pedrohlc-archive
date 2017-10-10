pagina = File.open('.\page.txt','rb').readlines
links = File.open('.\links.txt','w')
for line in pagina
  if line =~ /<a href="sheet\/(.*)"><img src=/
    links.write("http://www.spriters-resource.com/psx_ps2/cvsotn/sheet/#{$1}/\n")
  end
end
links.close