#include <Pixel-Engine.h>


class SandBox : public PE::Application
{
public:
	SandBox()
	{

	}
	~SandBox()
	{

	}
};

PE::Application* PE::CreateApplication()
{
	return new SandBox();
}