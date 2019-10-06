
import pixel_engine as pe

i = 0
def process(self, dt):
        global i
        self.getSprite().setFrameIndex((i//10)%3)
        i+=1

def drawCall(self):
        self.drawSelf()
