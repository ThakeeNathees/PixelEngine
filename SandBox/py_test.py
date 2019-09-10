
import pixel_engine as pe

#print(
#dir(pe.Key)
#)
#print(dir(pe))
#print(dir(pe.Event.EventType))
'''
print(dir(pe.Mouse))
#'''


def inp(event):
        if (event.getType() == pe.EventType.MouseWheelMoved):
                print(event.getWheel())
                print(event.getMousePosition())
        pass
	#print(event)

'''
k = pe.TrackKey(0,pe.TrackData(11212))
s = pe.SpriteFrameTrack()
s.addKey(k)

a = pe.Animation()
a.setTimeLength(10)
a.setSpriteFrameTrack(s)

spt = a.getSpriteFrameTrack()
print(spt.getKeys()[0].data.sprite_frame)


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
#area.rotate(area.getId()%360)


#print(area.getCount())

#spr.setFrames(3,3,0,0)
#spr.setFrameIndex(1)

#'''
