puts "#=============================================================================="
puts "# PCI Sampler"
puts "# By PedroHLC"
puts "# Ver. 0.9"
puts "#------------------------------------------------------------------------------"
puts "# Based on this project: http://blackbeltvb.com/index.htm?free/mcisamp.htm"
puts "#=============================================================================="

require("Win32API.so")

class PCI_Sampler_Class
  HIGHEST_VOLUME_SETTING = 100 #%
  AUX_MAPPER = -1
  MAXPNAMELEN = 32
  AUXCAPS_CDAUDIO = 1     #audio from internal CD-ROM drive
  AUXCAPS_AUXIN = 2       #audio from auxiliary input jacks
  AUXCAPS_VOLUME = 0x01   #supports volume control
  AUXCAPS_LRVOLUME = 0x02 #separate left-right volume control
  MMSYSERR_NOERROR = 0
  MMSYSERR_BASE = 0
  MMSYSERR_BADDEVICEID = (MMSYSERR_BASE + 2)
  
  AUXCAPS = ['0','0','0','','0','0']
    #0 = wMid As Integer
    #1 = wPid As Integer
    #2 = vDriverVersion As Long
    #3 = szPname As String * MAXPNAMELEN
    #4 = wTechnology As Integer
    #5 = dwSupport As Long
  #.pack('p6')
  VolumeSetting = ['0','0']
    #0 = LeftVol As Integer
    #1 = RightVol As Integer
  #.pack('p2')
  
  def initialize
    puts "Creating PCI Sampler..."
    @GetNumDevs = Win32API.new('winmm.dll','auxGetNumDevs','','l')
    @GetDevCaps = Win32API.new('winmm.dll','auxGetDevCaps','lp','l')
    @SetVolume= Win32API.new('winmm.dll','auxSetVolume','lp','l')
    @GetVolume= Win32API.new('winmm.dll','auxGetVolume','lp','l')
    #@RtlMoveMemory = Win32API.new('kernel32.dll','RtlMoveMemory','LLL','')
    puts "PCI Sampler was suceffuly created!"
  end
  
  def get_Signed(value)
    unsignedInt = value.to_f
    if unsignedInt > 65535 or unsignedInt < 0
      puts "Error in conversion from Unsigned to Signed Integer"
      return 0
    end
    if unsignedInt > 32767
      signed = unsignedInt - 65536
    else
      signed = unsignedInt
    end
    return signed.to_i
  end
  
  def get_Unsigned(value)
    signedInt = value.to_i
    unsigned = 0
    if signedInt < 0
      unsigned = signedInt + 65536
    end
    if unsigned > 65535 or unsigned < 0
      puts "Error in conversion from Signed to Unsigned Integer"
      return 0
    end
    return unsigned
  end
  
  def set_Volume(value0, value1, value2)
    leftVol = value0
    rightVol = value1
    deviceID = value2
    volume = VolumeSetting
    volume[0] = get_Signed(leftVol * 65535 / HIGHEST_VOLUME_SETTING).to_s
    volume[1] = get_Signed(rightVol * 65535 / HIGHEST_VOLUME_SETTING).to_s
    bothVol  = volume.pack('p2') #copy our Volume-variable to a long
    @SetVolume.call(deviceID, bothVol) #call the SetVolume-function
    return 0
  end
  
  def example
    #create default variables
    volume = VolumeSetting
    ac = AUXCAPS
    numDevs = (@GetNumDevs.call - 1).to_i #auxGetNumDevs is zero-based
    #check devs
    if numDevs < 0
      puts "No devices founded."
      return
    end
    #loop through all the devices
    puts "Starting check all devices"
    for cnt in 0..numDevs
      #get the volume
      volume_buffer = volume.pack('p2')
      @GetVolume.call(cnt, volume_buffer)
      volume = volume_buffer.unpack('p2')
      #get the device capabilities
      ac_buffer = ac.pack('p6')
      @GetDevCaps.call(cnt, ac_buffer)
      ac = ac_buffer.unpack('p6')
      #print the name on the form
      puts("Device #" + (cnt + 1).to_s + ":  " + ac[3].to_s.strip)
      #print the left- and right volume on the form
      puts("Left volume:" + get_Unsigned(HIGHEST_VOLUME_SETTING * get_Unsigned(volume[0]) / 65535).to_s)
      puts("Right volume:" + get_Unsigned(HIGHEST_VOLUME_SETTING * get_Unsigned(volume[1]) / 65535).to_s)
      #set the left- and right-volume to 50%
      set_Volume(50, 50, cnt)
      puts "Both volumes now set to 50%"
    end
    puts "All tasks suceffuly completed!"
  end
end

PCI_Sampler = PCI_Sampler_Class.new
PCI_Sampler.example

puts "Push Return/Enter to exit..."
gets