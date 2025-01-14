#include "stdafx.h"
#include "WindowManager.h"

WindowManger::WindowManger::WindowManger(char* title, int posx, int posy, int width, int height)
	:_window(nullptr),
	_renderer(nullptr),
	_fps(60)
{
	_window = SDL_CreateWindow(title, posx, posy, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
	ASSERT(_window);

	_renderer = CreateRenderer();
	ASSERT(_renderer);
}

WindowManger::WindowManger::~WindowManger()
{
	CleanupWindowManger();
}

Framework::IRenderer* WindowManger::WindowManger::CreateRenderer()
{
	ASSERT(_window);
	SDL_Renderer* ren = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return new Renderers::SDL_Renderer_Wrapper(ren);
}

void WindowManger::WindowManger::Update(SDL_Event* e)
{
	DESCENDANT_UNUSED(e);
}

void WindowManger::WindowManger::Render()
{
	Uint32 frametime = SDL_GetTicks();
	Uint32 minFrameTime = GetMinimumFrameTime();

	_renderer->RenderPresent();

	if (SDL_GetTicks() - frametime < minFrameTime)
		SDL_Delay(minFrameTime - (SDL_GetTicks() - frametime));
}

void WindowManger::WindowManger::AddGameObject(Framework::GameObject* gameObject)
{
	_objects.push_back(gameObject);
}

void WindowManger::WindowManger::CleanupWindowManger()
{
	if (_window != nullptr)
		SDL_DestroyWindow(_window);
	if (_renderer != nullptr)
		delete _renderer;

	while (!_objects.empty()) delete _objects.back(), _objects.pop_back();
}

void WindowManger::WindowManger::HandleError(const char* message)
{
	CleanupWindowManger();
	LogError(message);
	SDL_Quit();
}

