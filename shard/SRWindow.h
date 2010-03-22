#ifndef SRWINDOW_H
#define SRWINDOW_H
#include <string>
#include <Crystal.h>
#include <SRLog.h>

class SRWindow : public CSObject<SRWindow>
{
protected:
	int m_iWidth;
	int m_iHeight;
public:

	virtual void create(int width = 320, int height = 240) = 0;
	virtual void destroy() = 0;
	virtual void swap() = 0;
	virtual void setTitle(std::string title) = 0;
	virtual void setFocused() = 0;
	
	// controllers
	// emitter
};
#endif