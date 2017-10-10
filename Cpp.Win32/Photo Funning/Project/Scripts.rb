module PFDLL
  Invert = Win32API.new('PhotoFunning', 'Invert', 'l', 'i')
  BlackWhite = Win32API.new('PhotoFunning', 'BlackWhite', 'l', 'i')
  BlackWhite_Invert = Win32API.new('PhotoFunning', 'BlackWhite_Invert', 'l', 'i')
  GaussianBlur = Win32API.new('PhotoFunning', 'GaussianBlur', 'li', 'i')
  ColorDodge = Win32API.new('PhotoFunning', 'ColorDodge', 'll', 'i')
  Multiply = Win32API.new('PhotoFunning', 'Multiply', 'll', 'i')
  ChromaKeyFilter = Win32API.new('PhotoFunning', 'KeyFilter', 'll', 'i') #bitmap_pixel_alpha = (mask_pixel_green >= 127.5 ? bitmap_pixel_alpha : 0);
  KeyFilter = Win32API.new('PhotoFunning', 'KeyFilter', 'll', 'i') #bitmap_pixel_alpha = (bitmap_pixel_alpha - (255 - mask_pixel_red));
  Remover = Win32API.new('PhotoFunning', 'KeyFilter', 'll', 'i') #bitmap_pixel_alpha = (mask_pixel_alpha > 0 ? bitmap_pixel_alpha : 0);
  #Rotate180 = Win32API.new('PhotoFunning', 'Rotate180', 'l', 'i')
end

class ProgramMain_C
  def intialize
	@shutdown = false
  end
  def start
	create
	Graphics.transition
	#test
	loop do
	  mouse_update
	  Input.update
	  update
	  Graphics.update
	  break if @shutdown
	end
	Graphics.freeze
	dispose
  end
  def create
	Graphics.update
	@wid = Win32API.new('User32', 'GetActiveWindow', '', 'l').call
	@setWindowText = Win32API.new('User32', 'SetWindowText', 'lp', 'i')
	@ogl = @gaussian_level = 0.5
	@sprite = Sprite.new
	@sprite_top = Sprite.new
	@sprite_top.z += 1
	@sprite_top.bitmap = Bitmap.new(640, 480)
	@shots = Dir.entries('./Shots/')
	@backs = Dir.entries('./Backs/')
	@shots.delete('.')
	@shots.delete('..')
	@backs.delete('.')
	@backs.delete('..')
	@omi = @mi = 0
	@obi = @bi = 0
	@mm = (@shots.size - 1)
	@bm = (@backs.size - 1)
	@info = 0
	dmf(@shots[0], @backs[0])
  end
  
  def dmf(mfile, bfile)
	@bitmap = Bitmap.new(640,480)
	temp = Bitmap.new(640,480)
	photo = Bitmap.new('./Shots/' + mfile)
	background = Bitmap.new('./Backs/' + bfile)
	dest_rect = Rect.new(0, 0, 640, 480)
	@bitmap.stretch_blt(dest_rect, photo, photo.rect)
	temp.stretch_blt(dest_rect, photo, photo.rect)
	photo.dispose
	#PFDLL::DrawMyPhoto.call(@bitmap.__id__, temp.__id__, background.__id__)
	PFDLL::BlackWhite.call(@bitmap.__id__)
        PFDLL::BlackWhite_Invert.call(temp.__id__)
        PRFilter::MBlur.aply!(temp, PRFilter.gaussian_matrix(3, @gaussian_level+1)) #PFDLL::GaussianBlur(temp.__id__, 3);
        PFDLL::ColorDodge.call(@bitmap.__id__, temp.__id__)
        PFDLL::Multiply.call(@bitmap.__id__, background.__id__)
	temp.dispose
	background.dispose
	@sprite.bitmap = @bitmap
  end
  
  def test
	print "Invert"
	@sprite = Sprite.new
	@bitmap = Bitmap.new('Shots/Test')
	PFDLL::Invert.call(@bitmap.__id__)
	@sprite.bitmap = @bitmap
	for i in 0..79
	  Graphics.update
	end
	@sprite.bitmap.dispose
	
	print "BW"
	@bitmap = Bitmap.new('Shots/Test')
	PFDLL::BlackWhite.call(@bitmap.__id__)
	@sprite.bitmap = @bitmap
	for i in 0..79
	  Graphics.update
	end
	@sprite.bitmap.dispose
	
	print "BWInvert"
	@bitmap = Bitmap.new('Shots/Test')
	PFDLL::BlackWhite_Invert.call(@bitmap.__id__)
	@sprite.bitmap = @bitmap
	for i in 0..79
	  Graphics.update
	end
	@sprite.bitmap.dispose
        
	print "GB"
	@bitmap = Bitmap.new('Shots/Test')
	#PFDLL::GaussianBlur.call(@bitmap.__id__, 3)
	matriz = PRFilter.gaussian_matrix(3, 8)
        PRFilter::MBlur.aply!(@bitmap, matriz)
	@sprite.bitmap = @bitmap
  	for i in 0..79
	  Graphics.update
	end
	@sprite.bitmap.dispose

	print "CD"
	@bitmap = Bitmap.new('Shots/Test')
	temp = Bitmap.new('Graphics/Titles/001-Title01')
	PFDLL::ColorDodge.call(@bitmap.__id__, temp.__id__)
	temp.dispose
	@sprite.bitmap = @bitmap
	for i in 0..79
	  Graphics.update
	end
	@sprite.bitmap.dispose

	print "Multiply"
	@bitmap = Bitmap.new('Shots/Test')
	background = Bitmap.new('Backs/Paper2')
	PFDLL::Multiply.call(@bitmap.__id__, background.__id__)
	background.dispose
	@sprite.bitmap = @bitmap
	for i in 0..79
	  Graphics.update
	end
	@sprite.bitmap.dispose
  end
  def dispose
	@bitmap.dispose
	@sprite.dispose
	@sprite_top.bitmap.dispose
	@sprite_top.dispose
  end
  def mouse_update
	
  end
  def update
	@gaussian_level += 10  if Input.trigger?(Input::Z)
	@gaussian_level -= 10  if Input.trigger?(Input::Y)
	@gaussian_level += 1  if Input.trigger?(Input::UP)
	@gaussian_level -= 1  if Input.trigger?(Input::DOWN)
	@gaussian_level += 0.1  if Input.trigger?(Input::R)
	@gaussian_level -= 0.1  if Input.trigger?(Input::L)
	@mi += 1 if Input.trigger?(Input::C)
	@mi -= 1 if Input.trigger?(Input::B)
	@bi += 1 if Input.trigger?(Input::X)
	@mi = 0 if @mi > @mm
	@bi = 0 if @bi > @bm
	@mi = @mm if @mi < 0
	@gaussian_level= 0 if @gaussian_level < 0
	if @mi != @omi or @bi != @obi or @ogl != @gaussian_level
		@sprite_top.bitmap.clear
		@sprite_top.bitmap.font.color = system_color = Color.new(0, 0, 0, 255)
		@sprite_top.bitmap.draw_text(5, 449, 628, 32, "Processing...", 0)
		@sprite_top.bitmap.font.color = system_color = Color.new(255, 255, 255, 255)
		@sprite_top.bitmap.draw_text(6, 448, 628, 32, "Processing...", 0)
		@omi = @mi
		@obi = @bi
		@ogl = @gaussian_level
		Graphics.update
		dmf(@shots[@mi], @backs[@bi])
		@sprite_top.bitmap.clear
		@sprite_top.bitmap.font.color = system_color = Color.new(0, 0, 0, 255)
		@sprite_top.bitmap.draw_text(5, 449, 628, 32, "Photo Funning", 0)
		@sprite_top.bitmap.draw_text(5, 449, 628, 32, "Gaussian Level: #{@gaussian_level}", 2)
		@sprite_top.bitmap.font.color = system_color = Color.new(255, 255, 255, 255)
		@sprite_top.bitmap.draw_text(6, 448, 628, 32, "Photo Funning", 0)
		@sprite_top.bitmap.draw_text(6, 448, 628, 32, "Gaussian Level: #{@gaussian_level}", 2)

		@info = 80
	end
	if @info > 1
		@info -= 1
	elsif @info == 1
		@info -= 0
		@sprite_top.bitmap.clear
	end
  end
end