#!ruby -Ks
# DXRubyExtensionサンプル
require "dxruby"
require "dxrubyex"

# 動くもの共通クラス
class CollisionObject
  def initialize
    @x = rand(639-@image.width)
    @y = rand(439-@image.height)
  end

  def draw
    Window.draw(@x, @y, @image)
  end

attr_accessor :collision, :x, :y
end

# しかく
class Box < CollisionObject
  def initialize(size)
    @collision = CollisionBox.new(nil, 0, 0, size - 1, size - 1)
    @image = Image.new(size, size, [255, 200, 0, 0])
    super()
    collision.set(@x, @y)
  end
end

# まる
class Circle < CollisionObject
  def initialize(size)
    @collision = CollisionCircle.new(nil, size, size, size)
    @image = Image.new(size*2+1, size*2+1).circleFill(size, size, size, [255, 0, 0, 200])
    super()
    collision.set(@x, @y)
  end
end

# さんかく
class Triangle < CollisionObject
  def initialize(size)
    @collision = CollisionTriangle.new(nil, size/2,0,0,size-1,size-1,size-1)
    @image = Image.new(size, size)
    for i in 0..(size-1)
      @image.line(size/2-i/2, i, size/2+i/2, i, [255,0,200,0])
    end
    super()
    collision.set(@x, @y)
  end
end

font = Font.new(24)
x = Input.mousePosX
y = Input.mousePosY

# いまマウスで掴んでるオブジェクト
item = nil

# オブジェクト配列
arr = [Circle.new(25), Circle.new(50),
       Triangle.new(60), Triangle.new(100),
       Box.new(40), Box.new(80)]

# メインループ
Window.loop do
  oldx, oldy = x, y
  x, y = Input.mousePosX, Input.mousePosY
  mousecollision = CollisionPoint.new(nil)
  mousecollision.set(x, y)

  # ボタン押したら判定
  if Input.mousePush?(M_LBUTTON) then
    arr.each_with_index do |obj, i|
      if Collision.check(mousecollision, obj.collision) then
        # オブジェクトをクリックできたら並べ替えとitem設定
        arr.delete_at(i)
        arr.unshift(obj)
        item = obj
        break
      end
    end
  end

  # ボタン押されていたらマウスの移動分だけオブジェクトを移動
  if Input.mouseDown?(M_LBUTTON) then
    if item != nil then
      item.x += x - oldx
      item.y += y - oldy
      item.collision.set(item.x, item.y)
    end
  else
    # 離されたらオブジェクトを解放
    item = nil
  end

  # オブジェクト同士の判定
  collisions = Array.new(arr.size) {|i| arr[i].collision}
  if Collision.check(collisions, collisions) then
    Window.drawFont(0, 0, "hit!", font)
  end

  # 描画
  arr.reverse.each do |obj|
    obj.draw
  end

  break if Input.keyPush?(K_ESCAPE)
end
