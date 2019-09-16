#include "pch.h"

#include "pybind11/embed.h"
namespace py = pybind11;

#include "cli/CLI.h"
#include "path_handler/PathHandler.h"



int main(int argc, char** argv)
{
	py::scoped_interpreter intrp;

	PathHandler::init();
	// move them to a file at exec_path
	py::exec("sys.path.append('C:/dev/Pixel-Engine/Editor/src/pyutils')");
	py::exec("sys.path.append('C:/dev/Pixel-Engine/Editor/src/cli/proj_init')");

	auto ret = CLI::parseArgs(argc, argv);
	if (ret == CLI::CliRet::Done) return 0;


	return 0;
	//py::exec("print('[py]', os.getcwd())");


	unsigned int w = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int h = sf::VideoMode::getDesktopMode().height - 300;

	sf::RenderWindow window(sf::VideoMode(w, h), "Pixel-Engine");// , sf::Style::None);
	sf::Texture tex; tex.loadFromFile("res/logo/logo.png");
	window.setIcon(tex.getSize().x, tex.getSize().y, tex.copyToImage().getPixelsPtr());


	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;



	sf::Event event; sf::Clock clock;
	while (window.isOpen()) {

		// event handle
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) window.close();
		}
		ImGui::SFML::Update(window, clock.restart());

		// render editor
		ImGui::ShowTestWindow();


		window.clear( );
		ImGui::SFML::Render(window);
		window.display();

	}
	ImGui::SFML::Shutdown();
	return 0;
}