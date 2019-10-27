#include "pch.h"


#include "core/CLI.h"
#include "windows/StartWindow.h"

#include "core/Resources.h"
#include "core/EmbededApplication.h"

#include "core/MainMenuBar.h"
MainMenuBar* MainMenuBar::s_instance = nullptr;

#include "windows/PyInterpriter.h"
#include "core/Console.h"
/*
PYBIND11_EMBEDDED_MODULE(console, m) {
	py::class_<Console>(m, "Console")
		.def("addLog", [](Console& cons, const std::string& msg, int level = 0) {cons.addLog(msg, level); })
		;
}
*/

PYBIND11_EMBEDDED_MODULE(peio, m) {
	m
		.def("print", []() { CLI::getInstance()->getConsole()-> addLog( "" , 0); })
		.def("print", [](const py::object& msg) { CLI::getInstance()->getConsole()->addLog( py::str(msg).cast<std::string>(), 0); })
		.def("getMousePosition", []() {
				return EmbededApplication::getInstance()->getMousePosition();
			})
		.def("isWindowFocus", []() { return EmbededApplication::getInstance()->isWindowFocus(); })
		;
	
}


#include "node_graph/node_graph.h"
#include "ImGuizmo-master/ImSequencer.h"

#include "windows/file_tree/FileTree.h"

#include "windows/assets_create/ObjectCreator.h"
#include "windows/assets_create/ScriptsCreator.h"

#include "windows/projerty_editor/ObjPropEditor.h"
#include "windows/projerty_editor/SpritePropEditor.h"
#include "windows/projerty_editor/AreaPropEditor.h"



struct MySeq : public ImSequencer::SequenceInterface
{

	virtual int GetFrameMin() const override { return mFrameMin; }
	virtual int GetFrameMax() const override { return mFrameMax; }

	struct MySequenceItem
	{
		int mType;
		int mFrameStart, mFrameEnd;
		bool mExpanded;
	};
	std::vector<MySequenceItem> myItems;
	int mFrameStart;
	int mFrameEnd;
	int mType;

	int mFrameMin;
	int mFrameMax;

	virtual int GetItemCount() const { return (int)myItems.size(); }
	virtual void Get(int index, int** start, int** end, int* type, unsigned int* color)
	{
		MySequenceItem& item = myItems[index];
		if (color)
			*color = 0xFFAA8080; // same color for everyone, return color based on type
		if (start)
			*start = &item.mFrameStart;
		if (end)
			*end = &item.mFrameEnd;
		if (type)
			*type = item.mType;
		
	}
};

/* ****************** end of includes  *****************  */
static const char* SequencerItemTypeNames[] = { "Camera","Music", "ScreenEffect", "FadeIn", "Animation" };
int main(int argc, char** argv)
{

	// temp
	MySeq mySequence;
	mySequence.mFrameMin = -100;
	mySequence.mFrameMax = 1000;
	mySequence.myItems.push_back(MySeq::MySequenceItem{ 0, 10, 30, false });
	mySequence.myItems.push_back(MySeq::MySequenceItem{ 0, 40, 80, false });
	mySequence.myItems.push_back(MySeq::MySequenceItem{ 1, 20, 30, true });
	mySequence.myItems.push_back(MySeq::MySequenceItem{ 3, 12, 60, false });
	mySequence.myItems.push_back(MySeq::MySequenceItem{ 2, 61, 90, false });
	mySequence.myItems.push_back(MySeq::MySequenceItem{ 4, 90, 99, false });

	py::scoped_interpreter intrp;
	py::exec("import sys, os");
	py::exec("import pixel_engine as pe");
	py::exec("import peio");

	// create window
	unsigned int w = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int h = sf::VideoMode::getDesktopMode().height - 300;
	sf::RenderWindow window(sf::VideoMode(w, h), "Pixel-Engine");

	// initialize
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	CLI::getInstance()->init();
	Logger::init(CLI::getExecPath().append("/log.txt") );
	PE_LOG("Pixel-Engine initialized"); CLI::log("Engine Initialized", Console::LOGLEVEL_SUCCESS);
	window.setIcon( Resources::LOGO.getSize().x, Resources::LOGO.getSize().y, Resources::LOGO.copyToImage().getPixelsPtr());

	StartWindow::getInstance()->init();
	Resources::init(w, h);


	int error = 0;
	do {
		// start window render loop
		PE_LOG("start window loop started");
		StartWindow::getInstance()->dispStartWindow(window, error);
		PE_LOG("start window loop ended");

		FileTree::getInstance()->reload();

		// Load applicaton's assets
		error = CLI::getInstance()->readProjFile();
		if (error) { error = 2; continue; }
		error = Resources::readAssets();
		if (error) { error = 3; continue; }
	} while (error);


	/**********************     MAIN LOOP     **********************/
	sf::Clock clock;
	pe::Event event; 
	double dt =0;

	while (window.isOpen()) {

		/* ***************** Event Handle ********************** */
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			ImageViwer::getInstance()->handleEvent(event);
			FontViwer::getInstance()->handleEvent(event);

			if (event.type == sf::Event::Closed) window.close();
			// gain focus
			if (event.type == sf::Event::GainedFocus) { 
				FileTree::getInstance()->reload(); 
			}
			
			// event handle for applicaton
			if (EmbededApplication::getInstance()->isRunning()) {
				try {
					EmbededApplication::getInstance()->getApplication()->__handleEvent(&event);
				}
				catch (const std::exception& e){
					if (!EmbededApplication::getInstance()->hasError()) {
						CLI::getInstance()->getConsole()->addLog(e.what(),3);
						EmbededApplication::getInstance()->setError(true);
					}
				}
			}
		} // end of event handle

		/* ***********************	process and render ********************** */
		ImGui::SFML::Update(window, clock.restart());

		// process application
		if (EmbededApplication::getInstance()->isRunning()){
			try {
				EmbededApplication::getInstance()->getApplication()->__process(&dt);
			}
			catch (const std::exception& e){
				if (!EmbededApplication::getInstance()->hasError()) {
					EmbededApplication::getInstance()->setError(true);
					CLI::getInstance()->getConsole()->addLog(e.what(), 3);
				}
			}
		}

		/* ****************** Render Windows ******************** */
		show_dock_space();
		MainMenuBar::getInstance()->render();

		FileTree::getInstance()->render();
		PyInterpriter::getInstance()->render();
		CLI::getInstance()->getConsole()->render();
		ImageViwer::getInstance()->render();
		FontViwer::getInstance()->render();

		TextEditors::renderEditors();
		HexEditors::renderEditors();

		ObjectCreater::getInstance()->render();
		ScriptCreator::getInstance()->render();

		ObjPropEditor::getInstance()->render();
		SpritePropEditor::getInstance()->render();
		AreaPropEditor::getInstance()->render();
		
		EmbededApplication::getInstance()->render();

		ImGui::Begin("Sequencer");
		static int currentFrame = 0;
		static bool expanded = false;
		static int selectedEntry = -1;
		static int firstFrame = 0;
		ImGui::PushItemWidth(130);
		ImGui::InputInt("Frame ", &currentFrame);
		ImGui::PopItemWidth();
		ImSequencer::Sequencer(&mySequence, &currentFrame, &expanded, &selectedEntry, &firstFrame, ImSequencer::SEQUENCER_EDIT_STARTEND | ImSequencer::SEQUENCER_ADD | ImSequencer::SEQUENCER_DEL | ImSequencer::SEQUENCER_COPYPASTE | ImSequencer::SEQUENCER_CHANGE_FRAME);
		if (selectedEntry != -1)
		{
			const MySeq::MySequenceItem& item = mySequence.myItems[selectedEntry];
			ImGui::Text("I am a %s, please edit me", SequencerItemTypeNames[item.mType]);
			// switch (type) ....
		}
		ImGui::End();
		/* node editor
		static bool open = true; if (open)ShowExampleAppCustomNodeGraph(&open);
		*/

		ImGui::ShowTestWindow();

		ImGui::SFML::Render(window);
		window.display();

	}

	/***************************************************************/

	ImGui::SFML::Shutdown();
	return 0;
}
