import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom

## usage:
##      auto s = mod.attr("newScene")("scn_name", 70000)
##      mod.attr("addObject")(s, 60000)
##      mod.attr("writeScene")(s, "./res/scenes/")


scene_format = '''<scene name="%s" id="%s"><objects></objects></scene>'''
## name, id
## <object id="%s"/>

file_extension = ".scn.xml"

def writeScene(scn, path):
    plain_xml = ET.tostring(scn).decode('utf-8').replace('\n', '').replace('\t','')
    pretty_xml = mdom.parseString( plain_xml ).toprettyxml()
    name = obj.attrib['name']
    file = open(path+'/'+name+file_extension, 'w')
    file.write(pretty_xml)
    file.close()

def addObject(scene_tag, obj_id):
    obj_tag = ET.Element("object")
    obj_tag.set("id", str(obj_id))
    objs_tag = scene_tag.find("objects")
    print(objs_tag)
    objs_tag.insert(len(objs_tag), obj_tag)
    return scene_tag

def newScene(name, scn_id):
    scene_text = scene_format%(name, scn_id)
    scene_tag = ET.fromstring(scene_text)
    return scene_tag

    



