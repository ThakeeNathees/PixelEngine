import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom

## usage:
##      auto o = mod.attr("newObject")(...)
##      auto s = mod.attr("newSprite")(...)
##      auto a = mod.attr("newArea"  )(...)
##      o.attr("insert")(3, s)
##      o.attr("insert")(4, a)
##      mod.attr("writeObj")(o, "./res/objects/")


object_format = '''<object name="%s" id="%s"><class name="%s" type="%s">%s</class><properties z_index="%s" visible="%s" persistence="%s"/><transform><position x="0" y="0"/><rotation angle="0"/><scale x="1" y="1"/><origin x="0" y="0"/></transform><animations></animations></object>'''
## name, id, class_name, obj_type path,
## z_index, visible, persistence

sprite_format = '''<sprite name="%s" id="%s"><texture id="%s"/><texture_rect left="%s" top="%s" width="%s" height="%s"/><frames x="%s" y="%s" offset_x="%s" offset_y="%s" index="%s"/></sprite>'''
## name, id, tex_id, texture_rect, 
## frames,

area_format = '''<area name="%s" id="%s"><shape point_count="%s"></shape></area>'''
## name, id, point_count, [x, y] -> <point index="0" x="0" y="0"/>

file_extension = ".obj.xml"

def writeObject(obj, file_path):
    plain_xml = ET.tostring(obj).decode('utf-8').replace('\n', '').replace('\t','')
    pretty_xml = mdom.parseString( plain_xml ).toprettyxml()
    name = obj.attrib['name']
    file = open(file_path, 'w')
    file.write(pretty_xml)
    file.close()

def newObject(name, obj_id, class_name="", obj_type=0, ## 1 -> PYTHON_OBJECT, else -> CPP_OBJECT
                src_path="", z_index=0, visible=True, persistence=False):
    if obj_type == 1: obj_type = "PYTHON_OBJECT"
    else : obj_type = "CPP_OBJECT"
    obj_text = object_format%(name, obj_id, class_name, obj_type, src_path,
                z_index, visible, "true" if persistence else "false" )
    
    return ET.fromstring(obj_text)


def newSprite(name, spr_id, tex_id=-1,
              left=0, top=0, width=0, height=0,
              x=1, y=1, offsetx=0, offsety=0, index=0):
    spr_text = sprite_format%(name, spr_id, tex_id,left, top, width, height,
              x, y, offsetx, offsety, index)
    if tex_id <0:
        lines = spr_text.splitlines()
        lines[1:4] = []
        spr_text = '\n'.join(lines)
    return ET.fromstring(spr_text)


def newArea(name, area_id, point_count=0, points=[]):
    assert( len(points) == point_count )
    area_text = area_format%(name, area_id, point_count)
    area_tag = ET.fromstring(area_text)
    
    for i in range(point_count):
        point = ET.Element("point")
        point.set("index", str(i))
        point.set("x", str(points[i][0]))
        point.set("y", str(points[i][1]))
        area_tag.insert(len(area_tag), point)
    return area_tag

    



