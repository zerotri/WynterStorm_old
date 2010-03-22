#ifndef _WIN64
#ifndef BCHROMIUM_H
#define BCHROMIUM_H
#include <BWidget.h>

class BChromium
{
public:
	BChromium();
	~BChromium();
	virtual void load(BResourceManager& resourceManager);
	virtual void draw();

	//events
	virtual void onMouseEnter(int x, int y);
	virtual void onMouseLeave(int x, int y);
	virtual void onMouseMove(int x, int y);
	virtual void onMousePress(int x, int y, int button);
	virtual void onMouseRelease(int x, int y, int button);
};
#endif
#endif