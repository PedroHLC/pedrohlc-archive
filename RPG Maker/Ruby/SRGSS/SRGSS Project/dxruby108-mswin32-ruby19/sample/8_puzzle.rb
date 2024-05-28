#!ruby -Ks
# DXRuby �T���v�� �W�p�Y��
# ���N���b�N�Ńs�[�X���ړ��A�E�N���b�N�ŃV���b�t��
# �g�p�\�ȉ摜��jpg�Apng�Abmp�Ȃǒʏ�̃t�H�[�}�b�g�ł��B
require 'dxruby'

filename = Window.openFilename([["�����̧��(*.*)", "*.*"]], "�p�Y���p�̉摜��I��")
image = Image.loadToArray(filename, 3, 3)

# ���ݒ�
width = image[0].width
height = image[0].height
if width < 32 then
  Window.scale = 48.0 / width
end
Window.width   = image[0].width * 3
Window.height  = image[0].height * 3
Window.caption = "�W�p�Y��"

# �p�Y���̏��
piece = [0,1,2,3,4,5,6,7,8]

# �N���b�N���̏����B�󂢂Ă�ʒu�̂ƂȂ肾���������ւ���B
def click(x, y, piece)
  i = piece.index(8) # �󂢂Ă�s�[�X����
  if (((i % 3) - x).abs == 1 and (i / 3) == y) or (((i / 3) - y).abs == 1 and (i % 3) == x) then
    piece[x + y * 3], piece[i] = piece[i], piece[x + y * 3] # ����ւ� a,b = b,a��swap�ł���
  end
end

# ���C�����[�v
Window.loop do

  # �E�N���b�N�ŃV���b�t���i�����_����1000��قǃN���b�N���Ă�����Ă܂�^^;)
  if Input.mousePush?(M_RBUTTON) then
    1000.times do
      click(rand(3), rand(3), piece)
    end
  end

  # ���N���b�N����
  if Input.mousePush?(M_LBUTTON) then
    click((Input.mousePosX / Window.scale / image[0].width).to_i, (Input.mousePosY / Window.scale / image[0].height).to_i, piece)
  end

  # ��������ƕ`��
  for i in 0..8
    if piece[i] != 8 or piece == [0,1,2,3,4,5,6,7,8] then
      Window.draw(i % 3 * image[0].width , i / 3 * image[0].height, image[piece[i]])
    end
  end

  # �G�X�P�[�v�L�[�ŏI��
  break if Input.keyPush?(K_ESCAPE)
end
