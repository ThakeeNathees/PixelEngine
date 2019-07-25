#include <Pixel-Engine.h>

class SandBox : public pe::Application
{
public:
	SandBox()
	{
	}
	~SandBox()
	{

	}
};

pe::Application* pe::createApplication()
{
	return new SandBox();
}