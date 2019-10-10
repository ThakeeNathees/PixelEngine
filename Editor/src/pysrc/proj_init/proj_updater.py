import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom
import os

obj_format = ".obj.xml"
scene_format = ".scn.xml"
proj_format = ".peproj"


def updateProj(proj_name = "", working_dir='.'):
    proj_file_name= proj_name + proj_format
    working_dir = working_dir+'/' if working_dir[-1] !='/' else working_dir ## need below
    proj_file_path = os.path.join(working_dir , proj_file_name)

    ## search for proj file
    if (proj_name==""):
        for file in os.listdir(working_dir):
            if file.endswith(proj_format):
                proj_file_path = os.path.join(working_dir, file)
                break;
        else:
            proj_name = os.path.basename(os.path.abspath('.'))
            proj_file_path = os.path.join(working_dir, proj_name) +proj_format

    if not os.path.isfile(proj_file_path):
        proj_file = open(proj_file_path, 'w')
        proj_file.write('<Project title="%s"><window_size x="640" y="480"/><pref frame_rate="30" begin_scene_id="70000" debug_mode="true" no_console="false"/><logo_texture id="-1"/><bg_color r="80" g="80" b="80" a="255"/><assets>assets.xml</assets><objects next_id="60000"></objects><pypaths/><scenes next_id="70000"></scenes></Project>'%proj_name)
        proj_file.close()
    doc = ET.parse( proj_file_path )
    root = doc.getroot()

    objects = root.find('objects')
    obj_to_delete = {}
    for tag in objects:
        obj_to_delete[tag] = True
        
    pypaths = root.find('pypaths')
    pypath_to_delete = {}
    for pypath in pypaths:
        pypath_to_delete[pypath] = True
    
    scenes = root.find('scenes')
    scn_to_delete = {}
    for tag in scenes:
        scn_to_delete[tag] = True

    for path, folders, files in os.walk(working_dir):
        for file in files:
            asset_path = os.path.join(path, file)
            asset_rel_path = asset_path[len(working_dir):]
            if isPathObject(asset_rel_path):
                if not objectHasPaht(objects, asset_rel_path, obj_to_delete):
                    new_obj = ET.Element('path')
                    new_obj.text = asset_rel_path
                    objects.insert(len(objects), new_obj)
                    
                obj_doc = ET.parse(asset_path)
                obj_doc_root = obj_doc.getroot()
                
                ## next_id
                obj_id = int(obj_doc_root.attrib["id"])
                next_id = int(objects.attrib["next_id"])
                objects.set('next_id', str(max(obj_id+1, next_id+1)))
                
                cls = obj_doc_root.find('class')
                if cls.attrib["name"] != "" and cls.attrib["type"] == "PYTHON_OBJECT" and not pypathHasPaht(pypaths, cls.text, pypath_to_delete):
                    new_pypath = ET.Element('pypath')
                    new_pypath.text = cls.text
                    pypaths.insert(len(pypaths), new_pypath)

            if isPathScene(asset_rel_path):
                if not sceneHasPaht(scenes, asset_rel_path, scn_to_delete):
                    new_scn = ET.Element('path')
                    new_scn.text = asset_rel_path
                    scenes.insert(len(scenes), new_scn)
                    
                scn_doc = ET.parse(asset_path)
                scn_doc_root = scn_doc.getroot()
                ## next_id
                scn_id = int(scn_doc_root.attrib["id"])
                next_id = int(objects.attrib["next_id"])
                scenes.set('next_id', str(max(scn_id+1, next_id+1)))
                

    for obj, is_delete in obj_to_delete.items():
        if is_delete:
            objects.remove(obj)

    for pypath, is_delete in pypath_to_delete.items():
        if is_delete:
            pypaths.remove(pypath)
            
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

def pypathHasPaht(pypaths, path, pypath_to_delete):
    for pypath in pypaths:
        if pypath.text == path:
            pypath_to_delete[pypath] = False
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
