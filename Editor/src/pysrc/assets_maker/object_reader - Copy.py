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


class Sprite:
    def __init__(self):
        self.name        = None
        self.id          = None
        self.tex_id      = None
        self.tex_rect    = {}
        self.frames      = {}

class Area:
    def __init__(self):
        self.name  = None
        self.id    = None
        self.shape = {}

class Animation:
    def __init__(self):
        self.name               = None
        self.id                 = None
        self.time_len           = 0
        self.loop               = True
        self.reverse            = False
        self.sprite_frame_track = {}
        self.position_track     = {}
        self.rotation_track     = {}
        self.scale_track        = {}
    

class Object:
    def __init__(self, path):
        self.object_name 	= None
        self.id 		= None

        self.class_name 	= None
        self.class_type 	= None
        self.class_path 	= None

        self.z_index 		= 0
        self.visible 		= True
        self.persistence 	= False

        self.position 		= [0,0]
        self.rotation 		= 0
        self.scale 		= [1,1]
        self.origin 		= [0,0]

        self.sprite 		= None
        self.area               = None
        self.animations 	= []

        ####################################################################

        path = os.path.relpath(path)
        doc = ET.parse(path)
        root  = doc.getroot()

        self.object_name = root.attrib['name']
        self.id  = int(root.attrib['id'])
        
        class_tag = root.find('class')
        self.class_name = class_tag.attrib['name']
        self.class_type = class_tag.attrib['type']
        self.class_path = class_tag.text

        prop_tag = root.find('properties')
        self.z_index = int(prop_tag.attrib['z_index'])
        self.visible = True if prop_tag.attrib['visible'] == 'true' else False
        self.persistence = True if prop_tag.attrib['persistence'] == 'true' else False

        trans_tag = root.find('transform')
        pos_tag = trans_tag.find('position')
        self.position = [ float(pos_tag.attrib['x']), float(pos_tag.attrib['y']) ]
        self.rotation = float(trans_tag.find('rotation').attrib['angle'])
        scale_tag = trans_tag.find('scale')
        self.scale = [ float(scale_tag.attrib['x']), float(scale_tag.attrib['y']) ]
        origin_tag = trans_tag.find('origin')
        self.origin = [ float(origin_tag.attrib['x']), float(origin_tag.attrib['y']) ]

        sprite_tag = root.find('sprite')
        if sprite_tag is not None:
            self.sprite = Sprite()
            self.sprite.name = sprite_tag.attrib['name']
            self.sprite.id = int(sprite_tag.attrib['id'])
            self.sprite.tex_id = int(sprite_tag.find('texture').attrib['id'])
            tex_rect_tag = sprite_tag.find('texture_rect')
            self.sprite.tex_rect = {
                0 : int(tex_rect_tag.attrib['top']),
                1 : int(tex_rect_tag.attrib['left']),
                2 : int(tex_rect_tag.attrib['width']),
                3 : int(tex_rect_tag.attrib['height']),
            }
            frames_tag = sprite_tag.find('frames')
            self.sprite.frames = {
                0 : int(frames_tag.attrib['x']),
                1 : int(frames_tag.attrib['y']),
                2 : int(frames_tag.attrib['offset_x']),
                3 : int(frames_tag.attrib['offset_y']),
            }
        
        
        area_tag = root.find('area')
        if area_tag is not None:
            self.area = Area()
            self.area.name = area_tag.attrib['name']
            self.area.id = int( area_tag.attrib['id'] )
            for point in area_tag.find('shape'):
                self.area.shape[int(point.attrib['index'])] = [ point.attrib['x'], point.attrib['y'] ]
            
        
        for anim in root.find('animations'):
            animation = Animation()
            animation.name = anim.attrib['name']
            animation.id = int(anim.attrib['id'])
            prop_tag = anim.find('properties')
            animation.time_len = float(prop_tag.attrib['time_length'])
            animation.loop = True if prop_tag.attrib['loop'] == 'true' else False
            animation.reverse = True if prop_tag.attrib['reverse'] == 'true' else False

            spt_tag = anim.find('sprite_frame_track')
            if spt_tag is not None:
                for key in spt_tag : animation.sprite_frame_track[float(key.attrib['time'])] = int(key.attrib['frame'])

            pt_tag = anim.find('position_track')
            if pt_tag:
                for key in pt_tag : animation.position_track[float(key.attrib['time'])] = [float(key.attrib['x']), float(key.attrib['y'])]

            rt_tag = anim.find('rotation_track')
            if rt_tag is not None:
                for key in rt_tag: animation.rotation_track[float(key.attrib['time'])] = float(key.attrib['angle'])

            st_tag = anim.find('scale_track')
            if st_tag is not None:
                for key in st_tag: animation.scale_track[float(key.attrib['time'])] = [float(key.attrib['x']), float(key.attrib['y'])]
            
            self.animations.append(animation)





