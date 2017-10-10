#! ruby -Ks
require 'dxruby'
require 'dxrubyex'

image_houdai = Image.new(10,10,[0,255,0])

ENEMY_OBJECTS = []
ENEMY_COLLISIONS = []

class Enemy
  attr_reader :delete, :x, :y, :width, :height
  @@image = Image.new(50,50).circleFill(25,25,24,[255,0,255])
  @@image_damage = Image.new(50,50).circleFill(25,25,24,[255,200,255])
  def initialize
    @x = rand(590)
    @y = -49
    @speed = rand(5)
    @collision = CollisionCircle.new(self, 25, 25, 24)
    @delete = false
    @width = 50
    @height = 50
    @hp = 100
  end

  def update
    @y += 1
    if @y >= 480
      @collision.delete
      @delete = true
    else
      @collision.set(@x,@y)
      ENEMY_COLLISIONS.push(@collision)
    end
  end

  def hit(o) end

  def damage(o)
    @hp -= 1
    if @hp == 0
      @delete = true
    else
      Window.draw(@x, @y, @@image_damage,2)
    end
  end

  def draw
    Window.draw(@x, @y, @@image)
  end
end

class Laser
  attr_reader :collision, :enemy, :x, :y
  @@image_laser = Image.new(1,1,[128,255,255,255])
  def initialize(x, y)
    @x = x
    @y = y
    @collision = [CollisionTriangle.new(self, 0,0,0,0,0,0),CollisionTriangle.new(self, 0,0,0,0,0,0)]
    @collision[0].set(@x,@y)
    @collision[1].set(@x,@y)
    @angle = 0
    @enemy = []
  end

  def shot(d)
    @enemy.push(d)
  end

  def get_near_enemy
    near_distance = 800
    near_enemy = nil
    @enemy.each do |e|
      distance = Math.sqrt((@x - (e.x + e.width/2))**2 + (@y - (e.y + e.height/2))**2)
      if distance < near_distance
        near_distance = distance
        near_enemy = e
      end
    end
    return near_enemy
  end

  def rotation(x1,y1,x2,y2,x3,y3,x4,y4,angle)
    sina = Math.sin(angle/180.0*Math::PI)
    cosa = Math.cos(angle/180.0*Math::PI)
    result_x1 = x1 * cosa + y1 * sina
    result_y1 = x1 * sina - y1 * cosa
    result_x2 = x2 * cosa + y2 * sina
    result_y2 = x2 * sina - y2 * cosa
    result_x3 = x3 * cosa + y3 * sina
    result_y3 = x3 * sina - y3 * cosa
    result_x4 = x4 * cosa + y4 * sina
    result_y4 = x4 * sina - y4 * cosa
    return [result_x1, result_y1, result_x2, result_y2, result_x3, result_y3, result_x4, result_y4]
  end

  def update
    if Input.mouseDown?(M_LBUTTON)
      mx,my = Input.mousePosX, Input.mousePosY
      @angle = Math.atan2(mx - @x, @y - my) / Math::PI * 180
      x1,y1,x2,y2,x3,y3,x4,y4 = rotation(-5,-800,5,-800,5,0,-5,0,@angle+180)
      @collision[0].setRange(x1,y1,x2,y2,x3,y3)
      @collision[1].setRange(x2,y2,x3,y3,x4,y4)
    end
  end

  def draw(length)
    Window.drawEx(@x, @y, @@image_laser, :centerx=>0.5,:centery=>1,:scalex=>10,:scaley=>length,:angle=>@angle,:blend=>:add,:z=>1)
  end
end

laser = [Laser.new(145, 474), Laser.new(505, 474)]
font = Font.new(32)

count = 0
Window.loop do
  count += 1
  if count % 50 == 0
    ENEMY_OBJECTS.push(Enemy.new)
  end

  if Input.mouseDown?(M_LBUTTON)
    laser[0].update
    laser[1].update
  end

  ENEMY_OBJECTS.each do |e| e.update end

  laser.each do |l|
    Collision.check(l.collision, ENEMY_COLLISIONS) if Input.mouseDown?(M_LBUTTON)
    enemy = l.get_near_enemy
    enemy.damage(l) if enemy
    if Input.mouseDown?(M_LBUTTON)
      if enemy
        length = Math::sqrt(((enemy.x + enemy.width/2) - (l.x+5))**2 + ((enemy.y + enemy.height/2) - (l.y+5))**2)
      else
        length = 800
      end
      l.draw(length)
    end
  end

  ENEMY_OBJECTS.each do |e| e.draw end
  ENEMY_COLLISIONS.clear
  ENEMY_OBJECTS.delete_if do |e| e.delete end

  laser[0].enemy.clear
  laser[1].enemy.clear
  Window.drawFont(0,0,Window.getLoad.to_i.to_s + " %", font, :z=>3)

  Window.draw(140,470,image_houdai)
  Window.draw(500,470,image_houdai)
end


