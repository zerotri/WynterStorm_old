#ifndef SRSDLCORE_H
#define SRSDLCORE_H
#include <SRCore.h>
#include <SRLog.h>

class SRSDLCore : public SRCore
{
protected:
public:
	SRSDLCore();
	~SRSDLCore();
	virtual void Initialize();
	virtual void Shutdown();
	virtual void drawPixel(s32 x, s32 y, CSColor<u8> color);
private:
};
#endif