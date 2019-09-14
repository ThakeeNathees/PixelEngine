
import pixel_engine as pe


def init(self):
        return

def process(self, dt):
        spd = 4
        p = self.getScene().getObject("player1")
        if pe.isKeyPressed(pe.Keyboard.J):
                self.getSprite().setFrameIndex(23)
                self.move(-spd,0)
                intersect = (p.getArea().isIntersecting(self.getArea()))
                if (intersect): self.move(spd,0)
        if pe.isKeyPressed(pe.Keyboard.Key.L):
                self.getSprite().setFrameIndex(33)
                self.move(spd,0)
                intersect = (p.getArea().isIntersecting(self.getArea()))
                if (intersect): self.move(-spd,0)
        if pe.isKeyPressed(pe.Keyboard.I):
                self.getSprite().setFrameIndex(23)
                self.move(0,-spd)
                intersect = (p.getArea().isIntersecting(self.getArea()))
                if (intersect): self.move(0,spd)
        if pe.isKeyPressed(pe.Keyboard.K):
                self.getSprite().setFrameIndex(23)
                self.move(0,spd)
                intersect = (p.getArea().isIntersecting(self.getArea()))
                if (intersect): self.move(0,-spd)
        #print(intersect)
        pass

def handleEvent(self, event):
        pass

x = 0
def drawCall(self):
        global x
        x+=.1
        t = pe.Text()
        t.rotate(x)
        t.setCharacterSize(40)
        f = pe.Assets.getFont(10001)
        t.setPosition(100,100)

        t.setFont(f)
        t.setString("testing")
        self.draw(t)
        self.drawSelf()
        return 
        for i in range(8):
                for j in range(8):
                        color = pe.Color(255,255,255)
                        if (i==4 and j==0): color = pe.Color(100,0,0)
                        if (i==1 and j==4): color = pe.Color(0,0,100)
                        if (i == 5) : color = pe.Color(0,100,0)
                        if (j==3) : color = pe.Color(151, 101, 160)
                        self.drawRectangle(50*i+10,50*j+10,50-10,50-10, color, False, 3)

'''
def init(self):
        t = pe.Assets.newTexture("tex")
        t.loadFromFile("res/sheet.png")
        s = pe.Assets.newSprite("my_spr")
        s.setTexture(t)
        print(s.getTexture().getName())
        s.setFrames(12,8)
        self.setSprite(s)

def process(self):
        s = self.getSprite()
        print(s.getTexture().getId())
        pass
        #self.setSprite(s)
        
        
'''        

'''
def inp(event):
        if (event.getType() == pe.EventType.KeyPressed):
                print(event.getKey())                
        pass

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
