#pragma once


#ifdef PE_PLATFORM_WINDOWS

extern pe::Application* pe::createApplication();

int main(int argc, char** argv)
{
	auto app = pe::createApplication();
	app->run();
	delete app;

}

#endif