//----STANDARD----
#include "stdio.h"

//----LOCAL----
#include "main.h"
#include "core/application.h"

using namespace std;

int main(int argc, char* argv[])
{
	Starclock::Core::Application* application = new Starclock::Core::Application(argc, argv);
	application->run();

	delete application;

	return 0;
}
