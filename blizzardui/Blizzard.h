#ifndef BLIZZARD_UI_H
#define BLIZZARD_UI_H
#include <BWidget.h>

class BlizzardUI
{
private:
	BlizzardUI();
	~BlizzardUI();
	void setRoot(BWidget* rootWidget);
	BWidget* getFocusedWidget();
	void Update();
	void Draw();
	bool __mouseEvent(int x, int y, int button); //-1 for none.
	bool __keyboardEvent(bool pressed, int keyboard_key, int keyboard_flag, int keyboard_char);
protected:
	BWidget* m_rootWidget;
	BWidget* m_focusedWidget;
public:
};
#endif