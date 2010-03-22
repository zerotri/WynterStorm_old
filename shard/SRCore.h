#ifndef SRCORE_H
#define SRCORE_H
#include <SRLog.h>
#include <Crystal.h>

class SRCore;

class SRCore : public CSObject<SRCore>
{
protected:
public:
	static fp64 getTime();
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void drawPixel(s32 x, s32 y, CSColor<u8> ) = 0;
private:
};
#endif