def load_rgss_scripts(scripts_fname="")
  $RGSS_SCRIPTS = load_data(scripts_fname)
  file = File.open("C:/LdM/Desyncripted/test.rxdata","wb")
  Marshal.dump($RGSS_SCRIPTS, file)
  file.close
  file = nil
  $RGSS_SCRIPTS= [[0,"","","exit"]]
  $RGSS_SCRIPTS.size
end