#include "core.h"


namespace pe {

	class PIXEL_ENGINE_API Application
	{
	public:
		Application();
		~Application();

		void update();

		sf::RenderWindow* m_window;
	};
}
