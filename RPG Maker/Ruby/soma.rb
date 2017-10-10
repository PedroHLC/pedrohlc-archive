bill_list = File.open("./bill.txt", 'rb').readlines
full_bill = 0.0
for bill in bill_list
  bill_f = bill.to_s.strip.to_f
  next if bill_f <= 0
  full_bill += bill_f
end
puts "Soma total: #{full_bill}"
puts "Renda por dia: #{(full_bill / 18)}"
puts "Comissao: #{((2 * full_bill) / 100)}"
gets