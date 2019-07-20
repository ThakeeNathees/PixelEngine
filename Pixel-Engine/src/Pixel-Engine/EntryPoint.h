#pragma once

#ifdef PE_PLATFORM_WINDOWS


extern PE::Application* PE::createApplication();

int main(int argc, char** argv)
{

	PE::Log::Init();
	auto app = PE::createApplication();
	app->run();
	delete app;

}

#endif