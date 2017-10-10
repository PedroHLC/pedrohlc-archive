class MainWindow < Gtk::Window
  alias old_initialize initialize
  def initialize
    old_initialize
    set_window_cfg
    set_edit_cfg
    init_vars
    declare_signals
    agroup_components
    self.show_all
  end
  
  def set_window_cfg
    self.set_icon("./icon.ico")
    self.title = I18n.t(:title) + "(By: PedroHLC)"
    self.deletable=true
    self.move(320, 240)
    self.set_size_request(420,280)
    self.resizable=false
  end
  
  def set_edit_cfg
    @LANGUAGE= $LANGUAGE.to_s
    @HOST = $HOST.to_s
    @PORT = $PORT.to_s
    @SERVERNAME = $SERVERNAME.to_s
    @MOTD = $MOTD.to_s
    @CLIENTFILE = $CLIENTFILE.to_s
    @CLIENTCLASS = $CLIENTCLASS.to_s
    @SQL_U = $SQL_U.to_s
    @SQL_P = $SQL_P.to_s
    @SQL_H = $SQL_H.to_s
    @SQL_DB = $SQL_DB.to_s
    @DEBUG_MSG = $DEBUG_MSG
    @NO_PVP = $NO_PVP
  end
  
  def init_vars
    @start_server_btn = Gtk::Button.new(I18n.t(:server_start))
    #@close_server_btn = Gtk::Button.new(I18n.t(:server_close))
    @exit_btn = Gtk::Button.new(I18n.t(:exit))
    @save_btn = Gtk::Button.new(I18n.t(:save))
    @languange_btn1 = Gtk::RadioButton.new(I18n.t(:english))
    @languange_btn2 = Gtk::RadioButton.new(@languange_btn1,I18n.t(:portuguese))
    @ip_input = Gtk::Entry.new
    @ip_input.text = @HOST
    @port_input =Gtk::Entry.new
    @port_input.text = @PORT
    @sn_input =Gtk::Entry.new
    @sn_input.text = @SERVERNAME
    @mt_input =Gtk::Entry.new
    @mt_input.text = @MOTD
    @cf_input =Gtk::Entry.new
    @cf_input.text = @CLIENTFILE
    @cc_input =Gtk::Entry.new
    @cc_input.text = @CLIENTCLASS
    @sqlu_input =Gtk::Entry.new
    @sqlu_input.text = @SQL_U
    @sqlp_input =Gtk::Entry.new
    @sqlp_input.text = @SQL_P
    @sqlh_input =Gtk::Entry.new
    @sqlh_input.text = @SQL_H
    @sqldb_input =Gtk::Entry.new
    @sqldb_input.text = @SQL_DB
    @debug_msg_btn = Gtk::CheckButton.new(I18n.t(:debug_msg))
    @debug_msg_btn.active=@DEBUG_MSG
    @no_pvp_btn = Gtk::CheckButton.new(I18n.t(:no_pvp))
    @no_pvp_btn.active=@NO_PVP
    case @LANGUAGE
    when "pt_br"
      @languange_btn2.clicked
    else
      @languange_btn1.clicked
    end
  end
  
  def declare_signals
    @start_server_btn.signal_connect(:clicked){
      self.hide
      system("cls")
      Server.new
      system("cls")
      self.show_all
    }
    #@close_server_btn.signal_connect(:clicked){
    #  Server.stop
    #}
    @exit_btn.signal_connect(:clicked){
      Gtk.main_quit
    }
    @save_btn.signal_connect(:clicked){
      rewrite_configs
    }
    @languange_btn1.signal_connect(:clicked){
      @LANGUAGE = "en"
      I18n.locale = :en
      update_texts
    }
    @languange_btn2.signal_connect(:clicked){
      @LANGUAGE = "pt_br"
      I18n.locale = :pt_br
      update_texts
    }
    @debug_msg_btn.signal_connect(:clicked){
      if @DEBUG_MSG
        @DEBUG_MSG = false
      else
        @DEBUG_MSG = true
      end
    }
    @no_pvp_btn.signal_connect(:clicked){
      if @NO_PVP
        @NO_PVP = false
      else
        @NO_PVP = true
      end
    }
    self.signal_connect(:delete_event){
      Gtk.main_quit
    }
  end
  
  def agroup_components
    #Creat Layout
    table = Gtk::Layout.new
    table.set_size(420, 280)
    table.put(@start_server_btn,10,240)
    table.put(@exit_btn,60,240)
    #table.put(@close_server_btn,110,240)
    table.put(@save_btn, 360, 240)
    #Creat Inputs
    table.put(@ip_input, 10, 35)
    table.put(@port_input, 220, 35)
    table.put(@mt_input, 10, 70)
    table.put(@sn_input, 220, 70)
    table.put(@cf_input, 10, 105)
    table.put(@cc_input, 220, 105)
    table.put(@sqlu_input, 10, 140)
    table.put(@sqlp_input, 220, 140)
    table.put(@sqlh_input, 10, 175)
    table.put(@sqldb_input, 220, 175)
    table.put(@debug_msg_btn,220,210)
    table.put(@no_pvp_btn,10,210)
    #Criate HBox
    hbox = Gtk::HBox.new(true)
    hbox.add(@languange_btn1)
    hbox.add(@languange_btn2)
    #See table
    table.put(hbox,10,5)
    self.add(table)
  end  
  
  def update_texts
    @start_server_btn.label = I18n.t(:server_start)
    #@close_server_btn.label = I18n.t(:server_close)
    @exit_btn.label = I18n.t(:exit)
    @save_btn.label = I18n.t(:save)
    @languange_btn1.label = I18n.t(:english)
    @languange_btn2.label = I18n.t(:portuguese)
    @debug_msg_btn.label = I18n.t(:debug_msg)
    @no_pvp_btn.label = I18n.t(:no_pvp)
    self.title = I18n.t(:title) + " (By: PedroHLC)"
  end
  
  def rewrite_configs
    file =  File.open('Config.cfg', 'wb')
    file.write("$HOST = '#{@ip_input.text}'\n")
    file.write("$PORT = #{@port_input.text}\n")
    file.write("$SERVERNAME = '#{@sn_input.text}'\n")
    file.write("$MOTD = '#{@mt_input.text}'\n")
    file.write("$CLIENTFILE = '#{@cf_input.text}'\n")
    file.write("$CLIENTCLASS = '#{@cc_input.text}'\n")
    if @DEBUG_MSG == true
      file.write("$DEBUG_MSG = true\n")
    else
      file.write("$DEBUG_MSG = false\n")
    end
    if @NO_PVP == true
      file.write("$NO_PVP = true\n")
    else
      file.write("$NO_PVP = false\n")
    end
    file.write("$LANGUAGE = '#{@LANGUAGE}'\n")
    file.write("$SQL_U = '#{@sqlu_input.text}'\n")
    file.write("$SQL_P = '#{@sqlp_input.text}'\n")
    file.write("$SQL_H = '#{@sqlh_input.text}'\n")
    file.write("$SQL_DB = '#{@sqldb_input.text}'\n")
    file.close
    neo_puts(I18n.t(:restart))
    $LANGUAGE = @LANGUAGE.to_s
    $HOST = @ip_input.text.to_s
    $PORT = @port_input.text.to_i
    $SERVERNAME = @sn_input.text.to_s
    $MOTD = @mt_input.text.to_s
    $CLIENTFILE = @cf_input.text.to_s
    $CLIENTCLASS = @cc_input.text.to_s
    $SQL_U = @sqlu_input.text.to_s
    $SQL_P = @sqlp_input.text.to_s
    $SQL_H = @sqlh_input.text.to_s
    $SQL_DB = @sqldb_input.text.to_s
    $DEBUG_MSG = @DEBUG_MSG
    $NO_PVP = @NO_PVP
  end
end