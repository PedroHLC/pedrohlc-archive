=begin
RGSS200E )RPG Maker VX( Descompiled Data
by: PedroHLC
(Load Script Area)
=end

$@[0].to_s.sub(/:.*/,'')
$@[0].to_s.sub(/.*?:/,'').to_i
$@[0].to_s.sub(/.*?:/,'').to_i
$@[0].to_s.sub(/Section/,'').sub(/:.*/,'').to_i

while $@[0].to_s[0..5] == '(eval)' and $@.size > 1

Graphics._reset
Input.update
Audio.me_stop
Audio.se_stop
Audio.bgm_stop
Audio.bgs_stop
GC.start

$RGSS_SCRIPTS[%d][3]

$RGSS_SCRIPTS[$@[0].to_s.sub(/Section/,'').sub(/:.*/,'').to_i][1]

$RGSS_SCRIPTS = load_data(scripts_fname)
$RGSS_SCRIPTS.each { |s| s[3,0] = Zlib::Inflate.inflate(s[2]) }
$RGSS_SCRIPTS.size