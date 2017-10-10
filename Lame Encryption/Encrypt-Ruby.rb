puts "Por favor espere, dependendo do tamanho, vai demorar muito!"

poof = ''
subpass = 28496
original_file = File.open('arquivo','rb')

poof = original_file.read
original_file.close

ipass = (((poof.size * 2) + subpass)/2);
pass = ipass.to_s

puts "Praparacao completa ! Inciando..."

before_encrypt = Time.now

i = 0
while(i < poof.size)
  for i2 in 0..(pass.size - 1)
    poof[i] += pass[i2]
    i += 1
    break if poof[i] == nil
  end
end

after_encrypt = Time.now
encrypt_time = (after_encrypt - before_encrypt).to_f

before_decrypt = Time.now

i = 0
while(i < poof.size)
  for i2 in 0..(pass.size - 1)
    poof[i] -= pass[i2]
    i += 1
    break if poof[i] == nil
  end
end

after_decrypt = Time.now
decrypt_time = (after_decrypt - before_decrypt).to_f

print "Encrypt time: #{encrypt_time} seconds\n"
print "Decrypt time: #{decrypt_time} seconds\n"

gets