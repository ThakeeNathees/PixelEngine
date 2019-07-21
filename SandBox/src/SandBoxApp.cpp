#include <Pixel-Engine.h>
#include <Math/math.h>

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

PE::Application* PE::createApplication()
{
	return new SandBox();
}