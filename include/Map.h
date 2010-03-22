#ifndef MAP_H
#define MAP_H
#include <MapNode.h>

class MMap
{
private:
	static const int _maxObjects = 256;
	void* _mapObjects[_maxObjects];
public:
};
#endif