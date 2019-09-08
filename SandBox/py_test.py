
import pixel_engine as pe






spr = pe.Sprite()
tex = pe.Texture()
tex.loadFromFile("res/logo.png")

spr.setTexture(tex)
spr.setFrames(2,2,0,0)
spr.setFrameIndex(1)

spr.setPosition(100,100)
spr.setRotation(20)
spr.setScale(.5,.5)

area = pe.Area()
sh = pe.CircleShape(100, 20)
sh2 = pe.ConvexShape(3)
sh2.setPoint(0,pe.Vect(0,0))
sh2.setPoint(1,pe.Vect(100,10))
sh2.setPoint(2,pe.Vect(10,100))

area.setShape(sh2)
area.setPosition(100,100)
area.setScale(2,2)
area.setOrigin(10,10)
area.rotate(area.getId()%360)



#spr.setFrames(3,3,0,0)
#spr.setFrameIndex(1)

