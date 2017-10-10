puts('Video Bitrate Calculator')
puts('Created by PedroHLC')
puts('Version: 0.6')

#1.000.000.000
$CODEC = []
$CODEC[0] = 0
$CODEC[1] = 78125
$CODEC[2] = 104167
$CODEC[3] = 104167
$CODEC[4] = 723379.7

puts('Lista de codecs:')
puts('1.  MP4 MPEG4(AVC-H264)')
puts('2.  MP4 MPEG4(Divx)')
puts('3.  MP4 MPEG4(Xvid)')
puts('4.  AVI MJPEG')
puts('5.  3GP H263')
puts('6.  RM* RV40')
puts('7.  WMV WMV2')
puts('8.  MKV MATROSKA(AVC-H264)')
puts('9.  MKV MATROSKA(Divx)')
puts('10. MPG MPEG2')
puts('11. MOV QUICKTIME(AVC-H264)')
puts('12. SWF FLV')
puts('')

loop do
  print('Selecione o codec de video(somente numero):')
  codec_id = gets.to_i
  if $CODEC[codec_id].nil?
    puts('Este codec de video nao existe')
  else
    break
  end
end

print('Digite a largura do video:')
width = gets.to_i
print('Digite a altura do video:')
heigh = gets.to_i
print('Digite o FPS do video:')
fps = gets.to_f

kbs = ((width * heigh * fps * $CODEC[codec_id]) / 1000000000).to_i.to_s
puts("KB\s adequado: #{kbs}")
gets