#include <Map.h>
#include <cstring>
#include <math.h>
const int tile_width = 40;
const int tile_height = 40;

MMapNode::MMapNode()
{
	tileset = allocate<SRImage>();
	for(int _x = 0; _x < _width; _x++)
	{
		for(int _y = 0; _y < _height; _y++)
		{
			mapTiles[_x][_y][0] = 3;
		}
	}
	tileset->load("ts_main.png");

	const CSRectangle<int>& tsrect = tileset->getRect();
	ts_tiles_x = (tsrect.w / tile_width);
	ts_tiles_y = (tsrect.h / tile_height);
}

void MMapNode::setTile(int num, int x, int y)
{
	mapTiles[x][y][0] = num;
}
void MMapNode::draw()
{
	//make sure tileset is loaded before we draw it
	if(tileset->isLoaded() != true)
		return;
	tileset->draw(32, 32);
	int tile = 0;
	int dest_x;
	int dest_y;
	CSRectangle<int> rectSrc, rectDst;
	rectSrc.w = tile_width;
	rectSrc.h = tile_height;
	rectDst.w = tile_width;
	rectDst.h = tile_height;
	for(int _x = 0; _x < _width; _x++)
	{
		dest_x = _x*tile_width;
		for(int _y = 0; _y < _height; _y++)
		{
			
			dest_y = _y*tile_height;
			tile = mapTiles[_x][_y][0];

			//calculate x position
			int x_diff = tile%ts_tiles_x;
			rectSrc.x = (x_diff) * tile_width;

			//calculate y position
			rectSrc.y = ((int)floor((float)tile/(float)ts_tiles_x) * tile_height);
			rectDst.x = _x*tile_width;
			rectDst.y = _y*tile_height;
			tileset->draw(rectSrc,rectDst);
		}
	}
}