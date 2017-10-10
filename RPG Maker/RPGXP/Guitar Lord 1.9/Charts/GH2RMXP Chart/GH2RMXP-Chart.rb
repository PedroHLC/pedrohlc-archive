puts "================================================================="
puts " GH 2 RMXP Chart"
puts " Version: 0.57"
puts " By: PedroHLC"
puts "-----------------------------------------------------------------"
puts " Use esse aplicativo para converter '.chart' para '.rmxpchart'"
puts "================================================================="

loop do
  puts "Insira o nome do arquivo a ser convertido"
  $gh_file_path = gets.to_s.strip
  if FileTest.exist?($gh_file_path)
    puts "Iniciando a convercao..."
    $gh_file = File.open($gh_file_path, "r").read
    break
  else
    if FileTest.exist?($gh_file_path+".chart")
      $gh_file_path = ($gh_file_path+".chart")
      puts "Iniciando a convercao..."
      $gh_file = File.open($gh_file_path, "r").read
      break
    else
      puts "O arquivo '#{$gh_file_path}' nao pode ser encontrado"
    end
  end
end

$star_power_list = []
$ts = 40

$rmxpchart_file = {}
$rmxpchart_file["Type"] = "GH2RMXP Chart"
$rmxpchart_file["Info"] = {}
$rmxpchart_file["Events"] = []
$rmxpchart_file["ExpertSpecial"] = []
$rmxpchart_file["Expert"] = []
$rmxpchart_file["Hard"] = []
$rmxpchart_file["Medium"] = []
$rmxpchart_file["Easy"] = []
$rmxpchart_file["Sync"] = []
$rmxpchart_file["Last"] = 0

def convert_line(line)
  return if line.empty? or line.strip == "{"
  if line.strip == "}"
    $gh_file_local = ''
    return
  end
  if line.strip == "[Song]"
    $gh_file_local = 'SONG-Configs'
    puts "#Informacoes sobre a faixa detectadas"
    return
  end
  if line.strip == "[SyncTrack]"
    $gh_file_local = 'SyncTrack'
    puts "#Sincronismo detectado"
    return "Local: SONG-Sync"
  end
  if line.strip == "[Events]"
    $gh_file_local = 'Events'
    puts "#Eventos detectados"
    return
  end
  if line.strip == "[ExpertSingle]"
    $gh_file_local = 'Expert'
    puts "#Expert detectado"
    return
  end
  if line.strip == "[HardSingle]"
    $gh_file_local = 'Hard'
    puts "#Hard detectado"
    return
  end
  if line.strip == "[MediumSingle]"
    $gh_file_local = 'Medium'
    puts "#Medium detectado"
    return
  end
  if line.strip == "[EasySingle]"
    $gh_file_local = 'Easy'
    puts "#Easy detectado"
    return
  end
  return if $gh_file_local == 'Ingnore'
  case $gh_file_local.strip
  when 'SONG-Configs'
    case line.strip
    when /(.*) = "(.*)"$/
      $rmxpchart_file["Info"][$1.to_s.strip] = $2.to_s.strip
    when /(.*) = (.*)$/
      $rmxpchart_file["Info"][$1.to_s.strip] = $2.to_s.strip.to_i
    end
  when 'SyncTrack'
    case line.strip
    when /(.*) = TS (.*)$/
      $ts = $2.to_s.strip.to_i
      puts ">Novo TS: #{$ts}"
    when /(.*) = B (.*)$/
      $rmxpchart_file["Sync"][($1.to_s.strip.to_i / 10)] = ((($2.to_s.strip.to_f / 600).to_f / 120).to_f * 40).to_i #((Convert p/ segundo) divide pelo BPM pardrão) multiplica pelo FPS padrão
    end
    $rmxpchart_file["Last"] = $1.to_i if $1.to_i > $rmxpchart_file["Last"]
  when 'Events'
    case line.strip
    when /(.*) = E (.*)$/
      if !$rmxpchart_file["Events"][($1.to_s.strip.to_i / 10)].is_a?(Array)
        $rmxpchart_file["Events"][($1.to_s.strip.to_i / 10)] = [$2.to_s.strip]
      else
        $rmxpchart_file["Events"][($1.to_s.strip.to_i / 10)].push($2.to_s.strip)
      end
    end
    $rmxpchart_file["Last"] = $1.to_i if $1.to_i > $rmxpchart_file["Last"]
  when 'Expert'
    case line.strip
    when /(.*) = N (.*) (.*)$/
      if !$rmxpchart_file["Expert"][($1.to_s.strip.to_i / 10)].is_a?(Array)
        $rmxpchart_file["Expert"][($1.to_s.strip.to_i / 10)] = [[$2.to_s.strip.to_i,$3.to_s.strip.to_i]]
      else
        $rmxpchart_file["Expert"][($1.to_s.strip.to_i / 10)].push([$2.to_s.strip.to_i,$3.to_s.strip.to_i])
      end
    when /(.*) = S 2 (.*)$/
      slimit = $2.to_s.strip.to_i
      if $star_power_list[slimit] != true
        $rmxpchart_file["ExpertSpecial"][($1.to_s.strip.to_i / 10)] = slimit
        $star_power_list[slimit] = true
      end
    end
    $rmxpchart_file["Last"] = $1.to_i if $1.to_i > $rmxpchart_file["Last"]
  when 'Hard'
    case line.strip
    when /(.*) = N (.*) (.*)$/
      if !$rmxpchart_file["Hard"][($1.to_s.strip.to_i / 10)].is_a?(Array)
        $rmxpchart_file["Hard"][($1.to_s.strip.to_i / 10)] = [[$2.to_s.strip.to_i,$3.to_s.strip.to_i]]
      else
        $rmxpchart_file["Hard"][($1.to_s.strip.to_i / 10)].push([$2.to_s.strip.to_i,$3.to_s.strip.to_i])
      end
    end
    $rmxpchart_file["Last"] = $1.to_i if $1.to_i > $rmxpchart_file["Last"]
  when 'Medium'
    case line.strip
    when /(.*) = N (.*) (.*)$/
      if !$rmxpchart_file["Medium"][($1.to_s.strip.to_i / 10)].is_a?(Array)
        $rmxpchart_file["Medium"][($1.to_s.strip.to_i / 10)] = [[$2.to_s.strip.to_i,$3.to_s.strip.to_i]]
      else
        $rmxpchart_file["Medium"][($1.to_s.strip.to_i / 10)].push([$2.to_s.strip.to_i,$3.to_s.strip.to_i])
      end
    end
    $rmxpchart_file["Last"] = $1.to_i if $1.to_i > $rmxpchart_file["Last"]
  when 'Easy'
    case line.strip
    when /(.*) = N (.*) (.*)$/
      if !$rmxpchart_file["Easy"][($1.to_s.strip.to_i / 10)].is_a?(Array)
        $rmxpchart_file["Easy"][($1.to_s.strip.to_i / 10)] = [[$2.to_s.strip.to_i,$3.to_s.strip.to_i]]
      else
        $rmxpchart_file["Easy"][($1.to_s.strip.to_i / 10)].push([$2.to_s.strip.to_i,$3.to_s.strip.to_i])
      end
    end
    $rmxpchart_file["Last"] = $1.to_i if $1.to_i > $rmxpchart_file["Last"]
  end
  return
end

$gh_file.each_line {|line|
  convert_line(line)
}

case $gh_file_path
when /(.*).chart$/
  final_file = File.open($1.to_s.strip+".rmxpchart", "wb")
  Marshal.dump($rmxpchart_file, final_file)
  final_file.close
else
  final_file = File.open($gh_file_path+".rmxpchart", "wb")
  Marshal.dump($rmxpchart_file, final_file)
  final_file.close
end

puts "O arquivo foi convertido com sucesso! Pressione ENTER para finalizar!"
gets