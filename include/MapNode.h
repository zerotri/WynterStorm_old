#ifndef MAPNODE_H
#define MAPNODE_H
#include <SRImage.h>

class MMapNode
{
private:
	static const int _width = 16;
	static const int _height = 9;
	static const int _layers = 4;
	int ts_tiles_x;
	int ts_tiles_y;
	SRImage* tileset;
protected:
	int mapTiles[_width][_height][_layers];
public:
	MMapNode();
	void setTile(int num, int x, int y);
	void draw();
};
#endif