#ifndef WSSCRIPTCORE_H
#define WSSCRIPTCORE_H
#include "AngelScript.h"

class WSScriptCore
{
public:
	WSScriptCore();
	~WSScriptCore();
	static void MessageCallback(const asSMessageInfo *msg, void *param);
protected:
private:
};

#endif