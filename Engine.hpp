#ifndef __ENGINE__
#define __ENGINE__

#include <SDL2/SDL.h>

#include "config.h"
#include "RenderableCollection.hpp"
#include "ShapeCollection.hpp"
#include "Player.hpp"
#include "AsteroidGenerator.hpp"

#define GLSL(src) "#version 150 core\n" #src

const int NB_MAX_INIT_ASTEROIDS = 20;

class Engine {
	private:
	SDL_Window* m_window;
	SDL_GLContext m_context;
	ShapeCollection m_renderables;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;

	Player m_player;
	AsteroidGenerator m_asteroidGenerator;
	RenderableCollection m_entityCollection;

	bool m_bIsPaused;
	bool m_bPauseButtonReleased;
	bool m_bIsRunning;

	int _initSDL(const char* title, const int x, const int y, const int w, const int h);
	void _initGL();
	void _generateEntities();
	void _createShaders();
	void _createTextures();
	void _createShapes();
	void _handleEvents();
	void _update();
	void _setCamera();
	void _setFieldOfView();
	void _render();
	void _cleanSDL();

	public:
	void init(unsigned int screenWidth, unsigned int screenHeight);
	void run();
	void clean();
};

#endif
