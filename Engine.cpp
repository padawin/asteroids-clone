// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL/SOIL.h>

#include <SDL2/SDL_opengl.h>

// for math transformations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine.hpp"

void Engine::init(unsigned int screenWidth, unsigned int screenHeight) {
	_initSDL("OpenGL", 0, 0, screenWidth, screenHeight);
	_initGL();
	_createShaders();
	_createShapes();
	_createTextures();
}

void Engine::run() {
	m_world.setNbMaxEntities(NB_MAX_ENTITIES);
	_generateEntities();
	m_bIsPaused = false;
	m_bIsRunning = true;
	m_bPauseButtonReleased = true;
	while (m_bIsRunning) {
		_handleEvents();

		_update();

		_setCamera();
		_setFieldOfView();

		_render();
	}
}

void Engine::clean() {
	glDeleteProgram(m_shaderProgram);
	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);
	m_renderables.clean();
	m_world.clean();
	_cleanSDL();
}

int Engine::_initSDL(const char* title, const int x, const int y, const int w, const int h) {
	char l_bReturn = 1;
	int flags;
	flags = SDL_WINDOW_OPENGL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Init failed\n");
		l_bReturn = 0;
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		m_window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (m_window == 0) {
			printf("Window creation failed\n");
			l_bReturn = 0;
		}
		else {
			m_context = SDL_GL_CreateContext(m_window);
		}
	}

	return l_bReturn;
}

void Engine::_initGL() {
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK); // cull back face
	glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
}

void Engine::_createShaders() {
	// Create and compile the vertex shader
	const char* vertexSource = GLSL(
		in vec3 position;
		in vec3 color;
		in vec2 texture;

		out vec3 Color;
		out vec2 Texture;

		uniform mat4 trans;
		uniform mat4 view;
		uniform mat4 proj;

		void main()
		{
			Color = color;
			Texture = texture;
			gl_Position = proj * view * trans * vec4(position, 1.0);
		}
	);

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, &vertexSource, NULL);
	glCompileShader(m_vertexShader);

	// Create and compile the fragment shader
	const char* fragmentSource = GLSL(
		in vec3 Color;
		in vec2 Texture;

		out vec4 outColor;
		uniform sampler2D textureResource;
		uniform int time;

		void main()
		{
			if (Texture.x == 0.0f && Texture.y == 0.0f) {
				outColor = vec4(Color, 1.0);
			}
			else {
				outColor = texture(textureResource, Texture);
			}
		}
	);

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(m_fragmentShader);

	// link the shaders in a program to be used
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glBindFragDataLocation(m_shaderProgram, 0, "outColor");
	glLinkProgram(m_shaderProgram);
	glUseProgram(m_shaderProgram);
}

void Engine::_createTextures() {
	std::string texturesPath = "./textures/";
	const char* textures[] = {
		"Large_Asteroid_Diffuse.png",
		"Medium_Asteroid_Diffuse.png",
		"Small_Asteroid_Diffuse.png"
	};
	int nbTextures = 3;
	// textures
	GLuint tex[nbTextures];
	glGenTextures(nbTextures, tex);

	glActiveTexture(GL_TEXTURE0);
	for (int currentTexture = 0; currentTexture < nbTextures; ++currentTexture) {
		int width, height;
		unsigned char* image;
		glBindTexture(GL_TEXTURE_2D, tex[currentTexture]);
		image = SOIL_load_image(
			(texturesPath + textures[currentTexture]).c_str(),
			&width,
			&height,
			0,
			SOIL_LOAD_RGB
		);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glUniform1i(glGetUniformLocation(m_shaderProgram, "textureResource"), 0);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		m_world.addTexture(textures[currentTexture], tex[currentTexture]);
	}
}

void Engine::_createShapes() {
	m_renderables.addShape(SHIP);
	m_renderables.addShape(ASTEROID_LARGE);
	m_renderables.addShape(ASTEROID_MEDIUM);
	m_renderables.addShape(ASTEROID_SMALL);
	m_renderables.addShape(GUN_BULLET);
	m_renderables.addShape(MISSILE);
	m_renderables.generateBuffers();
	m_renderables.generateVertexArrays(m_shaderProgram);
}

void Engine::_generateEntities() {
	m_player = new Player();
	m_player->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	m_player->setDirection(Vector3D(0.0f, 1.0f, 0.0f));

	m_asteroidGenerator.setDistanceRecycle(MAX_DISTANCE_FROM_PLAYER);
	m_asteroidGenerator.setRangeDistanceAppear(
		MIN_DISTANCE_ASTEROID_GENERATE,
		MAX_DISTANCE_ASTEROID_GENERATE
	);
	m_world.addEntity(m_player);
}

void Engine::_handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_bIsRunning = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_UP) {
					m_player->thrust(true);
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					m_player->reverseThrust(true);
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					m_player->steerLeft(true);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					m_player->steerRight(true);
				}
				else if (event.key.keysym.sym == SDLK_SPACE) {
					m_player->openFire();
				}
				else if (event.key.keysym.sym == SDLK_1) {
					m_player->setWeapon1();
				}
				else if (event.key.keysym.sym == SDLK_2) {
					m_player->setWeapon2();
				}
				else if (event.key.keysym.sym == SDLK_3) {
					m_player->setWeapon3();
				}
				else if (event.key.keysym.sym == SDLK_4) {
					m_player->setWeapon4();
				}
				else if (event.key.keysym.sym == SDLK_p && m_bPauseButtonReleased) {
					m_bIsPaused = !m_bIsPaused;
					m_bPauseButtonReleased = false;
				}
				break;

			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP) {
					m_player->thrust(false);
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					m_player->reverseThrust(false);
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					m_player->steerLeft(false);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					m_player->steerRight(false);
				}
				else if (event.key.keysym.sym == SDLK_SPACE) {
					m_player->ceaseFire();
				}
				else if (event.key.keysym.sym == SDLK_p) {
					m_bPauseButtonReleased = true;
				}
				break;
		}
	}
}

void Engine::_update() {
	if (m_bIsPaused) {
		return;
	}

	m_asteroidGenerator.update(m_world, m_player->getPosition());
	m_world.update(m_player->getPosition());

	if (m_player->isDead()) {
		m_bIsRunning = false;
	}
}

// Needs to provide player's information
void Engine::_setCamera() {
	glm::mat4 view = glm::lookAt(
		// camera's position
		glm::vec3(m_player->getPosition().getX(), m_player->getPosition().getY(), 30.0f),
		// point where the camera is aiming at (eg player's position)
		glm::vec3(m_player->getPosition().getX(), m_player->getPosition().getY(), m_player->getPosition().getZ()),
		// "up" vector of the camera, for its orientation, based on player's
		// orientation
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	GLint uniView = glGetUniformLocation(m_shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
}

// based on player's speed?
void Engine::_setFieldOfView() {
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 120.0f);
	GLint uniProj = glGetUniformLocation(m_shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

void Engine::_render() {
	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform1i(glGetUniformLocation(m_shaderProgram, "time"), SDL_GetTicks());
	m_world.render(m_shaderProgram, m_renderables);

	SDL_GL_SwapWindow(m_window);
}

void Engine::_cleanSDL() {
	SDL_GL_DeleteContext(m_context);
	SDL_Quit();
}
