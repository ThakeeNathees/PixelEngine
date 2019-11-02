import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom
import os


class SceneTag:
    def __init__(self, path):
        self.path = path
        path = os.path.relpath(path)
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
            
    def createBg(self, bg_id, bg_name="", tex_id=-1):
        if bg_name == "": bg_name = "bg_" + str(bg_id)
        if not self.hasBgTag():
            ## TODO:
            pass

    
