puts "Loading"
$a = 0
$b = (-3)
$c = []
Thread.new{
  old_sec = Time.now.sec
  loop do
    if old_sec != Time.now.sec
      old_sec = Time.now.sec
      counter = ($a * 2.2).to_i
      $c.push(counter) if $b >= 1
      puts counter.to_s + " LPS" if $b >= 1
      $b += 1
      $a = 0
    end
    break if $b >= 8
  end
}
loop do
  $a +=1
  break if $b >= 8
end

$d = 0
for i in 0..($c.size - 1)
  $d += $c[i]
end
puts "\nMedia: #{$d} LPS\n"
gets