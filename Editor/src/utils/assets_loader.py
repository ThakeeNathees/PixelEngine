import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom
import os

image_formats = [".jpg", ".jpeg", ".png"]
font_formats = [ ".ttf" ]

def loadAssets(working_dir='./', assets_file_name='assets.xml', default_tex_smooth=True, default_tex_repeat=False):
    working_dir = working_dir+'/' if working_dir[-1] !='/' else working_dir ## need below
    assets_file_path = os.path.join(working_dir , assets_file_name)
    if not os.path.isfile(assets_file_path):
        assets_file = open(assets_file_path, 'w')
        assets_file.write('<assets>\n\t<textures next_id="0">\n\t</textures>\n\t<fonts next_id="10000">\n\t</fonts>\n</assets>')
        assets_file.close()
    doc = ET.parse( assets_file_path)
    assets = doc.getroot()

    textures = assets.find('textures')
    tex_to_delete = {}
    for tag in textures:
        tex_to_delete[tag] = True
    
    fonts = assets.find('fonts')
    font_to_delete = {}
    for tag in fonts:
        font_to_delete[tag] = True



    for path, folders, files in os.walk(working_dir):
        for file in files:
            asset_path = os.path.join(path, file)[len(working_dir):]
            if isPathImage(asset_path):
                if not texturesHasPaht(textures, asset_path, tex_to_delete):
                    next_id = int(textures.attrib['next_id'])
                    new_texture = ET.Element('texture', {
                            'name':"tex_"+str(next_id), 
                            'id':str(next_id),
                            'smooth':'true' if default_tex_smooth else 'false',
                            'repeat':'true' if default_tex_repeat else 'false'
                            }
                        )
                    new_texture.text = asset_path
                    textures.insert(len(textures), new_texture)
                    textures.set('next_id', str(next_id + 1))
            if isPathFont(asset_path):
                if not fontsHasPaht(fonts, asset_path, font_to_delete):
                        next_id = int(fonts.attrib['next_id'])
                        new_font = ET.Element('font', {'name':"font_"+str(next_id), 'id':str(next_id)})
                        new_font.text = asset_path
                        fonts.insert(len(fonts), new_font)
                        fonts.set('next_id', str(next_id + 1))

    for texture, is_delete in tex_to_delete.items():
        if is_delete:
            textures.remove(texture)
            
    for font, is_delete in font_to_delete.items():
        if is_delete:
            fonts.remove(font)


    plain_xml = ET.tostring(assets).decode('utf-8').replace('\n', '').replace('\t','')
    pretty_xml = mdom.parseString( plain_xml ).toprettyxml()

    file = open(assets_file_path, 'w')
    file.write(pretty_xml)
    file.close()

########################################################################

def isPathImage(path):
    for fmt in image_formats:
        if path.endswith(fmt): return True
    return False

def isPathFont(path):
    for fmt in font_formats:
        if path.endswith(fmt) : return True
    return False

def texturesHasPaht(textures, path, tex_to_delete):
    for texture in textures:
        if texture.text == path:
            tex_to_delete[ texture ] = False
            return True
    return False

def fontsHasPaht(fonts, path, font_to_delete):
    for font in fonts:
        if font.text == path:
            font_to_delete[font] = False
            return True
    return False

########################################################################