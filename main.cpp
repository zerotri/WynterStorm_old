#include <SDL/SDL.h>
#include <WynterStorm.h>
#include <Shard.h>
#include <MapNode.h>
#include <math.h>

class MGame : public WSGame
{
	
	enum editorState
	{
		st_tilePlace,
		st_tilePick
	};

	SRImage* bar_left;
	SRImage* bar_middle;
	SRImage* bar_right;
	SRImage* image;
	SRFont* font;
	MMapNode* node;
	bool mousedown;
	int tilenum;
	int mouse_place_x, mouse_place_y;
	int ts_width;
	int ts_height;
	char fpsTick[32];
	editorState state;
	CSBezier* bez;
public:
	virtual void Initialize()
	{
		bar_left = allocate<SRImage>();
		bar_middle = allocate<SRImage>();
		bar_right = allocate<SRImage>();
		image = allocate<SRImage>();
		mousedown = false;
		tilenum = 0;
		mouse_place_x = 0;
		mouse_place_y = 0;
		state = st_tilePlace;
		bar_left->load("gui/blizzard_bar_left.png");
		bar_middle->load("gui/blizzard_bar_middle.png");
		bar_right->load("gui/blizzard_bar_right.png");
		font = allocate<SRFont>();
		font->load("DejaVuSans.ttf");
		image->load("ts_main.png");
		node = new MMapNode();
		ts_width = image->getRect().w;
		ts_height = image->getRect().h;
		Log << "Width: " << ts_width << SRLog::Flush;
		Log << "Height: " << ts_height << SRLog::Flush;
		bez = new CSBezier(CSPoint<double>(32.0, 32.0),
						   CSPoint<double>(256.0, 64.0),
						   CSPoint<double>(32.0, 128.0));
	}
	virtual void Shutdown()
	{
		delete node;
		delete bar_left;
		delete bar_middle;
		delete bar_right;
		delete image;
		delete font;
	}
	virtual void Render()
	{
		node->draw();
		SDL_Rect cursor_rect = {0,0,40,40};
		SDL_GetMouseState(&cursor_rect.x, &cursor_rect.y);
		cursor_rect.x = ((int)floor(cursor_rect.x/40.0f))*40;
		cursor_rect.y = ((int)floor(cursor_rect.y/40.0f))*40;
		
		//draws tile picker on that state
		/*if(state == st_tilePick)
		{
			int cursor_start_x = ((int)floor(mouse_place_x/40.0f))*40;
			int cursor_start_y = ((int)floor(mouse_place_y/40.0f))*40;
			SDL_Rect window_rect = {0,0,640,480};
			SDL_SetRenderDrawColor(0x0, 0x0, 0x0, 0x32);
			SDL_SetRenderDrawBlendMode(SDL_BLENDMODE_MASK);
			SDL_RenderFillRect(&window_rect);
			image.draw(cursor_start_x,cursor_start_y);
		}*/

		
		CSRectangle<s32> middle_rectA = {0,0,1,38};
		CSRectangle<s32> middle_rectB = {40,32,400,38};
		bar_left->draw(middle_rectB.x-8,32);
		bar_middle->draw(middle_rectA,middle_rectB);
		bar_right->draw(middle_rectB.x+middle_rectB.w,32);
		sprintf(fpsTick,"FPS: %f",getFramesPerSecond());
		font->drawString(T("Hello World!\n $@This$@ is a $cEmultiline $cAtext.\nabcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ"),42,40);
		font->drawString(T(fpsTick), 4, 0);
		//draws cursor rectangle, always
		{
			//WSRect tile_rect = {
			SDL_SetRenderDrawColor(0xFF, 0xFF, 0x0, 0x44);
			SDL_SetRenderDrawBlendMode(SDL_BLENDMODE_ADD);
			SDL_RenderDrawRect(&cursor_rect);
		}
		SDL_SetRenderDrawColor(0x0, 0x0, 0xFF, 0xFF);
		SDL_RenderDrawLine(bez->m_a.x, bez->m_a.y, bez->m_b.x, bez->m_b.y);
		SDL_RenderDrawLine(bez->m_c.x, bez->m_c.y, bez->m_b.x, bez->m_b.y);
		
		CSPoint<double> last, cur;
		const double _acc = 1.0/16.0;
		last = bez->Plot(0.0);
		SDL_SetRenderDrawColor(0xFF, 0xFF, 0x0, 0xFF);
		for(double i = _acc; i < 1.0+_acc; i += _acc)
		{
			cur = bez->Plot(i);
			SDL_RenderDrawLine(last.x, last.y, cur.x, cur.y);
			last = cur;
		}
		SDL_SetRenderDrawBlendMode(SDL_BLENDMODE_BLEND);
	}
	void onMouseMove(s32 mouse_x, s32 mouse_y)
	{
		if(mousedown == true)
		{
			/*node->setTile(tilenum,  ((int)floor(mouse_x/40.0f))*40, 
									((int)floor(mouse_y/40.0f))*40);*/
		}
	};
	void onMousePress(MouseButtons mouse_button, s32 mouse_x, s32 mouse_y)
	{
		if(mouse_button == SDL_BUTTON_LEFT)
		{
			mousedown = true;
			/*node->setTile(tilenum, 
						((int)floor(mouse_x/40.0f))*40, 
						((int)floor(mouse_y/40.0f))*40);*/
		}
		if(mouse_button == SDL_BUTTON_RIGHT)
		{
			state = st_tilePick;
			mouse_place_x = mouse_x;
			mouse_place_y = mouse_y;
		}
	}
	
	void onMouseRelease(MouseButtons mouse_button, int mouse_x, int mouse_y)
	{
		if(mouse_button == SDL_BUTTON_LEFT)
		{
			mousedown = false;
		}
		if(mouse_button == SDL_BUTTON_RIGHT)
		{
			state = st_tilePlace;
			int mouse_difference_x = mouse_x - mouse_place_x;
			int mouse_difference_y = mouse_y - mouse_place_y;
			mouse_difference_x = std::max(0, std::min(mouse_place_x+ts_width,mouse_difference_x));
			mouse_difference_y = std::max(0, std::min(mouse_place_y+ts_height,mouse_difference_y));
			int tile_x = (int)floor(((float)mouse_difference_x/(float)ts_width)*40);
			int tile_y = (int)floor(((float)mouse_difference_y/(float)ts_height)*40);
			tilenum = tile_y*((int)floor((float)ts_width/40.0f))+tile_x;
			mouse_place_x = 0;
			mouse_place_y = 0;
		}
	}
};

int main(int argc, char** argv)
{
	MGame game;
	game.Run();
	return 0;
}
/*#include <vector>
#include <algorithm>

template <typename _T>
class TVar
{
private:
	CL_Mutex mutex;
	_T safe_variable;
public:
	void lock()
	{
		mutex.lock();
	}
	void unlock()
	{
		mutex.unlock();
	}
	_T Get()
	{
		mutex.lock();
			_T newvar = safe_variable;
		mutex.unlock();
		return newvar;
	}
	void Set(_T setvar)
	{
		mutex.lock();
			safe_variable = setvar;
		mutex.unlock();
	}
};


TVar<int> threaded_int;

TVar<float> x_move;
TVar<float> y_move;

TVar<float> x_pos;
TVar<float> y_pos;

TVar<bool> thread_end;

CL_GraphicContext gc;

class LandPlot
{
private:
	CL_Image spr;
	CL_Pointf position;
public:
	LandPlot( float x, float y)
	{
		position.x = x;
		position.y = y;
		spr = CL_Image(gc, "image_single1.tga");
	}
	static void Draw(const LandPlot& current)
	{
		current.spr.draw(gc, current.position.x-(current.spr.get_width()/2), current.position.y-(current.spr.get_height()/2));
	}
};
std::vector<LandPlot> plots;

void DrawPlot(const LandPlot& current)
{
	LandPlot::Draw(current);
}
class DisplayProgram
{
public:
	static int main(const std::vector<CL_String> &args);
};
class MyRunnable : public CL_Runnable
{
public:
	void run()
	{

		thread_end.Set(false);
		

		while( !thread_end.Get() )
		{
			x_pos.Set(x_pos.Get() + x_move.Get());
			y_pos.Set(y_pos.Get() + y_move.Get());
			CL_System::sleep(10);
		}
		return;
	}
};
void mouse_callback(const CL_InputEvent &event, const CL_InputState &state)
{
	if (event.type == CL_MOUSE_LEFT)
	{
		plots.push_back(LandPlot(event.mouse_pos.x, event.mouse_pos.y));
	}
}

// Create global application object:
// You MUST include this line or the application start-up will fail to
// locate your application object.
CL_ClanApplication app(&DisplayProgram::main);

int DisplayProgram::main(const std::vector<CL_String> &args)
{
	int num_cpu_cores = 0;
	// Setup clanlib modules:
	CL_SetupCore setup_core;
	CL_SetupDisplay setup_display;
	CL_SetupGL setup_gl;
	
	try
	{
		// Create a window:
		CL_DisplayWindow window("Hello World", 640, 480);
		num_cpu_cores = CL_System::get_num_cores();
		char str[1024] = "FPS: 0";
	
		// Retrieve some commonly used objects:
		gc = window.get_gc();
		CL_InputDevice keyboard = window.get_ic().get_keyboard();
		CL_InputDevice mouse = window.get_ic().get_mouse();
		CL_Slot slot = mouse.sig_key_down().connect(&mouse_callback);
		CL_Font font(gc, "Tahoma", 30);
		
		MyRunnable runnable;
		CL_Thread thread;
		thread.start(&runnable);
		
		// Loop until user hits escape:
		float fps = 0.0;
		unsigned int deltaTime = CL_System::get_time();
		unsigned int frameTime = CL_System::get_time();
		CL_Colorf color = CL_Colorf::cadetblue;
		color.a = 0.5f;
		while (!keyboard.get_keycode(CL_KEY_ESCAPE))
		{
			frameTime = CL_System::get_time();
			fps = ((float)frameTime - deltaTime)/1000.0f;
			deltaTime = frameTime;
			sprintf(str,"FPS: %f", 1.0f/fps);
			if(keyboard.get_keycode(CL_KEY_LEFT))
			{
				x_move.Set(-2.0f);
			}
			else if(keyboard.get_keycode(CL_KEY_RIGHT))
			{
				x_move.Set(2.0f);
			}else x_move.Set(0.0f);

			if(keyboard.get_keycode(CL_KEY_UP))
			{
				y_move.Set(-2.0f);
			}
			else if(keyboard.get_keycode(CL_KEY_DOWN))
			{
				y_move.Set(2.0f);
			}else y_move.Set(0.0f);

			// Draw some text and lines:
			gc.clear(CL_Colorf::cadetblue);

			
			CL_Draw::circle(gc, x_pos.Get(), y_pos.Get(), 32.0f, CL_Colorf::rosybrown);
			CL_Draw::line(gc, 0, 110, gc.get_width(), 110, CL_Colorf::yellow);
			CL_Draw::gradient_fill(gc, 0, 0, gc.get_width(), 24, CL_Gradient(CL_Colorf::aliceblue, color));
			font.draw_text(gc, 100, 100, "Hello World!", CL_Colorf::aliceblue);
			font.draw_text(gc, 100, 60, str, CL_Colorf::aliceblue);
			std::for_each(plots.begin(), plots.end(),&DrawPlot);
			
			// Make the stuff visible:
			window.flip(0);
	
			// Read messages from the windowing system message queue,
			// if any are available:
			CL_KeepAlive::process();
		
			// Avoid using 100% CPU in the loop:
			CL_System::sleep(10);
		}
		thread_end.Set(true);
		thread.join();
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();

		return -1;
	}
	
	return 0;
}*/