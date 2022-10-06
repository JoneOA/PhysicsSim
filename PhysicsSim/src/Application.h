#include "Renderer.h"

class Application {

private:
	bool running = false;

public:

	Application()
		: running(true)
	{}

	void OnUpdate();
	bool IsRunning();



};