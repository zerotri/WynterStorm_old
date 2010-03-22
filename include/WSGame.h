#ifndef WSGAME_H
#define WSGAME_H
#include <Shard.h>
#include <SRSDLCore.h>
#include <SRCore.h>

class WSGame
{
public:
	enum MouseButtons
	{
		MB_Left = 1,
		MB_Middle = 2,
		MB_Right = 3
	};
protected:
	SRWindow* m_pWindow;
	SRCore* m_pCore;
	bool m_bGameEnding;
	double m_dDeltaFramesPerSecond;
	double m_dLastFrameTime;
public:
	WSGame();
	~WSGame();
	void Run();
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void Render() = 0;

	//events
	virtual void onKeyPress(int keyboard_key, int keyboard_flag, int keyboard_char) {};
	virtual void onKeyRelease(int keyboard_key, int keyboard_flag, int keyboard_char) {};
	virtual void onMouseMove(int mouse_x, int mouse_y) {};
	virtual void onMousePress(MouseButtons mouse_button, int mouse_x, int mouse_y) {};
	virtual void onMouseRelease(MouseButtons mouse_button, int mouse_x, int mouse_y) {};
	virtual void onMouseWheel(int mouse_x_degrees, int mouse_y_degrees) {};
	virtual void onMouseFocus(int mouse_x, int mouse_y) {};
	virtual void onAppClose() {};
	virtual void onAppMinimize() {};
	virtual void onUserEvent(int eventID, void *data1, void *data2) {};

	//
	fp64 getFramesPerSecond();
};

#endif