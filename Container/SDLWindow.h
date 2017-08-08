#include <string>
#include <memory>
#include "SDL.h"     
//#include "SDL_TTF.h" 
//#include "SDL_image.h"

//SDL_Window Wrapper
class cSDL2Window
{
public:
	cSDL2Window();
	~cSDL2Window();

	void InitWindow(std::string title, int height, int width);
	SDL_Window* GetWindow();
private:
	SDL_Window* m_Window;
};
