import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom
import os

## obj editor
## ------------------------------------ 
## object name, id
## class name, type path
## z_index, visible, persistence
## 
## transform position, rotation, scale, origin
## 

## area -> area editor
## sprite -> sprite editor
## animation -> animation editor
## --------------------------------------
## sprite name, id, texture, texture_rect, frames
##
## area name, id, point_count+points
## 
## animations
##      animation name, id
##      time_length, loop, reverse
##      sprite_frame_track
##          key, value
##      positiontrack
##      rotation track
##      scale track

    

class ObjectTag:
    def __init__(self, path):
        self.path = path
        path = os.path.relpath(path)
        doc = ET.parse(path)
        self.root  = doc.getroot()

    def reload(self):
        doc = ET.parse(self.path)
        self.root  = doc.getroot()

    def save(self):
        plain_xml = ET.tostring(self.root).decode('utf-8').replace('\n', '').replace('\t','')
        pretty_xml = mdom.parseString( plain_xml ).toprettyxml()
        file = open(self.path, 'w')
        file.write(pretty_xml)
        file.close()

    def getName(self):
        return self.root.attrib['name']
    def setName(name):
        self.root.attrib['name'] = name
        
    def getId(self):
        return int(self.root.attrib['id'])
    def _setId(self,_id):
        self.root.attrib['id'] = str(_id)

    def getClassName(self):
        class_tag = self.root.find('class')
        return class_tag.attrib['name']
    def setClassName(self,class_name):
        class_tag = self.root.find('class')
        class_tag.attrib['name'] = class_name

    def getScriptPath(self):
        class_tag = self.root.find('class')
        return class_tag.text 
    def setScriptPath(self, path):
        class_tag = self.root.find('class')
        class_tag.text = path
    
    ## 0 -unknown, 1 = py, 2= cpp
    def getObjectType(self):
        class_tag = self.root.find('class')
        cls_type = class_tag.attrib['type']
        if cls_type == "PYTHON_OBJECT": return 1
        if cls_type == "CPP_OBJECT" : return 2
        return 0
    
    def setObjectType(self,obj_type):
        assert class_type in ['PYTHON_OBJECT', 'CPP_OBJECT']
        class_tag = self.root.find('class')
        class_tag.attrib['type'] = obj_type

    def getScriptPath(self):
        class_tag = self.root.find('class')
        return class_tag.text
    def setScriptPath(self,path):
        class_tag = self.root.find('class')
        class_tag.text = path

    def getZindex(self):
        prop_tag = self.root.find('properties')
        return int(prop_tag.attrib['z_index'])
    def setZindex(self,ind):
        prop_tag = self.root.find('properties')
        prop_tag.attrib['z_index'] = str(ind)
    
    def isVisible(self):
        prop_tag = self.root.find('properties')
        return True if prop_tag.attrib['visible'] == 'true' else False
    def setVisible(self,visible):
        prop_tag = self.root.find('properties')
        if visible: prop_tag.attrib['visible'] = 'true'
        else :prop_tag.attrib['visible'] = 'false'
        
    def isPersistence(self):
        prop_tag = self.root.find('properties')
        return True if prop_tag.attrib['persistence'] == 'true' else False
    def setPersistence(self,per):
        prop_tag = self.root.find('properties')
        if per:prop_tag.attrib['persistence'] = 'true'
        else: prop_tag.attrib['persistence'] = 'false'
    

    ## transform
    def getPosition(self):
        trans_tag = self.root.find('transform')
        pos_tag = trans_tag.find('position')
        return [ float(pos_tag.attrib['x']), float(pos_tag.attrib['y']) ]
    def setPosition(self,x, y):
        trans_tag = self.root.find('transform')
        pos_tag = trans_tag.find('position')
        pos_tag.attrib['x'] = str(x)
        pos_tag.attrib['y'] = str(y)
        
    def getRotation(self):
        trans_tag = self.root.find('transform')
        return float(trans_tag.find('rotation').attrib['angle'])
    def setRotation(rot):
        trans_tag = self.root.find('transform')
        trans_tag.find('rotation').attrib['angle'] = str(rot)
    
    def getScale(self):
        trans_tag = self.root.find('transform')
        scale_tag = trans_tag.find('scale')
        return [ float(scale_tag.attrib['x']), float(scale_tag.attrib['y']) ]
    def setScale(self,x, y):
        trans_tag = self.root.find('transform')
        scale_tag = trans_tag.find('scale')
        scale_tag.attrib['x'] = str(x)
        scale_tag.attrib['y'] = str(y)
    
    def getOrigin(self):
        trans_tag = self.root.find('transform')
        origin_tag = trans_tag.find('origin')
        return  [ float(origin_tag.attrib['x']), float(origin_tag.attrib['y']) ]
    def setOrigin(self,x, y):
        trans_tag = self.root.find('transform')
        origin_tag = trans_tag.find('origin')
        origin_tag.attrib['x'] = str(x)
        origin_tag.attrib['y'] = str(y)
        

    def hasSpriteTag(self):
        return self.root.find('sprite') is not None
    def getSpriteTag(self):
        return self.root.find('sprite')
    def getSpriteTextureId(self):
        return int(self.root.find('sprite').find('texture').attrib['id'])
    def getSpriteTextureRect(self):
        return [
            int(self.root.find('sprite').find('texture_rect').attrib['left']),
            int(self.root.find('sprite').find('texture_rect').attrib['top']),
            int(self.root.find('sprite').find('texture_rect').attrib['width']),
            int(self.root.find('sprite').find('texture_rect').attrib['height'])
            ]
    def getSpriteFrames(self):
        return [
            int(self.root.find('sprite').find('frames').attrib['x']),
            int(self.root.find('sprite').find('frames').attrib['y']),
            int(self.root.find('sprite').find('frames').attrib['offset_x']),
            int(self.root.find('sprite').find('frames').attrib['offset_y']),
            int(self.root.find('sprite').find('frames').attrib['index']),
            ]
    
    def hasAreaTag(self):
        return self.root.find('area') is not None
    def getAreaTag(self):
        return self.root.find('area')

    def hasAnyAnimations(self):
        return self.root.find('animations').find('animation') is not None

    def getAnimationsTag(self):
        return self.root.find('animations')




