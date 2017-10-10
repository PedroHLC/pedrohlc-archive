$RGSS_SCRIPTS = load_data(scripts_fname)
$RGSS_SCRIPTS.each { |s| s[3,0] = Zlib::Inflate.inflate(s[2]) }
$RGSS_SCRIPTS.size