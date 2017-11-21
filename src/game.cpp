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
			   objectFactory_{},
			   fov_{90}, projection_{getProjection()},
			   camera_{glm::vec3(0.0f,0.0f,10.0f)},
			   framerateLimit_{30} {
	// print versions
	std::cout << "Application Version: " << getVersionString() << std::endl;
	std::cout << "SFML Version: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;
	std::cout << "GLEW Version: " << GLEW_VERSION_MAJOR << "." << GLEW_VERSION_MINOR << "." << GLEW_VERSION_MICRO << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	initSFMLStates();
	initOpenGLStates();

	// temporary
	const std::string PATH_TO_PLAYER = "../res/models/playerTemp.obj";
	const std::string PATH_TO_BACKGROUND = "../res/models/background00.obj";
	const std::string PATH_TO_PLAYER_VERT_SOURCE = "../res/shaders/playerShaderVertex.vert";
	const std::string PATH_TO_PLAYER_FRAG_SOURCE ="../res/shaders/playerShaderFragment.frag";
	const std::string PATH_TO_VERT_SOURCE = "../res/shaders/simpleVertex.vert";
	const std::string PATH_TO_FRAG_SOURCE = "../res/shaders/simpleFragment.frag";

	gameObjects_.push_back(objectFactory_.make(GameObjectTypes::PLAYER, PATH_TO_PLAYER, PATH_TO_VERT_SOURCE, PATH_TO_FRAG_SOURCE));
	gameObjects_.push_back(objectFactory_.make(GameObjectTypes::PLATFORM, PATH_TO_BACKGROUND, PATH_TO_VERT_SOURCE, PATH_TO_FRAG_SOURCE));

	gameObjects_[0]->translate(glm::vec3(-3.0f, -2.5f, 0));
	gameObjects_[1]->translate(glm::vec3(0,0, -10.0f));

	playerIterator_ = gameObjects_.begin();
}
void Game::initSFMLStates() {
	contextSettings_ = window_.getSettings();
//	window_.setIcon();
//	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(framerateLimit_);
	window_.setActive();
}
void Game::initOpenGLStates() const {
	glewExperimental = GL_TRUE;
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Game::run() {
	running_ = true;
	bool runningCommand_ = false;
	while(running_) {
		if(!runningCommand_) {
			processEvents();
		}

		update();

		draw();
		swapFrameBuffers();
	}
}

glm::mat4 Game::getProjection() const {
	return glm::perspective(glm::radians(fov_), (float)window_.getSize().x / (float)window_.getSize().y, 0.1f, 100.0f);
}

uint16_t Game::getFramerateLimit() const {
	return framerateLimit_;
}

void Game::setFramerateLimit(uint16_t framerateLimit) {
	framerateLimit_ = framerateLimit;
	window_.setFramerateLimit(framerateLimit_);
}

std::string Game::getVersionString() const {
	std::string versionString =
		std::to_string(versionMajor_)+"."+
		std::to_string(versionMinor_)+"."+
		std::to_string(versionRevision_) ;
	return versionString;
}

void Game::processCommand() {
/*
	std::string command;
	std::cin >> command;
	if(command == "move") {
		int distance = 0;
		std::cin >> distance;
		(*playerIterator_)->move(5);
	} else if(command == "flip") {
		(*playerIterator_)->flip();
	} else if(command == "jump") {
		(*playerIterator_)->jump();
	} else {
		help();
	}
*/
}

void Game::help() const {
	std::cout << "press left or right arrows to move" << std::endl;
	std::cout << "press space to jump" << std::endl;
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
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					(*playerIterator_)->faceLeft();
					(*playerIterator_)->translate(glm::vec3(0.25f, 0, 0));
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					(*playerIterator_)->faceRight();
					(*playerIterator_)->translate(glm::vec3(0.25f, 0, 0));
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					//(*playerIterator_)->translate(glm::vec3());
				}
			break;
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



