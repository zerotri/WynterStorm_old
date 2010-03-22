#ifndef SRSDLWINDOW_H
#define SRSDLWINDOW_H
#include <SRWindow.h>
#include <SDL/SDL.h>

class SRSDLWindow : public SRWindow
{
protected:
	SDL_Window* m_pWindow;
public:

	SRSDLWindow();
	~SRSDLWindow();
	virtual void create(int width = 320, int height = 240);
	virtual void destroy();
	virtual void swap();
	virtual void setTitle(std::string title);
	virtual void setFocused();
};
#endif