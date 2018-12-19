//show console for debugging
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "SystemClass.h"


int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	SystemClass* System;
	bool result;
	
	
	// Create the system object.
	System = new SystemClass;
	if(!System) {
		return 0;
	}

	// Initialize and run the system object.
	result = System->initialize();
	if(result) {
		System->run();
	}

	// Shutdown and release the system object.
	System->shutdown();
	delete System;
	System = 0;

	return 0;
}