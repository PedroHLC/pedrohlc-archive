#==============================================================================
#
#                   (Dir,FileTest) Correct
#                    1.0
#
#                    by: Pedro(HCDO)
#                        Renan(RTH)
#                               
#                        (PRCoders)
#
#==============================================================================
#   Este script corrige alguns bugs do Dir e FileTest do RGSS,
# ao procurar arquivos com Dir, ou usar funções do FileTest
# usando nome de arquivos ou diretorios com acentos.
#==============================================================================

#==============================================================================
# module Dir
#==============================================================================

class Dir
 
  # File Attribute Constants
 
  FILE_ATTRIBUTE_ARCHIVE = 0x20
  FILE_ATTRIBUTE_COMPRESSED = 0x800
  FILE_ATTRIBUTE_DEVICE = 0x40
  FILE_ATTRIBUTE_DIRECTORY = 0x10
  FILE_ATTRIBUTE_ENCRYPTED = 0x4000
  FILE_ATTRIBUTE_NORMAL = 0x80
  FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = 0x2000
  FILE_ATTRIBUTE_OFFLINE = 0x1000
  FILE_ATTRIBUTE_READONLY = 0x1
  FILE_ATTRIBUTE_REPARSE_POINT = 0x400
  FILE_ATTRIBUTE_SPARSE_FILE = 0x200
  FILE_ATTRIBUTE_SYSTEM = 0x4
  FILE_ATTRIBUTE_TEMPORARY = 0x100
  FILE_ATTRIBUTE_VIRTUAL = 0x10000
  INVALID_FILE_ATTRIBUTES = -1

  # File
 
  GENERIC_READ = 0x80000000
  FILE_SHARE_READ = 0x00000001
  OPEN_EXISTING = 3
  INVALID_HANDLE_VALUE = -1
  MAX_PATH = 260
 
  MultiByteToWideChar = Win32API.new("kernel32", "MultiByteToWideChar", "iipipi", "l")
  WideCharToMultiByte = Win32API.new("kernel32", "WideCharToMultiByte", "iipipiii", "l")
  GetFileAttributes = Win32API.new("kernel32", "GetFileAttributes", "p", "i")
  FileOpen = Win32API.new("kernel32", "CreateFile", "pllliii", "l")
  GetFileSize = Win32API.new("kernel32", "GetFileSize", "pi", "l")
  CloseHandle = Win32API.new("kernel32", "CloseHandle", "l", "i")
  FindFirstFile = Win32API.new("kernel32", "FindFirstFile", "pp", "i")
  FindNextFile = Win32API.new("kernel32", "FindNextFile", "pp", "i")
  FindClose = Win32API.new("kernel32", "FindClose", "l", "i")
 
  CP_UTF8 = 65001
  CP_ACP = 0
 
  #--------------------------------------------------------------------------
  # Converte Str
  #--------------------------------------------------------------------------
 
  def self.StrConvert(str, from, to, strlen = -1)
    # Pega o tamanho do buffer temporario
    len   = MultiByteToWideChar.call(from, 0, str, strlen, nil, 0)
    temp  = "\0\0" * len
    # Faz a converção
    MultiByteToWideChar.call(from,  0,  str, strlen, temp, len)
    # Pega o tamanho do buffer de saida
    len2  = WideCharToMultiByte.call(to, 0, temp, len, nil, 0, 0, 0)
    saida = "\0" * len2
    # Faz a converção
    WideCharToMultiByte.call(to, 0, temp, len, saida, len2, 0, 0)
    return saida
  end
 
  #--------------------------------------------------------------------------
  # Passa Unicode para Ansi
  #--------------------------------------------------------------------------
 
  def self.UnicodeToAnsi(string)
    return string.unpack("U*").pack("C*").delete("\0")
  end
 
  #--------------------------------------------------------------------------
  # Passa Ansi para Unicode
  #--------------------------------------------------------------------------
 
  def self.AnsiToUnicode(string)
    return string.unpack("C*").pack("U*").delete("\0")
  end
 
  #--------------------------------------------------------------------------
  # Verifica atributo
  #--------------------------------------------------------------------------
 
  def self.FileAttribute?(filename, attribute)
    r = GetFileAttributes.call(UnicodeToAnsi(filename))
    return false if r == INVALID_FILE_ATTRIBUTES
    (r & attribute) == attribute
  end
 
  #--------------------------------------------------------------------------
  # Verifica se o arquivo existe
  #--------------------------------------------------------------------------
 
  def self.FileExist?(filename)
    if GetFileAttributes.call(UnicodeToAnsi(filename)) == INVALID_FILE_ATTRIBUTES
      return false
    else
      return true
    end
  end
 
  #--------------------------------------------------------------------------
  # Pega o tamanho do arquivo
  #--------------------------------------------------------------------------
 
  def self.GetFileSize(filename)
    file = FileOpen.call(UnicodeToAnsi(filename), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0)
    return 0 if file == INVALID_HANDLE_VALUE
    size = GetFileSize.call(file, 0)
    CloseHandle.call(file)
    return size
  end
 
  #--------------------------------------------------------------------------
  # Corrige o nome do arquivo
  #--------------------------------------------------------------------------
 
  def self.format_filename(filename)
    spl = filename.split("")
    loop do
      if spl.empty?
        break
      elsif spl[0] == " "
        spl.delete_at(0)
      elsif spl[spl.size-1] == " "
        spl.delete_at(spl.size-1)
      else
        break
      end
    end
    spl.join("")
  end
 
  #--------------------------------------------------------------------------
  # Procura os arquivos
  #--------------------------------------------------------------------------
  
  def self.find_files(dir, type)
    type = format_filename(type)
    if type == "*"
      type = "*.*"
    end
   
    if !FileTest.directory?(dir)
      return ["#{dir}/#{type}"]
    end
   
    files = []
   
    buff = "\0\0\0\0" * 11 + "\0" * (14 + MAX_PATH)
   
    ffile = FindFirstFile.call(UnicodeToAnsi("#{dir}/#{type}"), buff)
   
    if ffile == INVALID_HANDLE_VALUE
      return []
    end
   
    filef = buff.unpack("LLLLLLLLLLLc#{MAX_PATH}c14")
    file = AnsiToUnicode(filef[11...271].pack("c260"))
   
    if file != "" and
      file != "." and
      file != ".."
      files << file
    end

    loop do
      buff[0...buff.size] = ""
      buff = filef[0...11].pack("LLLLLLLLLLL") + ("\0" * (14 + MAX_PATH))
      if FindNextFile.call(ffile, buff) == 0
        break
      else
        filef = buff.unpack("LLLLLLLLLLLc#{MAX_PATH}C14")
        len = 0
        for i in 11...271
          break if (filef[i] == 0)
          len += 1
        end       
        file = AnsiToUnicode(filef[11...271].pack("c260"))
        if file != "" and
          file != "." and
          file != ".."

          files << file
        end
      end
    end
   
    FindClose.call(ffile)
   
    for i in 0...files.size
      j = files[i]
      files[i] = dir + "/" + j
    end
   
    files
  end
 
  #--------------------------------------------------------------------------
  # Pega os arquivos de uma pasta
  #--------------------------------------------------------------------------
 
  def self.[](dir)
    find_files(File.dirname(dir), File.basename(dir))
  end
end

#==============================================================================
# module FileTest
#==============================================================================

module FileTest
 
  #--------------------------------------------------------------------------
  # Verifica se é uma pasta
  #--------------------------------------------------------------------------
 
  def self.directory?(filename)
    Dir.FileAttribute?(filename, Dir::FILE_ATTRIBUTE_DIRECTORY)
  end
 
  #--------------------------------------------------------------------------
  # Verifica se é um arquivo
  #--------------------------------------------------------------------------
 
  def self.file?(filename)
    Dir.FileAttribute?(filename, Dir::FILE_ATTRIBUTE_ARCHIVE)
  end
 
  #--------------------------------------------------------------------------
  # Verifica se o arquivo existe
  #--------------------------------------------------------------------------
 
  def self.exist?(filename)
    Dir.FileExist?(filename)
  end
 
  #--------------------------------------------------------------------------
  # Verifica o tamanho do arquivo
  #--------------------------------------------------------------------------
 
  def self.size(filename)
    if !exist?(filename) or
      !file?(filename)
      return 0
    end
    return Dir.GetFileSize(filename)
  end
end
