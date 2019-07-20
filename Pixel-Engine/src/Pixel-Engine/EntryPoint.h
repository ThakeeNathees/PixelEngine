#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern PE::Application* PE::createApplication();

int main(int argc, char** argv)
{

	PE::Log::Init();
	
	PE_CORE_WARN("Initialized Log");
	int a = 2;
	PE_INFO("Initialized Log var={0}", a);

	auto app = PE::createApplication();
	app->run();
	delete app;

}

#endif