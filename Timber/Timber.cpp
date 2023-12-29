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
	sf::Sprite spriteCloud1;
	sf::Sprite spriteCloud2;
	sf::Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variables to control time itself
	sf::Clock clock;

	// Track whether the game is running
	bool paused = true;


	
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
			// Cloud 1
			if (!cloud1Active)
			{

				// How fast is the cloud;
				std::srand((int)std::time(0) * 10);
				cloud1Speed = (std::rand() % 200);

				//How high is the cloud
				std::srand((int)std::time(0) * 10);
				float height = (std::rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
			{

				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);

				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					//set it as a "new" cloud
					cloud1Active = false;
				}

			}

			// Cloud 2


			if (!cloud2Active)
			{

				// How fast is the cloud;
				std::srand((int)std::time(0) * 20);
				cloud2Speed = (std::rand() % 200);

				//How high is the cloud
				std::srand((int)std::time(0) * 20);
				float height = (std::rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{

				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);

				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					//set it as a "new" cloud
					cloud2Active = false;
				}

			}

			// Cloud 3
			if (!cloud3Active)
			{

				// How fast is the cloud;
				std::srand((int)std::time(0) * 30);
				cloud3Speed = (std::rand() % 200);

				//How high is the cloud
				std::srand((int)std::time(0) * 30);
				float height = (std::rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{

				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);

				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud3.getPosition().x > 1920)
				{
					//set it as a "new" cloud
					cloud3Active = false;
				}

			}
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
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the insect
		window.draw(spriteBee);
		
		// Show everything we just drew
		window.display();

	}

	return 0;
}

