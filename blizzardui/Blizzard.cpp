#include <Blizzard.h>

BlizzardUI::BlizzardUI()
{
	m_rootWidget = 0;
	m_focusedWidget = 0;
}
BlizzardUI::~BlizzardUI()
{
}

void BlizzardUI::Update()
{
}
void BlizzardUI::Draw()
{
	m_rootWidget->draw();
}

void BlizzardUI::setRoot(BWidget* rootWidget)
{
}
BWidget* BlizzardUI::getFocusedWidget()
{
	return m_focusedWidget;
}

bool BlizzardUI::__mouseEvent(int x, int y, int button) //-1 for none.
{
	if(m_rootWidget->isPointInside(x, y))
	{

		return m_rootWidget->__mouseEvent(x, y, button);
	}
	else
	{
		if(button == -1)
		{
			m_focusedWidget = 0;
		}
		return false;
	}
}
bool BlizzardUI::__keyboardEvent(bool pressed, int keyboard_key, int keyboard_flag, int keyboard_char)
{
	if( m_focusedWidget != 0)
		return m_focusedWidget->__keyboardEvent(pressed, keyboard_key, keyboard_flag, keyboard_char);
	else
		return false;
}