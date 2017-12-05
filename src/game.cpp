#include "game.hpp"

Game::Game(std::string title) :
			   versionMajor_{Platformer_VERSION_MAJOR},
			   versionMinor_{Platformer_VERSION_MINOR},
			   versionRevision_{Platformer_VERSION_REVISION},
			   contextSettings_{
							/*depth_bits*/ 24, /*stencil_bits*/ 8, /*antialiasing_level*/ 4,
							/*major*/ Platformer_OPENGL_MAJOR, /*Requested OpenGL context version*/
							/*minor*/ Platformer_OPENGL_MINOR },
			   window_{
							sf::VideoMode(800, 600), title,
							sf::Style::Default, contextSettings_ },
			   running_{false},
			   gameObjects_(0),
			   objectFactory_{},
			   fov_{90}, projection_{getProjection()},
			   camera_{},
			   framerateLimit_{30},
			   elevations_(std::make_shared<std::vector<double>>())
{

	std::cout << getDependancyAndAppInfoString() << std::endl;
	initSFMLStates();
	initOpenGLStates();

	const std::string pathToLevelOne = "../levels/level_one.txt";
	loadLevel(pathToLevelOne);
	playerIterator_ = gameObjects_.begin();
}

void Game::loadLevel(const std::string &pathToFile) {
	std::ifstream input(pathToFile);
	if(!input) {
		throw std::runtime_error("Error::loadLevel()::ifstream() file not found");
	}

	std::string line;
	// read each line in the file
	while(getline(input, line)) {
		std::stringstream ss(line);
		std::string word;
		// read each word(string seperated by white-space)
		while(ss >> word) {
			// if the word is one of the concrete GameObject classes
			// pass the ifstream to the loadGameObject which finishes loading
			// the rest of the data used to initialize the GameObject
			if(word == "Player") {
				loadGameObject(input, GameObjectTypes::PLAYER);
			} else if(word == "Platform") {
				loadGameObject(input, GameObjectTypes::PLATFORM);
			} else if(word == "Enemy") {
				loadGameObject(input, GameObjectTypes::ENEMY);
			}
			// if the first word is elevations push_back the number that follow
			if(word == "elevations") {
				elevations_->reserve(300);
				while(ss >> word) {
					elevations_->push_back(std::stod(word));
				}
			}
		}
	}
}
void Game::loadGameObject(std::ifstream &input, GameObjectTypes type) {
	// The data that will be retrived and passed to the GameObjectFactory objectFactory_
	std::string pathToMesh;
	std::string pathToVertexShaderSrc;
	std::string pathToFragShaderSrc;
	glm::vec3 initialPosition;

	std::string line;
	bool foundPosition = false;
	while(getline(input, line)) {
		std::stringstream ss(line);
		std::string word;
		while(ss >> word) {
			if(word == "mesh") {
				// gets the word that follows mesh - should be something ending in .obj
				if(ss >> word) {
					pathToMesh = word;
				} else {
					throw std::runtime_error("Error::loadGameObject() path to .obj not found");
				}
			} else if(word == "vert") {
				// get the word that follows vert - should end in .vert
				if(ss >> word) {
					pathToVertexShaderSrc = word;
				} else {
					throw std::runtime_error("Error::loadGameObject() path to vertex shader not found");
				}
			} else if(word == "frag") {
				// gets the word that follows frag - should in in .frag
				if(ss >> word) {
					pathToFragShaderSrc = word;
				} else {
					throw std::runtime_error("Error::loadGameObject() path to fragment shader not found");
				}
			} else if(word == "pos") {
				// gets the next three words that follow pos - should be numbers
				float x, y, z;
				if(ss >> word) {
					x = std::stof(word);
					if(ss >> word) {
						y = std::stof(word);
						if(ss >> word) {
							z = std::stof(word);
						} else {
							z = 0;
						}
						initialPosition = glm::vec3(x, y, z);
						foundPosition = true;
					} else {
						throw std::runtime_error("Error::loadGameObject() initial y position not found");
					}
				} else {
					throw std::runtime_error("Error::loadGameObject() initial x position not found");
				}
			} else if(word == "end" || (foundPosition && !pathToMesh.empty() && !pathToVertexShaderSrc.empty() && !pathToFragShaderSrc.empty())){
				// once complete call GameObjectFactory::make which initializes
				// GameObject. It uses shared_ptrs shader programs and meshes
				// to save on graphics memory
				gameObjects_.push_back(objectFactory_.make(
					type,
					pathToMesh,
					pathToVertexShaderSrc,
					pathToFragShaderSrc,
					initialPosition,
					elevations_
				));
				std::cout << "added object: " << gameObjects_.back()->getDescription() << std::endl;
				return;
			} else {
				throw std::runtime_error("Error::loadGameObject() incomplete or wrongly formated data");
			}
		}
	}
}
void Game::saveLevel(const std::string &pathToFile) {
	std::ofstream output(pathToFile);
	if(!output) {
		throw std::runtime_error("Error::ifstream() file not found");
	}

	std::string line;
}
void Game::initSFMLStates() {
	contextSettings_ = window_.getSettings();
	//sf::Image icon;
	//if(!icon.loadFromFile("../res/textures/icon.png")) {
	//	throw std::runtime_error("Error::LoadFromFile()::failed to load icon");
	//}
	//window_.setIcon(128, 128, icon.getPixelsPtr()); // icon not showing on Ubuntu Gnome
	// SFML icons don't work with GNOME so I thought "whats the point"
//	window_.setVerticalSyncEnabled(true);

	// limit the framerate limit to 30 fps so that the physics objects are in sync
	window_.setFramerateLimit(framerateLimit_);

	// does this by default - it is redundant but explicit
	window_.setActive();
}
void Game::initOpenGLStates() const {
// use glew if on linux else use
#ifdef __linux__
	glewExperimental = GL_TRUE; // tells glew to use the newest features, features from opengl 3.3 and higher
								// else glew only loads features from 1.1 to 3.2
	GLenum glewErr = glewInit(); // loads opengl extensions
	if(glewErr != GLEW_OK) {
		throw std::runtime_error("Error::glewInit()::failed");
	}
#endif
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // sets tha background to black
	glEnable(GL_DEPTH_TEST); // draws faces behind appropriate faces instead of drawing the most recently process face infront of all other faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // doesn't draw faces that are facing away from the camera
}

void Game::run() {
	//SoundManager::SoundManager gameMusic = default;
	//gameMusic.playMusic();
    sf::Music bgMusic;
    if (!bgMusic.openFromFile("../res/sounds/BgMusic.wav"))
    {
        std::cout <<"Failed to load background music... \n" << std::endl;
    } else
   {
    bgMusic.play();
    bgMusic.setLoop(true);
}

	running_ = true;
	//bool runningCommand = false;
	while(running_) { // main event loop

		// used in the draw function - should have also been used in the updatePhysics/physics_object's incrementPosition fucntion
		sf::Time elapsed = clock_.getElapsedTime();

		processEvents();

		// the camera always follows the player and is three units above it and 10 units away away from it in the z direction
        camera_.setPosition(glm::vec3( (*playerIterator_)->getXPosition(),(*playerIterator_) -> getYPosition()+3,10));

		checkCollisions();
		update();

		draw(elapsed);
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

#ifdef __Linux__
        "GLEW Version: " +
		std::to_string(GLEW_VERSION_MAJOR) + "." +
		std::to_string(GLEW_VERSION_MINOR) + "." +
		std::to_string(GLEW_VERSION_MICRO) + "\n" +
#endif
		"OpenGL Version: ";
		std::string openGLVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
		versionsString += openGLVersion;
	return versionsString;
}
/*
void Game::processCommand(std::string & command) {

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
	//LIST OF COMMANDS
	//move, flip, jump, and stop
	//std::string command;
	//std::cin >> command;
	
	/*
	sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav"))
        return -1;

    ...

    return 0;
	
	if(command == "move" || command == "Move" || command == "MOVE") {
		//float distance = 0;
		//std::cin >> distance;
		//get direction
		if ((*playerIterator_)->getDirection() == true)		//true is facing right, false is left
		(*playerIterator_)->getDynamicObject().setXVelocity(10.0);
		else
		(*playerIterator_)->getDynamicObject().setXVelocity(-10.0);
		//(*playerIterator_)->move(5);
	} else if(command == "flip" || command == "Flip" || command == "FLIP") {
		if ((*playerIterator_)->getDirection() == true)
		(*playerIterator_)->faceLeft();
		else
		{
		(*playerIterator_)->faceLeft();
		}
	} else if(command == "jump" || command == "Jump" || command == "JUMP") {
		std::cout << "Jumping \n";
		sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile("../res/sounds/jumpSound.wav"))
        std::cout << "Failed to load jumpSound.wav" << std:: endl;
	else
		{
			std::cout << "Loading SOUND FILE" << std::endl;
			sf::Sound jumpSound;
			jumpSound.setBuffer(soundBuffer);
			jumpSound.setVolume(150);
			jumpSound.play();
			std::cout << "Played SOUND FILE" << std::endl;
		}
		(*playerIterator_)->getDynamicObject().setYVelocity(10.0);
		std::cout << "JUMPED \n";
	} else if (command == "stop" || command == "Stop" || command == "STOP")
	{
		(*playerIterator_)->getDynamicObject().setXVelocity(0.0);
	}
	 else {
		help();
	}
	//std::cin.clear();
}
*/
void Game::help() const {
	std::cout << "press left or right arrows to move" << std::endl;
	std::cout << "press space to jump" << std::endl;
	//std::cout << "INVALID COMMAND: Press space and enter a command" << std::endl;
	//std::cout << "Accepted commands Jump, Move, Flip, and Stop" << std::endl;
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
				/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					std::string newCommand;
					std::cout << "Enter a command... \n";
					std::cin >> newCommand;
					processCommand(newCommand);
					std::cout << "Command command completed \n";
				}
			else {
					help();
				}
				*/
				// move left
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					(*playerIterator_)->faceLeft();
					(*playerIterator_)->getDynamicObject().setXVelocity(-7.0);
				}
				// move right
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					(*playerIterator_)->faceRight();
					(*playerIterator_)->getDynamicObject().setXVelocity(7.0);
				}
				// jump
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					(*playerIterator_)->getDynamicObject().setYVelocity(10.0);
				}
				// if stuck
                else if((*playerIterator_)->getDynamicObject().getXVelocity() == 0)
                {
                    (*playerIterator_)->getDynamicObject().setXVelocity(0);
                }
                // print help
                else {
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

void Game::checkCollisions()  {
	if(gameObjects_.size() >= 2) {
		for(auto firstObjectIt = gameObjects_.begin(); firstObjectIt != gameObjects_.end() - 1; ++firstObjectIt) {
			for(auto secondObjectIterator = gameObjects_.begin() + 1; secondObjectIterator != gameObjects_.end(); ++secondObjectIterator) {
				// check if the bounding boxes are in the same X range
				bool collidingX = (*firstObjectIt)->getPosition()[0] + (*firstObjectIt)->getHeight() >= (*secondObjectIterator)->getPosition()[0] && (*secondObjectIterator)->getPosition()[0] + (*secondObjectIterator)->getHeight() >= (*firstObjectIt)->getPosition()[0];
				// check if the bounding boxes are in the same Y domain
				bool collidingY = (*firstObjectIt)->getPosition()[1] + (*firstObjectIt)->getWidth() >= (*secondObjectIterator)->getPosition()[1] && (*secondObjectIterator)->getPosition()[1] + (*secondObjectIterator)->getWidth() >= (*firstObjectIt)->getPosition()[1];
				// if both are true then they are colliding
				bool colliding = collidingX && collidingY;
				if(colliding) {
					(*firstObjectIt)->setCollisionTarget(*secondObjectIterator);
					(*secondObjectIterator)->setCollisionTarget(*firstObjectIt);
					if((*firstObjectIt)->getType() == GameObjectTypes::PLAYER && (*secondObjectIterator)->getType() == GameObjectTypes::ENEMY)
					{
						running_=false;
					}
				} else {
					(*firstObjectIt)->setCollision(false);
					(*secondObjectIterator)->setCollision(false);
				}
			}
		}
	}
}

void Game::draw(const sf::Time &elapsed) const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(auto objectIterator = gameObjects_.begin(); objectIterator != gameObjects_.end(); ++objectIterator) {
		(*objectIterator)->draw(getProjection(), camera_.getView(), elapsed);
	}
	glFlush();
}

void Game::swapFrameBuffers() {
	window_.display();
}
void Game::frameBufferResize(int32_t width, int32_t height) const {
	glViewport(0, 0, width, height);
}
