
## How editor works
The main function first initialize the python interpreter, the pixel engine editor window, ```CLI``` class (which is a command line utility for 
pixel engine editor) , Logger, and then the ```StartWindow``` (which is responsible for project creation and selection)

### CLI initialization
```CLI``` add the editor.exe path to python's ```sys.path``` and then calls ```readPeConfigFile()``` to read the configurations file, 
the method first opens a file called ```peconfig.init``` located at the directory of editor's executable, and add all resources and configurations 
to the application. After the ```CLI``` initialization the ```Startwindow``` loop runs until the user create or select a valid pixel engine project.

### Main Loop
1. sfml window's event polled and passed to all the window singleton instances to handle
2. If the embedded Pixel-Engine application window running ```EmbededApplication::getInstance()->getApplication()->__process(&dt)``` called and error handled.
3. finally render all the singleton windows and display in the following order
	1. render the dock space and the main menu bar
	2. file tree
	3. embedded python interpreter
	4. editor's cli console
	5. image viewer, font viewer, text editors and hex editor
	6. object creator, script creator
	7. property editors : Object, Sprite, Area, Scene  
	8. embedded pixel engine application

### Window Singletons
#### file tree
A file tree singleton instance have 3 python objects ```m_py_filetree```, ```m_object_reader```, ```m_scene_reader```, for rendering the tree. 
```m_py_filetree```  defined a python object ```FileTree``` which consists 2 lists, one for file paths and the other for list of ```FileTree``` 
for directories. (additionally it contains 2 more lists for  paths of ```*.obj.xml```  and ```*.scn.xml```.

when rendering it calls a method ```renderTreeRecursive(py::object& tree, bool next_item_open)```. Each paths of files and directories will 
hashed(md5) and generate id to create an ```ImGui ``` tree widget. If the current path is a directory then it calls the ```renderTreeTecursive``` 
for that directory, else it checks if the path is a pixel engine specific file (```*.obj.xml```, ```*.scn.xml```, ```assets.xml```) and if so it 
calls the proper method for that file to render (```renderAssetsTree(std::string path)```, ```renderObjectTree(std::string path)```, 
```renderSceneTree(std::string path)```) else it draw the icon and name of the file, and handles listens events ( if clicked it will opens the 
proper window instance to view the file (image, font, text editor, if binary hex viewer, property editor, ...) )

#### object creator and script creator
object creator is to serialize and create ```*.obj.xml``` from the given inputs of the creator window, and the script creator is also doing the 
same to create ```*.py``` or ```*.h```. these widows use browse windows (render it) for 
capture the browse path.

#### sprite property editor

#### Area property editor

#### object property editor

#### scene property editor

#### embedded pixel engine application

