puts "-----------------------------"
puts "Gerador de CPF"
puts " "
puts "Versao: 1.2 BETA"
puts "Criado por: Alexx Ware"
puts "Compilado por: PedroHLCC"
puts "-----------------------------"
puts "Pressione ENTER para gerar um novo CPF:\n"
loop do
gets
a = [rand(10),rand(10),rand(10),rand(10),rand(10),rand(10),rand(10),rand(10),rand(10)]
b = [rand(10),rand(10),rand(10),rand(10),rand(10),rand(10),rand(10),rand(10),rand(10)]
q = [rand(12),rand(12),rand(12),rand(12),rand(12),rand(12),rand(12),rand(12),rand(12), rand(12)]
w = [rand(12),rand(12),rand(12),rand(12),rand(12),rand(12),rand(12),rand(12),rand(12), rand(12)]
c = []
g = []
c[0] = a[0] * b[0]
c[1] = a[1] * b[1]
c[2] = a[2] * b[2]
c[3] = a[3] * b[3]
c[4] = a[4] * b[4]
c[5] = a[5] * b[5]
c[6] = a[6] * b[6]
c[7] = a[7] * b[7]
c[8] = a[8] * b[8]

d = c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8]
resto = d % 11
quo = d / 11


if (resto < 2)
  digito1 = 0
else
  u = 11 - resto
  digito2 = u
end 
   
g[0] = q[0] * w[0]
g[1] = q[1] * w[1]
g[2] = q[2] * w[2]
g[3] = q[3] * w[3]
g[4] = q[4] * w[4]
g[5] = q[5] * w[5]
g[6] = q[6] * w[6]
g[7] = q[7] * w[7]
g[8] = q[8] * w[8]
g[9] = q[9] * w[9]

k = g[0] + g[1] + g[2] + g[3] + g[4] + g[5] + g[6] + g[7] + g[8] + g[9]

resto = k % 11
quo = k / 11

if (resto < 2)
  digito1 = 0
else
  u = 11 - resto
  digito2 = u
end
f = [digito1,digito2]
#n = a + f
puts  ("CPF Gerado: " + a.to_s + "-" + f.to_s)
end