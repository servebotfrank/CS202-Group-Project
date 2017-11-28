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

	std::cout << getDependancyAndAppInfoString() << std::endl;
	initSFMLStates();
	initOpenGLStates();

	// temporary
	{
		const std::string PATH_TO_PLAYER = "../res/models/playerTemp.obj";
		const std::string PATH_TO_BACKGROUND = "../res/models/background00.obj";
		const std::string PATH_TO_RECTANGLE = "../res/models/platformRectangle.obj";
		const std::string PATH_TO_PLAYER_VERT_SOURCE = "../res/shaders/playerShaderVertex.vert";
		const std::string PATH_TO_PLAYER_FRAG_SOURCE ="../res/shaders/playerShaderFragment.frag";
		const std::string PATH_TO_VERT_SOURCE = "../res/shaders/simpleVertex.vert";
		const std::string PATH_TO_FRAG_SOURCE = "../res/shaders/simpleFragment.frag";

		gameObjects_.push_back(objectFactory_.make(GameObjectTypes::PLAYER, PATH_TO_PLAYER, PATH_TO_VERT_SOURCE, PATH_TO_FRAG_SOURCE, glm::vec3(0, 4, 0)));
		gameObjects_.push_back(objectFactory_.make(GameObjectTypes::PLATFORM, PATH_TO_RECTANGLE, PATH_TO_VERT_SOURCE, PATH_TO_FRAG_SOURCE, glm::vec3(0, -2, 0)));

		playerIterator_ = gameObjects_.begin();
	}
}
void Game::initSFMLStates() {
	contextSettings_ = window_.getSettings();
	sf::Image icon;
	if(!icon.loadFromFile("../res/textures/icon.png")) {
		throw std::runtime_error("Error::LoadFromFile()::failed to load icon");
	}
	window_.setIcon(128, 128, icon.getPixelsPtr()); // icon not showing on Ubuntu Gnome
//	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(framerateLimit_);
	window_.setActive();
}
void Game::initOpenGLStates() const {
#ifndef Xcode
	glewExperimental = GL_TRUE; // tells glew to use the newest features, features from opengl 3.3 and higher
								// else glew only loads features from 1.1 to 3.2
	GLenum glewErr = glewInit(); // loads opengl extensions
#endif
	if(glewErr != GLEW_OK) {
		throw std::runtime_error("Error::glewInit()::failed");
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // sets tha background to black
	glEnable(GL_DEPTH_TEST); // draws faces behind appropriate faces instead of drawing the most recently process face infront of all other faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // doesn't draw faces that are facing away from the camera
}

void Game::run() {
	running_ = true;
	bool runningCommand = false;
	while(running_) { // main event loop
		if(!runningCommand) {
			processEvents();
		}

		checkCollisions();
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

std::string Game::getDependancyAndAppInfoString() const {
	std::string versionsString =
		"Application Version: " +
		std::to_string(versionMajor_)+"."+
		std::to_string(versionMinor_)+"."+
		std::to_string(versionRevision_)+"\n"+

		"SFML Version: " +
		std::to_string(SFML_VERSION_MAJOR) + "." +
		std::to_string(SFML_VERSION_MINOR) + "." +
		std::to_string(SFML_VERSION_PATCH) + "\n" +

		"GLEW Version: " +
		std::to_string(GLEW_VERSION_MAJOR) + "." +
		std::to_string(GLEW_VERSION_MINOR) + "." +
		std::to_string(GLEW_VERSION_MICRO) + "\n" +

		"OpenGL Version: ";
		std::string openGLVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
		versionsString += openGLVersion;
	return versionsString;
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
					std::cout<<"about to call function to set xy velocities"<<std::endl;
					(*playerIterator_)->getDynamicObject().setXVelocity(-0.5);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					(*playerIterator_)->faceRight();
					std::cout<<"about to call function to set xy velocities"<<std::endl;
					(*playerIterator_)->getDynamicObject().setXVelocity(0.5);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					
				} else {
					help();
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

void Game::checkCollisions() const {
	if(gameObjects_.size() >= 2) {
		for(auto firstObjectIt = gameObjects_.begin(); firstObjectIt != gameObjects_.end() - 1; ++firstObjectIt) {
			for(auto secondObjectIterator = gameObjects_.begin() + 1; secondObjectIterator != gameObjects_.end(); ++secondObjectIterator) {
				bool collidingX = (*firstObjectIt)->getPosition()[0] + (*firstObjectIt)->getHeight() >= (*secondObjectIterator)->getPosition()[0] && (*secondObjectIterator)->getPosition()[0] + (*secondObjectIterator)->getHeight() >= (*firstObjectIt)->getPosition()[0];
				bool collidingY = (*firstObjectIt)->getPosition()[1] + (*firstObjectIt)->getWidth() >= (*secondObjectIterator)->getPosition()[1] && (*secondObjectIterator)->getPosition()[1] + (*secondObjectIterator)->getWidth() >= (*firstObjectIt)->getPosition()[1];
				bool colliding = collidingX && collidingY;
				if(colliding) {
					std::cout << (*firstObjectIt)->getDescription() << " is colliding with " << (*secondObjectIterator)->getDescription() << std::endl;
					(*firstObjectIt)->setCollisionTarget(*secondObjectIterator);
					(*secondObjectIterator)->setCollisionTarget(*firstObjectIt);
				} else {
					(*firstObjectIt)->setCollision(false);
					(*secondObjectIterator)->setCollision(false);
				}
			}
		}
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



