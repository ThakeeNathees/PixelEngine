#include "pch.h"

#include "pybind11/embed.h"
namespace py = pybind11;

int main(int argc, char** argv)
{
	py::scoped_interpreter intrp;


	unsigned int desktop_width = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int desktop_height = sf::VideoMode::getDesktopMode().height - 300;

	sf::RenderWindow window(sf::VideoMode(desktop_width, desktop_height), "Pixel-Engine");// , sf::Style::None);


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

		ImGui::ShowTestWindow();


		window.clear( );
		ImGui::SFML::Render(window);
		window.display();

	}
	ImGui::SFML::Shutdown();
	return 0;
}