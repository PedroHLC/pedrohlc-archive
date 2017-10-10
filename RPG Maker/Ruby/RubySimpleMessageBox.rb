#====================================================
# RubySimpleMessageBox
# By: PedroHLC
# Ver: 1.0
#====================================================
require 'Win32API'
module MessageBox
  @data = Win32API.new('user32', 'MessageBox', 'ippi', 'i')
  def self.call(data='', title='',type=64)
    if type < 0
      @data.call(0, "As MessageBoxs variam de 0 Ã  9!","RubySimpleMessageBox", 64)
      return 'error'
    end
    if type > 80
      @data.call(0, "Somente Existe 79 tipos de MessageBoxs!","RubySimpleMessageBox", 64)
      return 'error'
    end
    result = @data.call(0, data, title,type)
    return result
  end
end
for i in 0..80
  puts i
  MessageBox.call('ã','ç',i)
end