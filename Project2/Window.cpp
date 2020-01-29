#include "Window.h"
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
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
Window::~Window()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
}
void Window::handleMessage(Message &message)
{
	if (!messagequeue.empty()) {
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Closebuttonpressed:
			std::cout << "Message: windowclose called." << std::endl;
			std::cout << "messagequeue size: " << messagequeue.size() << std::endl;
			break;
		}
	}
}
void Window::swapWindow() {
	SDL_GL_SwapWindow(window);
}
void Window::updateWindow()//monitor refresh rate
{
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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
void Window::postMessage(Message message) {
	
	if (messagequeue.size() <= 32) {
		messagequeue.push(message);
	}
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