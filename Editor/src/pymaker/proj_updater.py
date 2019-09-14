import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom
import os

obj_format = ".obj.xml"
scene_format = ".scn.xml"

def updateProj(proj_name = "SandBox", working_dir='.'):
    proj_file_name= proj_name + '.peproj.xml'
    working_dir = working_dir+'/' if working_dir[-1] !='/' else working_dir ## need below
    proj_file_path = os.path.join(working_dir , proj_file_name)
    if not os.path.isfile(proj_file_path):
        proj_file = open(proj_file_path, 'w')
        proj_file.write('<Project title="%s"><window_size x="640" y="480"/><pref frame_rate="30" begin_scene_id="70000" debug_mode="true" no_console="false"/><logo_texture id="-1"/><bg_color r="80" g="80" b="80" a="255"/><assets>assets.xml</assets><objects/><scenes/></Project>'%proj_name)
        proj_file.close()
    doc = ET.parse( proj_file_path )
    root = doc.getroot()

    objects = root.find('objects')
    obj_to_delete = {}
    for tag in objects:
        obj_to_delete[tag] = True
    
    scenes = root.find('scenes')
    scn_to_delete = {}
    for tag in scenes:
        scn_to_delete[tag] = True

    for path, folders, files in os.walk(working_dir):
        for file in files:
            asset_path = os.path.join(path, file)[len(working_dir):]
            if isPathObject(asset_path):
                if not objectHasPaht(objects, asset_path, obj_to_delete):
                    new_obj = ET.Element('path')
                    new_obj.text = asset_path
                    objects.insert(len(objects), new_obj)
            if isPathScene(asset_path):
                if not sceneHasPaht(scenes, asset_path, scn_to_delete):
                        new_scn = ET.Element('path')
                        new_scn.text = asset_path
                        scenes.insert(len(scenes), new_scn)

    for obj, is_delete in obj_to_delete.items():
        if is_delete:
            objects.remove(obj)
            
    for scn, is_delete in scn_to_delete.items():
        if is_delete:
            scenes.remove(scn)


    plain_xml = ET.tostring(root).decode('utf-8').replace('\n', '').replace('\t','')
    pretty_xml = mdom.parseString( plain_xml ).toprettyxml()

    file = open(proj_file_path, 'w')
    file.write(pretty_xml)
    file.close()

########################################################################

def isPathObject(path):
    if path.endswith(obj_format): return True
    return False

def isPathScene(path):
    if path.endswith(scene_format) : return True
    return False

def objectHasPaht(objects, path, obj_to_delete):
    for obj in objects:
        if obj.text == path:
            obj_to_delete[ obj ] = False
            return True
    return False

def sceneHasPaht(scenes, path, scn_to_delete):
    for scn in scenes:
        if scn.text == path:
            scn_to_delete[scn] = False
            return True
    return False

########################################################################

if __name__ == "__main__" and 0:
    updateProj()
