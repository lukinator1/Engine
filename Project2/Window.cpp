#include "Window.h"
Window::Window(int width = 800, int height = 600, std::string title = "Untitled", std::string icon = "Defaulticon.png", bool fullscreen = false, bool desktopfullscreen = true, bool borderless = false, bool vsync = false)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	SDL_Init(SDL_INIT_EVENTS);
	windowwidth = width;
	windowheight = height;
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //bit data for 1 pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (fullscreen == true) {
		if (borderless == false) {
			if (desktopfullscreen == true) {
				window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE);
				}
			else {
				window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);
			}
		}
		else if (borderless == true) {
			if (desktopfullscreen == true) {
				window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
			}
			else {
				window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
			}
		}
	}
	else if (fullscreen == false) {
		if (borderless == true) {
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
		}
		else {
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		}
	}
	setWindowIcon(icon);
	glContext = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		engineLog(__FILE__, __LINE__, "Glew failed to initialize. Rendering mechanics won't work.", 3, 2, false);
	}

	if (vsync == false) {
		SDL_GL_SetSwapInterval(0);
	}
	else if (vsync == true) {
		SDL_GL_SetSwapInterval(1);
	}
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glViewport(0, 0, windowwidth, windowheight);
	/*glEnable(GL_CULL_FACE);*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	/*glEnable(GL_FRAMEBUFFER_SRGB);*/
	/*glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	glClearColor(0.0, 0.0, 0.0, 0.0);
}
Window::Window(int width, int height)
{
	windowwidth = width;
	windowheight = height;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //bit data for 1 pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	window = SDL_CreateWindow("Untitled", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowwidth, windowheight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	glContext = SDL_GL_CreateContext(window);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		engineLog(__FILE__, __LINE__, "Glew failed to initialize. Rendering mechanics won't work.", 3, 2, false);
	}

	SDL_GL_SetSwapInterval(0);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glViewport(0, 0, windowwidth, windowheight);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	/*glEnable(GL_FRAMEBUFFER_SRGB);*/
	glEnable(GL_DEPTH_CLAMP);
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	glClearColor(0.0, 0.0, 0.0, 0.0);
}
int Window::getWindowWidth() {
	return windowwidth;
}
int Window::getWindowHeight() {
	return windowheight;
}
void Window::setWindow(int newwidth, int newheight) {
	windowheight = newheight;
	windowwidth = newwidth;
	SDL_SetWindowSize(this->window, newwidth, newheight);
}
void Window::setWindow(int newwidth, int newheight, const char* newtitle) {
	windowheight = newheight;
	windowwidth = newwidth;
	SDL_SetWindowSize(this->window, newwidth, newheight);
	SDL_SetWindowTitle(this->window, newtitle);
}
void Window::setWindowIcon(std::string filename) { 
	Texture icon;
	int width, height, components;
	unsigned char * pixels;
	icon.loadIconPixels(filename, pixels, width, height, components);
	
	if (pixels != NULL) {
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 4 * width, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
			SDL_SetWindowIcon(window, surface);
		}
		else {
			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 4 * width, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
			SDL_SetWindowIcon(window, surface);
			SDL_FreeSurface(surface);
		}
	}
}
bool Window::closeRequested()
{
	return closerequested;
}
bool Window::Maximized() {
	return maximized;
}
bool Window::Minimized()
{
	return minimized;
}
void Window::setWindowBordered(bool isbordered) {
	if (isbordered == true) {
		SDL_SetWindowBordered(this->window, SDL_TRUE);
	}
	else if (isbordered == false) {
		SDL_SetWindowBordered(this->window, SDL_FALSE);
	}
}
void Window::setFullscreen(bool fullscreen) {		//error codes?
	if (fullscreen == true) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else if (fullscreen == false) {
		SDL_SetWindowFullscreen(window, 0);
	}
}
void Window::setFullscreen(bool fullscreen, bool desktop) {		//error codes?
	if (fullscreen == true && desktop == false) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	if (fullscreen == true && desktop == true) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else if (fullscreen = false) {
		SDL_SetWindowFullscreen(window, 0);
	}
}
void Window::swapWindow() {
	SDL_GL_SwapWindow(window);
}
void Window::updateWindow()//monitor refresh rate
{
	closerequested = false;
	maximized = false;
	minimized = false;
	SDL_GL_SwapWindow(window);
	/*SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
		if (sdlevent.type == SDL_QUIT) {
			Message message(Message::Messagetypes::Windowclose);
			postMessage(message);
			/*Message message(Windowclose);
			postMessage(Windowclose);
			std::cout << "messagequeue size: " << messagequeue.size() << std::endl;
		}
	}*/
	/*glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::clearWindow(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::closeWindow() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Window::handleMessage(Message &message)
{
	if (!messagequeue.empty()) {
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Closebuttonpressed:
			std::cout << "Message: windowclose called." << std::endl;
			std::cout << "messagequeue size: " << messagequeue.size() << std::endl;
			closerequested = true;
			break;
		case Message::Messagetypes::Maximized:
			std::cout << "Message: window maximized." << std::endl;
			maximized = true;
			break;
		case Message::Messagetypes::Minimized:
			std::cout << "Message: window minimized." << std::endl;
			minimized = true;
			break;
		}
		}
	}
void Window::postMessage(Message message) {	
	if (messagequeue.size() < messagequeuecapacity) {
		messagequeue.push(message);
	}
}
Window::~Window()
{
}
/*void Window::postMessage(Message::Messagetypes messagetype, int dataone, int datatwo)
{
	if (messagequeue.size() < 32) {
		Message newmessage(messagetype, Message::Category::Window);
		newmessage.messagedataone = dataone;
		newmessage.messagedatatwo = datatwo;
		messagequeue.push(newmessage);
	}
}*/