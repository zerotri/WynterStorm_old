#include <Crystal.h>
#include <SRLog.h>
#include <SRSDLFont.h>
#include <math.h>
#include <cstring>
#include <stdexcept>


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <freetype/fterrors.h>
static FT_Library crystal_freetype;


static float sinvalue = 0;

#define FT_FLOOR(X)	((X & -64) / 64)
#define FT_CEIL(X)	(((X + 63) & -64) / 64)
struct ColorTableDefinition
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
ColorTableDefinition fontColorModifiers[] = 
{
	{0,0,0},//default
	{255,0,0},//red
	{0,255,0},//green
	{0,0,255},//blue
	{127,255,0} // chartreuse
};

template<> SRFont* CSObject<SRFont>::alloc()
{
	return new SRSDLFont();
}
SRSDLFont::SRSDLFont()
{
	if(FT_Init_FreeType( &crystal_freetype ))
			throw std::runtime_error("FT_Init_FreeType failed");

	for(int i = 0; i < 256; i++)
		m_charGlyphs[i] = allocate<SRImage>();
}
SRSDLFont::~SRSDLFont()
{
	for(int i = 0; i < 256; i++)
		delete m_charGlyphs[i];
}
void SRSDLFont::load(unsigned char* data)
{
}
void SRSDLFont::draw(int x, int y)
{
	m_charGlyphs['b']->draw(x,y);
}
void SRSDLFont::drawChar(unsigned char character, int x, int y)
{
	m_charGlyphs[character]->draw(x,y);
}
void SRSDLFont::drawString( std::string outputString, int x, int y)
{
	int start_x = x;
	int cur_x = x;
	int cur_y = y + (m_fontMetrics.yMax + m_fontMetrics.yMin);
	Metrics metric;
	size_t stringLength = outputString.size();
	bool drawOffset = false;
	ColorTableDefinition modColor = fontColorModifiers[0];
	sinvalue += 0.005f;
	for(unsigned int i = 0; i < stringLength ; i++)
	{
		unsigned char currentChar = outputString.c_str()[i];
		metric = m_charMetrics[currentChar];
		float xoffset = metric.horiBearingX;
		float yoffset = -metric.horiBearingY;
		int origin = cur_y;
		if(drawOffset)
		{
			yoffset += sinf(sinvalue)*2.0f;
		}
		switch(currentChar)
		{
			case '$':
				if(++i < stringLength)
				{
					currentChar = outputString.c_str()[i];
					switch(currentChar)
					{
						case '@':
							drawOffset = !drawOffset;
							break;
						case 'c'://change color
							if(++i < stringLength)
							{
								currentChar = outputString.c_str()[i];
								modColor = fontColorModifiers[std::min<unsigned char>(currentChar - 'A',25)];
							}
							break;
						case '$'://output '$' char
							m_charGlyphs[currentChar]->setDrawingColor(modColor.red,modColor.green,modColor.blue);
							m_charGlyphs[currentChar]->draw(cur_x+(int)xoffset,cur_y + (int)yoffset);
							m_charGlyphs[currentChar]->setDrawingColor(0,0,0);
							cur_x += m_charGlyphs['$']->getRect().h*5;
							break;
					}
				}
				break;
			case '\n':
				cur_x = start_x;
				cur_y -= yoffset*2;//m_charGlyphs[0]->getRect().h;
				break;
			case ' ':
				cur_x += m_charMetrics['A'].advance_x;
				break;
			case '\t'://
				cur_x += m_charMetrics['A'].advance_x*5;
				break;
			case '\0':
				return;
				break;
			default:
				m_charGlyphs[currentChar]->setDrawingColor(modColor.red,modColor.green,modColor.blue);
				m_charGlyphs[currentChar]->draw(cur_x+(int)xoffset,cur_y+(int)yoffset);
				m_charGlyphs[currentChar]->setDrawingColor(0,0,0);
				cur_x += metric.advance_x;
				break;
		}
	}
}
void loadGlyph( FT_Bitmap*  bitmap, SRImage* image )
{
	unsigned char* img = new unsigned char[(bitmap->width*2)*bitmap->rows*4];
	int i, j, p, q;
	int x_max = bitmap->width;
	int y_max = bitmap->rows;
	int	off = 0;

	for ( j = 0, q = 0; j < y_max; j++, q++ )
	{
		for ( i = 0, p = 0; i < x_max; i++, p++ )
		{
			off = (j*bitmap->width*4)  + i*4;
			if(bitmap->buffer[q * bitmap->width + p] != 0)
			{
				img[off] = 255;
				img[off + 1] = 255;
				img[off + 2] = 255;
				img[off + 3] = bitmap->buffer[q * bitmap->width + p];
			}
			else
			{
				img[off] = 0;
				img[off + 1] = 0;
				img[off + 2] = 0;
				img[off + 3] = 0;
			}
		}
	}
	image->load(img, bitmap->width, bitmap->rows, 32);
	delete img;
}
void SRSDLFont::load(const char* fileName)
{
	FT_Face face;
	
	int error = FT_New_Face( crystal_freetype, fileName, 0, &face ); // create face object
	if(error)
	{
		//Log << "An Error Occurred" << WSLog::Flush;
		return;
	}
	// error handling omitted

	error = FT_Set_Char_Size( face, 16 * 64, 0, 100, 0 ); // set character size
	
	int n;
	FT_BBox boundingBox;
	FT_Glyph glyph;
	for( n = 0; n < 256; n++)
	{
		uint32_t glyph_ind = FT_Get_Char_Index(face, n);
		if(FT_Load_Glyph( face, glyph_ind, FT_LOAD_RENDER ) == 0) //FT_LOAD_RENDER | 
		{
			FT_Get_Glyph( face->glyph, &glyph ); 
			FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_UNSCALED, &boundingBox);
			loadGlyph(&face->glyph->bitmap, m_charGlyphs[n]);
			m_charMetrics[n].height = face->glyph->metrics.height >> 6;
			m_charMetrics[n].horiAdvance = face->glyph->metrics.horiAdvance >> 6;
			m_charMetrics[n].horiBearingX = face->glyph->metrics.horiBearingX >> 6;
			m_charMetrics[n].horiBearingY = face->glyph->metrics.horiBearingY >> 6;
			m_charMetrics[n].vertAdvance = face->glyph->metrics.vertAdvance >> 6;
			m_charMetrics[n].vertBearingX = face->glyph->metrics.vertBearingX >> 6;
			m_charMetrics[n].vertBearingY = face->glyph->metrics.vertBearingY >> 6;
			m_charMetrics[n].width = face->glyph->metrics.width >> 6;
			m_charMetrics[n].xMin = FT_FLOOR(boundingBox.xMin);
			m_charMetrics[n].yMin = FT_FLOOR(boundingBox.yMin);
			m_charMetrics[n].xMax = FT_CEIL(boundingBox.xMax);
			m_charMetrics[n].yMax = FT_CEIL(boundingBox.yMax);
			m_charMetrics[n].xoff = face->glyph->bitmap_left >> 6;
			m_charMetrics[n].yoff = face->glyph->bitmap_top >> 6;
			m_charMetrics[n].advance_x = face->glyph->advance.x >> 6;
			FT_Done_Glyph( glyph );
		}
	}
	char nc = 'q';
	Log << "Character '" << nc << "' Font Metrics:" << SRLog::Flush;
	Log << "Height: " << m_charMetrics[nc].height << SRLog::Flush;
	Log << "horiAdvance: " << m_charMetrics[nc].horiAdvance << SRLog::Flush;
	Log << "horiBearingX: " << m_charMetrics[nc].horiBearingX << SRLog::Flush;
	Log << "horiBearingY: " << m_charMetrics[nc].horiBearingY << SRLog::Flush;
	Log << "vertAdvance: " << m_charMetrics[nc].vertAdvance << SRLog::Flush;
	Log << "vertBearingX: " << m_charMetrics[nc].vertBearingX << SRLog::Flush;
	Log << "vertBearingY: " << m_charMetrics[nc].vertBearingY << SRLog::Flush;
	
	Log << "xMin: " << m_charMetrics[nc].xMin << SRLog::Flush;
	Log << "yMin: " << m_charMetrics[nc].xMin << SRLog::Flush;
	Log << "xMax: " << m_charMetrics[nc].xMax << SRLog::Flush;
	Log << "yMax: " << m_charMetrics[nc].yMax << SRLog::Flush;
	Log << "width: " << m_charGlyphs[nc]->getRect().w << SRLog::Flush;
	Log << "height: " << m_charGlyphs[nc]->getRect().h << SRLog::Flush;
	Log << "xoff: " << m_charMetrics[nc].xoff << SRLog::Flush;
	Log << "yoff: " << m_charMetrics[nc].yoff << SRLog::Flush;


	m_fontMetrics.xMin = m_fontMetrics.yMin =  32000;
	m_fontMetrics.xMax = m_fontMetrics.yMax = -32000;
	for ( n = 0; n < face->num_glyphs; n++ )
	{
		if(FT_Load_Glyph( face, n, FT_LOAD_RENDER ) == 0) //FT_LOAD_RENDER | 
		{
			FT_Get_Glyph( face->glyph, &glyph ); 
			FT_Glyph_Get_CBox(glyph, ft_glyph_bbox_pixels, &boundingBox);
			if(m_fontMetrics.xMin > (boundingBox.xMin ))
			{
				m_fontMetrics.xMin = (boundingBox.xMin );
			}
			if(m_fontMetrics.yMin > (boundingBox.yMin ))
			{
				m_fontMetrics.yMin = (boundingBox.yMin );
			}
			if(m_fontMetrics.xMax < (boundingBox.xMax ))
			{
				m_fontMetrics.xMax = (boundingBox.xMax );
			}
			if(m_fontMetrics.yMax < (boundingBox.yMax ))
			{
				m_fontMetrics.yMax = (boundingBox.yMax );
			}
			FT_Done_Glyph( glyph );
		}
	}
	Log << "xMin: " << m_fontMetrics.xMin << SRLog::Flush;
	Log << "yMin: " << m_fontMetrics.xMin << SRLog::Flush;
	Log << "xMax: " << m_fontMetrics.xMax << SRLog::Flush;
	Log << "yMax: " << m_fontMetrics.yMax << SRLog::Flush;

  FT_Done_Face    ( face );
  FT_Done_FreeType( crystal_freetype );
}