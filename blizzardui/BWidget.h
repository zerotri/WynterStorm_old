#ifndef BWIDGET_H
#define BWIDGET_H
#include <Crystal.h>
#include <BResourceManager.h>
#include <vector>

class BWidget
{
public:
	BWidget();
	~BWidget();
	virtual void load(BResourceManager& resourceManager) = 0;
	virtual void draw() = 0;

	//events
	virtual void onMouseEnter(int x, int y){};
	virtual void onMouseLeave(int x, int y){};
	virtual void onMouseMove(int x, int y){};
	virtual void onMousePress(int x, int y, int button){};
	virtual void onMouseRelease(int x, int y, int button){};

	//mutators
	virtual bool __mouseEvent(int x, int y, int button); //-1 for none.
	virtual bool __keyboardEvent(bool pressed, int keyboard_key, int keyboard_flag, int keyboard_char);
	//accessors
	virtual bool isPointInside(int x, int y);
	virtual BWidget* getFocusedWidget();
private:
protected:
	std::vector <BWidget*> m_widgets;
};
#endif