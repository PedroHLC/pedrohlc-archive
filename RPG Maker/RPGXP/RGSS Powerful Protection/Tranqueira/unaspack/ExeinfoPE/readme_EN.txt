___________________________________________________________________________

                                              
      ExeInfo PE ver. 0.0.2.9  by A.S.L  ( c ) 2006.03 - 2011              
                                              
                     freeware version     for Windows XP                    
                                              
   Windows 32 PE executable  file checker , compilators, exe packers ....           
                                              
       with solve hint for unpack  /  internal exe tools / rippers                 
                                              
___________________________________________________________________________




		Internal Tools Menu :
		---------------------

- overlay remover / adder ...                   - generate new file without overlay data , added data from file
- save overlay as external file
- EP Corrector ( for Delphi / C++ 5/6 )         - generate many exe file with Entry Point  
- EP Corrector ( for Delphi v.5 ) Runtime       - correct EP  
- XoR permutator (xor,or,shl..)       		- create one file with xor data ( 255x2000 bytes )
- Section splitter                    		- save exe sections as files & exe header
- Search strin 8 / 16 bit           		- enter 8 bit string = double search - 16 bit strings & 8 bit ( F7 key )
- REGistry call finder + CLSID        		- find registry call &  regedit.exe strings
- overlay xor uncrypter               		- uncrypt one byte crypted exe in ovl. 
- External exe file runner            		- ( from exeinfopeRUN.cfg ) - txt user file list to run
- External exe detector runner                  - from shell registry : Fast Scaner , CFF Explorer , Bit Detector , Quick Unpack ....
- Add fake signer Visual Basic for UPX          - You can add VBasic v5/6 signature to exe file packed with upx.exe



		File Menu :
		--------------------

+ Rename file
+ Copy file As.. *.bak
+ Execute - create executable process  ( exe )
+ Execute - windows ext. associate     ( dll ,zip ... )
+ Delete file ( ALt+Del) - work in multiscan mode
+ Run multifile scanner mode ( Directory scan )
+ kill Windows process
+ - view global log file ( c:\Raport-exeinfo-log.txt ) 
  - delete global log file ( no confirm )


		Rippers Menu : 
		--------------------

- www address searcher inside exe   - work on any file

- ExE inside ExE ( Win32 Pe windows executable)      - work on any file

Archives ripper :

- Zip archives inside ExE  www.winzip.com  - work on any file
- Rar archives inside ExE  www.rarlab.com  - work on any file
- 7z  archives inside ExE  www.7-zip.org   - work on any file
- CAB MS archives inside ExE  (for MSI installers ) - work on any file

- SWF flash Adobe animation files ( internal length fixer for non exe files )
- ICO nonstandard icon ripper

Graphics ripper submenu : 

BMP , 
PNG , 
JPG ( JFIF only !!! Exif - not supported ) , 
GIF ( static pic. only )


- ( All in one ) - for lazy boys ( without 'www address' )


- XML ripper


keys :

F1 key  - keyboard help
F2 key  - Multiple file scanner for *.exe files 
F3 key  - external view ( hiewdemo.exe or hiew32.exe ) path directory
F4 key  - external test ( peid.exe ) path directory
F5 key  - external test RDG Packer Detector ( I read location from Win registry )
F6 key  - external test DiE.exe Detect it Easy  ( I read location from Win registry - shell integration req.)
F7 key  - 8 / 16 bit String finder

F9 key  - UPX.exe  pack ( LZMA ) from path directory
Alt+F9  - UPX.exe  pack ( LZMA + Force mode ) from path directory
F10 key - UPX.exe unpack
Alt+S   - ZOOM Window x2 !
Right Mouse Button - Run external exe detectors - Fast Scanner, CFF Explorer , Quick Unpack ... - required shell integration before !

Alt+Delete - delete file

"+" ,"-" - Numeric KEY =  adjust transparent Form


Non executable file detection :

Image file   - jpg , png , mng ,gif (87/89) , bmp , tiff , TGA new only .
Sound file   - mp3 (ID3/noID) ,wma , ogg , .mid , .xm , .mod , AAC
Video file   - avi (divx/xvid + info ) , wmv , mpg , 3GP , mov , mp4/m4v , .RM , FLV
Archive file - 7zip ,zip ,rar , gzip , bzip

other : chm (Microsoft HTML Help), msi , pdf , xml , fws , cws , php , html , hlp , mdb , lnk ,reg , rtf.
        Linux ELF , .dylib - Mac OS X Universal Binary executable , .class - java






Overlay detector : 


01. zip archives
02. cab archives  
03. SWF Flash object  ( packed & unpacked format )
04. Executable PE file
05. 7zip archives
06. RAR archives
07. MSI/DOC/XLS

- Plugins like a Peid.exe ( 70 % compatible  )



-------------------------

 Multiscaner use - command line : 

- Exeinfope *.sys  ( show all .sys files )

- Exeinfope *.* /s ( Show All PE files and sent to log file ( s = silent mode no GUI !  -> !ExEinfo-Multiscan.log  ) 
  Exeinfope *.exe /s
 
 

-------------------------





*ACM - anti cheat mechanism ( anti fake sign )

_______________________________________________________________________


	www site :      www.exeinfo.xwp.pl


_______________________________________________________________________





	ExeInfo detection list :

]------------------------------------------------[  


001. RealArcade Wrapper ( Microsoft Visual C++ )  
002. Borland Delphi ( 2.0 - 7.0 )
003. Microsoft Visual C++ ver. 5.0 ~ 6.0 ( exe )
004. Microsoft Visual C++ ver. 7.x ( exe ,dll)
005. PEtite 2.x -> Ian Luck
006. UPX exe 0.89.6 - 1.02 / 1.05 - 1.93B -> Markus & Laszlo
007. UPX dll file - 1.93Beta -> Markus & Laszlo
008. Aspack v2.12 -> Alexey Solodovnikov
009. EXECryptor v.2.3.1-6  ( www.strongbit.com )    
010. Morphine ver.2.7b  ( plugin Peid.exe )
 
011. AC protect 2.0 by  RIScO Software Inc. ( www.ultraprotect.com )
012. ASprotect 2.1 reg ( www.aspack.com/asprotect.htm )  only exe files DLL files detect as ASpack :)
013. AHTeam EP Protector ver.0.3 priv
014. WinUpack 0.39 final by Dwing  ( http://dwing.51.net )  :-((
015. Software Compress ver. 1.2 Lite - www.bgsopt.com
016. PEcompact ver.2.78a - 3.0.3.9  - www.bitsum.com
017. nsPack ver.2.3 unreg - by North Star  -  www.nsdsn.com
018. nsPack ver.3.0 - 4.1 reg - by North Star  -  www.nsdsn.com
019. Mole Box 2.5.7  by Teggo. - www.molebox.com

020. Microsoft Visual C++ ver. 8
021. EXE Guarder 1.8 - 2.1 (2006/2008 unreg)  www.exeicon.com/exeguarder
022. EXE Wrapper ver. 2.3-2.5 ( www.533soft.com/exewrapper ) - how to remove password
023. Exe password protector 1.0.5.100  (protect/unprotect)
024. TASM / MASM / FASM - assembler language 
025. MS Visual Basic 5.0-6.0   dll
026. MS Visual Basic 5.0-6.0   exe

027. Armadillo 4.4x ~ 4.62..5.0~7.0  32bit   -  www.siliconrealms.com   (60e8)
028. Enigma protector v1.1x   - www.enigma.izmuroma.ru © Sukhov Vladimir 2004-2006
029. SVK-Protector v1.32 demo  -  Pavol Cerven - www.anticracking.sk


. . . 


571. PPT to EXE Converter Vaysoft v5.36 ( 2009.12.24 Delphi stub ) - www.vaysoft.com ( packed or not packed stub )
572. EXEForger (SignsImitator) v1.0.40.10 by STRELiTZIA ( 15.04.2010 ) - www.at4re.com
573. VMProtect v.2.05  2003-2010 VMProtect Software - www.vmprotect.ru
574. KiXtart 2010 (version 4.61) scripting language - www.kixtart.org
575. BoxedAppPacker v2.2.0.45  ( 2004 - 2010 Softanics ) - www.boxedapp.com
576. Obsidium v1.4.3.7 ( exe/dll ) Obsidium Software - www.obsidium.de
577. Private exe Protector v.3.2.0 or newer ( Generic detector 2010.05.xx )  - www.setisoft.com
578. DeployMaster Instaler v.3.3.2 ( 01.07.2010 ) Jan Goyvaerts - www.deploymaster.com
579. Zylom Game wrapper ( MS Visual C++ 7.x ) www.zylom.com
580. Zylom (wrapper) Crypted Game.exe file - www.zylom.com
581. Aspack v2.24-2.25 ( 03/11.2010 ) -> Alexey Solodovnikov - www.aspack.com     *ACM  
582. [dUP] diablo2oo2''s Universal Patcher [ loader installer ] - Version: 2.20 - 2.21 beta2 ( 05.10.2010 ) - http://diablo2oo2.cjb.net *ACM
583. [dUP] diablo2oo2''s Universal Patcher [ simple loader ] - Version: 2.20 - 2.21 beta2 ( 05.10.2010 ) - http://diablo2oo2.cjb.net *ACM
584. [dUP] diablo2oo2''s Universal Patcher [ patch ] - Version: 2.20 - 2.21 beta2 ( 05.10.2010 ) - http://diablo2oo2.cjb.net *ACM
585. Xenocode Virtual Application Studio 2010 ( v.8.0.xx ) - 2003-2009 Code Systems Corporation - www.xenocode.com    *ACM
586. GENERIC CHECK : ? Gentee Programming Language © 2004-2006  www.gentee.com
587. ASPROTECT generic / modified / unknown version detector
588. Enigma Virtual Box v1.30 free - 21.11.2010 - www.enigmaprotector.com
589. *generic check - Free Pascal compiler (MinGW/FPC) - familly *unknown version
590. VProtect ver.1.9.0.0 - VirtualizeProtect ( 2010.12.23 ) www.vprotect.net    *ACM 
591. VProtect ver.1.x - Generic detector - VirtualizeProtect  www.vprotect.net
592. Generic check : VMProtect v.2.07 - X.X  2003-2010 VMProtect Software - www.vmprotect.ru
593. GCC-MINGW compiler ver.4.4.4 - Generic detect
594. GCC Cygwin-MSYS  compiler - http://gcc.gnu.org/wiki/WindowsBuilding
595. GCC MINGW-64w compiler for 32 and 64 bit Windows - http://mingw-w64.sourceforge.net
596. Red Gate Installer v.1.x.x - www.red-gate.com ( MS VC++ v8/9 )
597. .NET compiler + {SmartAssembly} Obfuscator v2.0-6.0  - www.red-gate.com
598. XenoCode Virtual Application Studio 200x - Spoon Studio 2011 - http://spoon.net/Studio



_______________________________________________________________________

                   www.exeinfo.xwp.pl
_______________________________________________________________________


		2011.02.28 ( c ) A.S.L.


