begin
  require 'wx'
  require 'zip/zip'
####-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
### Module Rxdata
####-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
## Autores:
##  HugoLnx/HugoLinux
##  PedroHLC
###-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

module RXDATA
  require 'zlib'
  def insert(path,title,code)
    File.open(path,'rb'){ |rxdata_file|
      @rxdata_array = Marshal.load(rxdata_file)
    }
    @rxdata_array.each_with_index{|rx_script,i|
      if rx_script[1] == 'Main'
        @rxdata_array.insert(i,[0,title,Zlib::Deflate.deflate(code)])
        File.open(path,'wb'){|rxdata_file|
          rxdata_file << Marshal.dump(@rxdata_array,rxdata_file)
        } 
        break
      end
    }
  end
  def add_from_rxmod(proj_path,scripts)
      scripts.each{|script|
        insert("#{proj_path}/Data/Scripts.rxdata", script[0], script[2])
      }
    #end
  end
  module_function :insert
  module_function :add_from_rxmod
end

module RXMOD
  def load(file)
    zipfile = nil
    @graphics = nil
    @audios = nil
    Zip::ZipFile.open(file, true) { |zipfile|
      eval(zipfile.read("Inf/info.txt").to_s)
      for i in 0..(@scripts.size-1)
        file_name = "Inf/"+@scripts[i][1].to_s
        @scripts[i].push(zipfile.read(file_name).to_s)
      end
      if @graphics != nil
        for i in 0..(@graphics.size-1)
          file_name =  @graphics[i][0].to_s + @graphics[i][1].to_s
          @graphics[i].push(zipfile.read(file_name).to_s)
        end 
      end
      if @audios != nil
        for i in 0..(@audios.size-1)
          file_name =  @audios[i][0].to_s + @audios[i][1].to_s
          @audios[i].push(zipfile.read(file_name).to_s)
        end 
      end
      zipfile.close
      return [@scripts,@graphics,@audios]
    }
  end
  module_function :load
end

module ExtraFiles
  def insert(path, dir, name, value)
    if value == "" or value == nil
      return
    end
    file =  File.open(path+dir+name,'wb')
    file.write(value)
    file.close
  end
  def add_graphics(graphics,proj_path)
    if graphics == nil or graphics == []
      return
    end
    graphics.each{|graphic|
        insert("#{proj_path}/", graphic[0], graphic[1], graphic[2])
      }
  end
  def add_audios(audios,proj_path)
    if audios == nil or audios == []
      return
    end
    audios.each{|audio|
        insert("#{proj_path}/", audio[0], audio[1], audio[2])
      }
  end
  module_function :insert  
  module_function :add_graphics
  module_function :add_audios
end

  DIR_EXPL_TXT_ID = 0
  DIR_PATH_TXT_ID = 1
  DIR_BTN_TXT_ID = 2
  
  FILE_EXPL_TXT_ID = 3
  FILE_PATH_TXT_ID = 4
  FILE_BTN_TXT_ID = 5
  
  INSTALL_BTN_ID = 6
  class MainFrameWidgets
    attr_accessor :dir_expl_txt, :dir_path_txt, :dir_btn , :file_expl_txt, :file_path_txt, 
      :file_btn, :install_btn, :win_msg
    def initialize(main_frame)
      @dir_expl_txt = Wx::StaticText.new(
        main_frame, 
        :id => DIR_EXPL_TXT_ID,
        :label => 'Indique o diretorio do projeto',
        :pos => [10,10],
        :name => 'dir_expl_txt',
        :style => Wx::ST_NO_AUTORESIZE)
      dir_expl_txt_x = @dir_expl_txt.get_position.x
      dir_expl_txt_y = @dir_expl_txt.get_position.y 
      dir_expl_txt_h = @dir_expl_txt.get_size.height 
      @dir_path_txt = Wx::TextCtrl.new(
        main_frame, 
        :id => DIR_PATH_TXT_ID,
        :pos => [dir_expl_txt_x,dir_expl_txt_y+dir_expl_txt_h],
        :size => [300,Wx::DEFAULT_SIZE.height])
      dir_path_txt_x = @dir_path_txt.get_position.x  
      dir_path_txt_y = @dir_path_txt.get_position.y
      dir_path_txt_w = @dir_path_txt.get_size.width
      dir_path_txt_h = @dir_path_txt.get_size.height
      @dir_btn = Wx::Button.new(
        main_frame, 
        :id => DIR_BTN_TXT_ID,
        :label => '...',
        :pos => [dir_path_txt_x + dir_path_txt_w,dir_path_txt_y],
        :size => [30,dir_path_txt_h])
        
      dir_path_txt_x = @dir_path_txt.get_position.x
      dir_path_txt_y = @dir_path_txt.get_position.y 
      dir_path_txt_h = @dir_path_txt.get_size.height   
      
        
      @file_expl_txt = Wx::StaticText.new(
        main_frame, 
        :id => FILE_EXPL_TXT_ID,
        :label => 'Indique o arquivo .rxmod',
        :pos => [dir_path_txt_x,dir_path_txt_y+dir_path_txt_h + 10],
        :style => Wx::ST_NO_AUTORESIZE)
      file_expl_txt_x = @file_expl_txt.get_position.x
      file_expl_txt_y = @file_expl_txt.get_position.y 
      file_expl_txt_h = @file_expl_txt.get_size.height 
      @file_path_txt = Wx::TextCtrl.new(
        main_frame, 
        :id => FILE_PATH_TXT_ID,
        :pos => [file_expl_txt_x,file_expl_txt_y+file_expl_txt_h],
        :size => [300,Wx::DEFAULT_SIZE.height],
        :name => 'file_path_txt')
      file_path_txt_x = @file_path_txt.get_position.x  
      file_path_txt_y = @file_path_txt.get_position.y
      file_path_txt_w = @file_path_txt.get_size.width
      file_path_txt_h = @file_path_txt.get_size.height
      @file_btn = Wx::Button.new(
        main_frame, 
        :id => FILE_BTN_TXT_ID,
        :label => '...',
        :pos => [file_path_txt_x + file_path_txt_w,file_path_txt_y],
        :size => [30,file_path_txt_h])
      @install_btn = Wx::Button.new(
        main_frame, 
        :id => INSTALL_BTN_ID,
        :label => 'Instalar',
        :pos => [file_path_txt_x,file_path_txt_y + file_path_txt_h + 10],
        :style => Wx::BU_EXACTFIT)
        
    end 
  end  

  class MainFrame < Wx::Frame
    def initialize
      super(nil,
        :title => 'XP Easy Script Installer',
        :size => [355,176],
        :style => Wx::DEFAULT_FRAME_STYLE & ~ (Wx::RESIZE_BORDER|Wx::RESIZE_BOX|Wx::MAXIMIZE_BOX))
      @widgets = MainFrameWidgets.new(self)  
      declare_events
    end
    def declare_events
      evt_button(@widgets.dir_btn.get_id,:on_dir_click)
      evt_button(@widgets.file_btn.get_id,:on_file_click)
      evt_button(@widgets.install_btn.get_id,:on_install_click)
    end  

    def on_dir_click
      if File.exist?(@widgets.dir_path_txt.value)
        dir_dialog = Wx::DirDialog.new(self, "Escolha um diretório",@widgets.dir_path_txt.value)
      else
        dir_dialog = Wx::DirDialog.new(self, "Escolha um diretório")
      end  
      result = dir_dialog.show_modal
      if result == Wx::ID_OK
        @widgets.dir_path_txt.value = dir_dialog.get_path
      end 
    end 
    def on_file_click
      if File.exist?(@widgets.file_path_txt.value)
        if File.directory?(@widgets.file_path_txt.value)
          path_aux = @widgets.file_path_txt.value
        else
          path_aux = File.dirname(@widgets.file_path_txt.value)
        end  
        file_dialog = Wx::FileDialog.new(self, "Escolha um arquivo .rxmod",
          path_aux, :wildcard => '*.rxmod')
      else
        file_dialog = Wx::FileDialog.new(self, "Escolha um arquivo .rxmod",
          :wildcard => '*.rxmod')
      end  
      result = file_dialog.show_modal
      if result == Wx::ID_OK
        @widgets.file_path_txt.value = file_dialog.get_path
      end 
    end 
    def on_install_click
      proj_path = @widgets.dir_path_txt.value

      if FileTest.exist?("#{proj_path}/Data/Scripts.rxdata")
        if File.exist?(@widgets.file_path_txt.value)
          rxmod_path = @widgets.file_path_txt.value
          rxmod = RXMOD::load(rxmod_path)
          @scripts = rxmod[0]
          @graphics = rxmod[1]
          @audios = rxmod[2]
          RXDATA::add_from_rxmod(proj_path,@scripts)
          ExtraFiles::add_graphics(@graphics,proj_path)
          ExtraFiles::add_audios(@audios,proj_path)
          msg = 'O script foi instalado com sucesso'     
        else
          msg = 'O arquivo apontado é inválido'
        end 
        
      else
        msg = 'O diretório apontado é inválido'
      end
      win_msg = Wx::MessageDialog.new(self, msg, 
                  "Aviso", 
                  Wx::ICON_INFORMATION)
      win_msg.show_modal 
    end  
  end 
  class MainAplication < Wx::App
    def on_init
      self.app_name = 'XP Easy Script Installer'
      frame = MainFrame.new
      frame.show
    end
  end
  app = MainAplication.new
  app.main_loop
end