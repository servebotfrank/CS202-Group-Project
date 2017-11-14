#include "game.hpp"

Game::Game(std::string title) : versionMajor_{Platformer_VERSION_MAJOR},
			   versionMinor_{Platformer_VERSION_MINOR},
			   versionRevision_{Platformer_VERSION_REVISION},
			   contextSettings_{
							/*depth_bits*/ 24, /*stencil_bits*/ 8, /*antialiasing_level*/ 4,
							/*major*/ Platformer_OPENGL_MAJOR,
							/*minor*/ Platformer_OPENGL_MINOR },
			   window_{
							sf::VideoMode(800, 600), title,
							sf::Style::Default, contextSettings_ },
			   running_{false},
			   gameObjects_(0),
			   fov_{90}, projection_{getProjection()},
			   camera_{glm::vec3(0.0f,0.0f,5.0f)} {
	// print versions
	std::cout << "Application Version: " << getVersionString() << std::endl;
	std::cout << "SFML Version: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;
	std::cout << "GLEW Version: " << GLEW_VERSION_MAJOR << "." << GLEW_VERSION_MINOR << "." << GLEW_VERSION_MICRO << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Finish initailizing sfml
	contextSettings_ = window_.getSettings();
//	window_.setIcon();
	window_.setVerticalSyncEnabled(true);
	window_.setActive();

	// initialize opengl states
	glewExperimental = GL_TRUE; 
	glewInit();
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// temporary
	const std::string PATH_TO_MODEL = "../res/models/monkey.obj";
	const std::string PATH_TO_VERT_SOURCE = "../res/shaders/simpleVertex.vert";
	const std::string PATH_TO_FRAG_SOURCE = "../res/shaders/simpleFragment.frag";
	gameObjects_.push_back(std::make_unique<Platform>(PATH_TO_MODEL, PATH_TO_VERT_SOURCE, PATH_TO_FRAG_SOURCE));
}

void Game::run() {
	running_ = true;
	while(running_) {
		processEvents();

		update();

		draw();
		swapFrameBuffers();
	}
}

glm::mat4 Game::getProjection() const {
	return glm::perspective(glm::radians(fov_), (float)window_.getSize().x / (float)window_.getSize().y, 0.1f, 100.0f);
}

std::string Game::getVersionString() const {
	std::string versionString =
		std::to_string(versionMajor_)+"."+
		std::to_string(versionMinor_)+"."+
		std::to_string(versionRevision_) ;
	return versionString;
}

void Game::processEvents() {
	sf::Event event;
	while(window_.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				running_ = false;
				break;
			case sf::Event::Resized:
				frameBufferResize(static_cast<int>(event.size.width), static_cast<int>(event.size.height));
				break;
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
			case sf::Event::TextEntered:
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
			case sf::Event::MouseWheelMoved:
			case sf::Event::MouseWheelScrolled:
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
			case sf::Event::MouseMoved:
			case sf::Event::MouseEntered:
			case sf::Event::MouseLeft:
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			case sf::Event::JoystickMoved:
			case sf::Event::JoystickConnected:
			case sf::Event::JoystickDisconnected:
			case sf::Event::TouchBegan:
			case sf::Event::TouchMoved:
			case sf::Event::TouchEnded:
			case sf::Event::SensorChanged:
			case sf::Event::Count:
				break;
			default:
				break;
		}
	}
}

void Game::update() {
	for(auto objectIterator = gameObjects_.begin(); objectIterator != gameObjects_.end(); ++objectIterator) {
		(*objectIterator)->updatePhysics();
	}
}

void Game::draw() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(auto objectIterator = gameObjects_.begin(); objectIterator != gameObjects_.end(); ++objectIterator) {
		(*objectIterator)->draw(getProjection(), camera_.getView());
	}
	glFlush();
}

void Game::swapFrameBuffers() {
	window_.display();
}
void Game::frameBufferResize(int32_t width, int32_t height) const {
	glViewport(0, 0, width, height);
}



