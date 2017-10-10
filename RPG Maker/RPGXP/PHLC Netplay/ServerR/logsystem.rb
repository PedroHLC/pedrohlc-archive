FileUtils.mkdir("./debug") if !FileTest.exist?("./debug")
FileUtils.mkdir("./debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/") if !FileTest.exist?("./debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/")

$log_folder = "./debug/#{Time.now.day}-#{Time.now.month}-#{Time.now.year}/"

def log(type, object, message)
  file = File.open($log_folder + type.to_s.upcase + ".txt", "a+")
  final = "#{Time.now} => #{object}: #{message}\n"
  file.write(final)
  file.close
  puts("#{object}: #{message}") if Settings::PRINT_PACKETS
end