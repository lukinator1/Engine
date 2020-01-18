#include "Window.h"
//to do: window icon + resolution
namespace Engine{
Window::Window(int width, int height, std::string title)
{
	windowwidth = height;
	windowheight = height;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //bit data for 1 pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	glContext = SDL_GL_CreateContext(window);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	SDL_GL_SetSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

}
Window::~Window()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
}
void Window::handleMessage(Message message)
{
	/*SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
	}*/
	Engine::messagequeue.push(message);
	switch (message->messagetype) { //other window functions possible
	case Message::Messagetypes::Windowclose:
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		break;
	}
}
void Window::updateWindow()
{
	SDL_GL_SwapWindow(window);
	//SDL_Delay(1); for monitor refresh rate
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
		if (sdlevent.type == SDL_QUIT) {
			setWindow(300, 200, "monkey");
			std::cout << "window closed";
		}
	}
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Window::setWindow(int newwidth, int newheight) {
	SDL_SetWindowSize(this->window, newwidth, newheight);
}
void Window::setWindow(int newwidth, int newheight, const char* newtitle) {
	SDL_SetWindowSize(this->window, newwidth, newheight);
	SDL_SetWindowTitle(this->window, newtitle);
}
void Window::setWindowIcon() {

} //to do
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
int Window::getWindowWidth(Window window) {
	return windowheight;
}
int Window::getWindowHeight(Window window) {
	return windowheight;
}
}