import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom
import os


class SceneTag:
    def __init__(self, path):
        self.path = path
        try:
            path = os.path.relpath(path)
        except Exception as err:
            print(err)
        doc = ET.parse(path)
        self.root = doc.getroot()

    def getPath(self):
        return self.path

    def reload(self):
        doc = ET.parse(self.path)
        self.root = doc.getroot()

    def save(self):
        plain_xml = ET.tostring(self.root).decode('utf-8').replace('\n', '').replace('\t','')
        pretty_xml = mdom.parseString( plain_xml ).toprettyxml()
        file = open(self.path, 'w')
        file.write(pretty_xml)
        file.close()

    def getName(self):
        return self.root.attrib['name']
    def setName(self, name):
        self.root.attrib['name'] = name

    def getId(self):
        return int(self.root.attrib['id'])
    def _setId(self, _id):
        self.root.attrib['id'] = _id

    ## bg
    def hasBgTag(self):
        return self.root.find('background') is not None
    def deleteBg(self):
        bg = self.root.find('background')
        if bg is not None:
            self.root.remove(bg)
    ## TODO: bg tag speed, scale, ...
            
    def createBg(self, bg_id, bg_name="", tex_id=-1):
        if bg_name == "": bg_name = "bg_" + str(bg_id)
        if not self.hasBgTag():
            new_bg = ET.Element('background')
            new_bg.attrib['name'] = bg_name
            new_bg.attrib['id'] = str(bg_id)
            self.root.insert(0, len(self.root), new_bg)

            prop = ET.Element('properties')
            new_bg.insert(0, prop)
            prop.attrib['visible'] = 'true'

            move_speed = ET.Element('move_speed')
            new_bg.insert(len(new_bg), move_speed)
            move_speed.attrib['x'] = '0'
            move_speed.attrib['y'] = '0'

            scale = ET.Element('scale')
            new_bg.insert(len(new_bg), scale)
            scale.attrib['x'] = '1'
            scale.attrib['y'] = '1'

            ## no textures when creating

    ## TODO: add object 
    def getObjectsCount(self):
        return len(self.root.find('objects'))
    def getObjectId(self, ind):
        if ind < 0 or len(self.root.find('objects')) <= ind:
            raise Exception("invalid index (getObjectId): ", __FILE__)
        return int(self.root.find('objects')[ind].attrib['id'])
