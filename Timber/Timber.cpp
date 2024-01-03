#include <SFML/Graphics.hpp>
#include<cstdlib>
#include<ctime>
#include <string>
#include<sstream>

int main()
{
	// Creating a video mode object
	sf::VideoMode vm(1920, 1080);

	// Creating and opening a window for the game
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

	// Setting Background

	// Creating a texture to hold the background
	sf::Texture textureBackground;

	// load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	sf::Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the sprite background to cover the screen
	spriteBackground.setPosition(0, 0);

	// Making a tree sprite
	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Preparing the bee sprite
	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	// is the bee currently moving?
	bool beeActive = false;
	// How fast can the bee fly?
	float beeSpeed = 0.0f;

	// Making 3 cloud sprites from one texture
	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	sf::Sprite spriteCloud[3];

	for (int i = 0; i < 3; i++)
	{
		spriteCloud[i].setTexture(textureCloud);
	}

	spriteCloud[0].setPosition(0, 0);
	spriteCloud[1].setPosition(0, 250);
	spriteCloud[2].setPosition(0, 500);

	bool cloudActive[3] = { false,false,false };
	float cloudSpeed[3] = { 0.0f ,0.0f ,0.0f };

	// Variables to control time itself
	sf::Clock clock;

	// Time bar
	sf::RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	sf::Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;

	// Draw some text
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	// Choose a font
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to Start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	// Position the text
	sf::FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);
	
	// Main game loop
	while (window.isOpen())
	{
		/*
		**********************************
		Handle the player's input
		**********************************
		*/

		// If player exits
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{

			window.close();

		}

		// Start the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			paused = false;

			// Reset the time and the score
			score = 0;
			timeRemaining = 6;
		}

		/*
		**********************************
		Update the scene
		**********************************
		*/

		//if the game is not paused
		if (!paused)
		{
			// Measure time since last clock restart and put it in dt (delta time)
			sf::Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();

			// Size up the timeBar
			timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				// Pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("Out of Time!!");

				// Reposition the text based on its new size
				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}


			// Setup the bee
			if (!beeActive)
			{
				// How fast is the bee
				std::srand((int)std::time(0));
				beeSpeed = (std::rand() % 200) + 200;

				// How high is the bee
				std::srand((int)std::time(0) * 10);
				float height = (std::rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
				// if bee is active, move the bee
			{
				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				// Has the bee reached the left-Hand edge of the frame?
				if (spriteBee.getPosition().x < -100)
				{
					//set it up ready to be a "new" bee next frame
					beeActive = false;
				}

			}


			// Manage the clouds
			for (int i = 0; i < 3; i++)
			{
				if (!cloudActive[i])
				{

					// How fast is the cloud;
					std::srand((int)std::time(0) * 10 * i);
					cloudSpeed[i] = (std::rand() % 200);

					//How high is the cloud
					std::srand((int)std::time(0) * 10* i);
					float height = (std::rand() % (150*(i+1)));
					if (i != 0) height -= 150;
					spriteCloud[i].setPosition(-200, height);
					cloudActive[i] = true;
				}
				else
				{

					spriteCloud[i].setPosition(
						spriteCloud[i].getPosition().x +
						(cloudSpeed[i] * dt.asSeconds()),
						spriteCloud[i].getPosition().y);

					// Has the cloud reached the right hand edge of the screen?
					if (spriteCloud[i].getPosition().x > 1920)
					{
						//set it as a "new" cloud
						cloudActive[i] = false;
					}

				}
			}

			//Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		}
	
		/*
		**********************************
		Draw the scene
		**********************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the clouds
		for (int i = 0; i < 3; i++)
		{
			window.draw(spriteCloud[i]);
		}
		
		// Draw the tree
		window.draw(spriteTree);

		// Draw the insect
		window.draw(spriteBee);

		// Draw the score
		window.draw(scoreText);
		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Draw the timebar
		window.draw(timeBar);
		
		// Show everything we just drew
		window.display();

	}

	return 0;
}

