// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include "ECE_Centipede.hpp"
#include <vector>
#include <random>
#include <list>
#include <chrono>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

enum class state {
	EMPTY,
	HEALTHY_MUSHROOM,
	DESTROYED_MUSHROOM
};

struct mushroom {
	Sprite spriteMushroom;
	state currentState;
};

const int NUM_MUSHROOMS = 30;
const int NUM_LIVES = 3;

const int X_RESOLUTION = 1920;
const int Y_RESOLUTION = 1080;

const Color darkYellow = Color(112, 119, 24);

int main()
{
	// Create and open a window for the game
	RenderWindow window(VideoMode(X_RESOLUTION, Y_RESOLUTION), "Centipede", Style::Fullscreen);

	// Create a background sprite
	Sprite spriteBackground;
	spriteBackground.setColor(Color::Black);
	spriteBackground.setScale(X_RESOLUTION, Y_RESOLUTION);
	spriteBackground.setPosition(0, 0);

	// Make a starship sprite
	Texture textureStarship;
	textureStarship.loadFromFile("graphics/Starship.png");
	Sprite spriteStarship;
	spriteStarship.setTexture(textureStarship);
	spriteStarship.setOrigin(spriteStarship.getLocalBounds().getSize() * 0.5f);
	spriteStarship.setScale(Vector2f(2, 2));
	spriteStarship.setPosition(X_RESOLUTION * 0.5, Y_RESOLUTION * 0.95);

	// Make a spider sprite
	Texture textureSpider;
	textureSpider.loadFromFile("graphics/spider.png");
	Sprite spriteSpider;
	spriteSpider.setTexture(textureSpider);
	spriteSpider.setPosition(0, Y_RESOLUTION * 0.75);

	// Variables to control time itself
	Clock clock;
	Texture startupScreenTexture;
	startupScreenTexture.loadFromFile("graphics/startup.png");
	Sprite startupScreenSprite;
	startupScreenSprite.setTexture(startupScreenTexture);
	startupScreenSprite.setPosition(0, 0);

	// Create bottom and top of screen
	RectangleShape screenBottom;
	screenBottom.setSize(Vector2f(X_RESOLUTION, Y_RESOLUTION * 0.1));
	screenBottom.setFillColor(darkYellow);
	screenBottom.setPosition(0, Y_RESOLUTION * 0.9);

	RectangleShape screenTop;
	screenTop.setSize(Vector2f(X_RESOLUTION, Y_RESOLUTION * 0.1));
	screenTop.setFillColor(darkYellow);
	screenTop.setPosition(0, 0);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;

	// Track whether the game is running
	bool paused = true;

	// Create score counter at top of screen
	int score = 0;
	sf::Text scoreText;
	sf::Font font;
	font.loadFromFile("fonts/SEGOEPRB.TTF");
	scoreText.setFont(font);
	scoreText.setString(to_string(score));
	scoreText.setCharacterSize(50);
	scoreText.setOrigin(scoreText.getLocalBounds().getSize() * 0.5f);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(X_RESOLUTION * 0.5, Y_RESOLUTION * 0.02);

	vector<Sprite> lives(NUM_LIVES);
	for (int i = 0; i < NUM_LIVES; i++) {
		lives[i].setTexture(textureStarship);
		lives[i].setOrigin(lives[i].getLocalBounds().getSize() * 0.5f);
		lives[i].setScale(Vector2f(2, 2));
		lives[i].setPosition(X_RESOLUTION * 0.75 + (i * 50), (Y_RESOLUTION * 0.02) + 20);
	}

	// Random position generator
	default_random_engine generator;
	generator.seed(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution mushroomPositionX(0, X_RESOLUTION);
	uniform_int_distribution mushroomPositionY((int)(Y_RESOLUTION * 0.11), (int)(Y_RESOLUTION * 0.88));

	// Initialize each mushroom into the map
	Texture textureMushroom;
	textureMushroom.loadFromFile("graphics/Mushroom0.png");
	map<pair<float, float>, mushroom> mushrooms;
	for (int i = 0; i < NUM_MUSHROOMS; i++) {
		Vector2f position = Vector2f(mushroomPositionX(generator), mushroomPositionY(generator));
		mushroom oneMushroom;
		oneMushroom.spriteMushroom.setTexture(textureMushroom);
		oneMushroom.currentState = state::HEALTHY_MUSHROOM;
		oneMushroom.spriteMushroom.setOrigin(11, 12);
		oneMushroom.spriteMushroom.setPosition(position);
		mushrooms.insert({ pair(position.x, position.y), oneMushroom });
	}

	vector<ECE_Centipede> centipedes(1, ECE_Centipede());
	
	// Control the player input
	bool acceptInput = false;
	
	while (window.isOpen())
	{
		// score ++;
		Event event;
		while (window.pollEvent(event))
		{
			

			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;

				// hide the axe
				/*spriteAxe.setPosition(2000,
					spriteAxe.getPosition().y);
			}*/

		}

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// Reset the time and the score
			score = 0;
			timeRemaining = 6;

			// Make all the branches disappear
		/*	for (int i = 1; i < NUM_MUSHROOMS; i++)
			{
				branchPositions_remove[i] = side::NONE;
			}*/

			acceptInput = true;


		}

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// More code here next...
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				//playerSide = side::RIGHT;

				//score++;

				//// Add to the amount of time remaining
				//timeRemaining += (2 / score) + .15;

				//spriteAxe.setPosition(AXE_POSITION_RIGHT,
				//	spriteAxe.getPosition().y);

				//

				//spritePlayer.setPosition(1200, 720);

				//// update the branches
				//updateBranches(score);

				//// set the log flying to the left
				//spriteLog.setPosition(810, 720);
				//logSpeedX = -5000;
				//logActive = true;


				acceptInput = false;

			}

			//// Handle the left cursor key
			//if (Keyboard::isKeyPressed(Keyboard::Left))
			//{
			//	// Make sure the player is on the left
			//	playerSide = side::LEFT;

			//	score++;

			//	// Add to the amount of time remaining
			//	timeRemaining += (2 / score) + .15;

			//	spriteAxe.setPosition(AXE_POSITION_LEFT,
			//		spriteAxe.getPosition().y);


			//	spritePlayer.setPosition(580, 720);

			//	// update the branches
			//	updateBranches(score);

			//	// set the log flying
			//	spriteLog.setPosition(810, 720);
			//	logSpeedX = 5000;
			//	logActive = true;


				acceptInput = false;

			}


		}


		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{

			// Measure time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();


			if (timeRemaining <= 0.0f) {

				// Pause the game
				paused = true;
			}


			//// Setup the bee
			//if (!beeActive)
			//{

			//	// How fast is the bee
			//	srand((int)time(0) * 10);
			//	beeSpeed = (rand() % 200) + 200;

			//	// How high is the bee
			//	srand((int)time(0) * 10);
			//	float height = (rand() % 500) + 500;
			//	spriteSpider.setPosition(2000, height);
			//	beeActive = true;

			//}
			//else
			//	// Move the bee
			//{

			//	spriteSpider.setPosition(
			//		spriteSpider.getPosition().x -
			//		(beeSpeed * dt.asSeconds()),
			//		spriteSpider.getPosition().y);

			//	// Has the bee reached the right hand edge of the screen?
			//	if (spriteSpider.getPosition().x < -100)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		beeActive = false;
			//	}
			//}

			// Manage the clouds
			// Cloud 1
			//if (!cloud1Active)
			//{

			//	// How fast is the cloud
			//	srand((int)time(0) * 10);
			//	cloud1Speed = (rand() % 200);

			//	// How high is the cloud
			//	srand((int)time(0) * 10);
			//	float height = (rand() % 150);
			//	spriteCloud1.setPosition(-200, height);
			//	cloud1Active = true;


			//}
			//else
			//{

			//	spriteCloud1.setPosition(
			//		spriteCloud1.getPosition().x +
			//		(cloud1Speed * dt.asSeconds()),
			//		spriteCloud1.getPosition().y);

			//	// Has the cloud reached the right hand edge of the screen?
			//	if (spriteCloud1.getPosition().x > 1920)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		cloud1Active = false;
			//	}
			//}
			//// Cloud 2
			//if (!cloud2Active)
			//{

			//	// How fast is the cloud
			//	srand((int)time(0) * 20);
			//	cloud2Speed = (rand() % 200);

			//	// How high is the cloud
			//	srand((int)time(0) * 20);
			//	float height = (rand() % 300) - 150;
			//	spriteCloud2.setPosition(-200, height);
			//	cloud2Active = true;


			//}
			//else
			//{

			//	spriteCloud2.setPosition(
			//		spriteCloud2.getPosition().x +
			//		(cloud2Speed * dt.asSeconds()),
			//		spriteCloud2.getPosition().y);

			//	// Has the cloud reached the right hand edge of the screen?
			//	if (spriteCloud2.getPosition().x > 1920)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		cloud2Active = false;
			//	}
			//}

			//if (!cloud3Active)
			//{

			//	// How fast is the cloud
			//	srand((int)time(0) * 30);
			//	cloud3Speed = (rand() % 200);

			//	// How high is the cloud
			//	srand((int)time(0) * 30);
			//	float height = (rand() % 450) - 150;
			//	spriteCloud3.setPosition(-200, height);
			//	cloud3Active = true;


			//}
			//else
			//{

			//	spriteCloud3.setPosition(
			//		spriteCloud3.getPosition().x +
			//		(cloud3Speed * dt.asSeconds()),
			//		spriteCloud3.getPosition().y);

			//	// Has the cloud reached the right hand edge of the screen?
			//	if (spriteCloud3.getPosition().x > 1920)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		cloud3Active = false;
			//	}
			//}

			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			//// update the branch sprites
			//for (int i = 0; i < NUM_MUSHROOMS; i++)
			//{

			//	float height = i * 150;

			//	if (branchPositions_remove[i] == side::LEFT)
			//	{
			//		// Move the sprite to the left side
			//		mushrooms[i].setPosition(610, height);
			//		// Flip the sprite round the other way
			//		mushrooms[i].setOrigin(220, 40);
			//		mushrooms[i].setRotation(180);
			//	}
			//	else if (branchPositions_remove[i] == side::RIGHT)
			//	{
			//		// Move the sprite to the right side
			//		mushrooms[i].setPosition(1330, height);
			//		// Set the sprite rotation to normal
			//		mushrooms[i].setOrigin(220, 40);
			//		mushrooms[i].setRotation(0);

			//	}
			//	else
			//	{
			//		// Hide the branch
			//		mushrooms[i].setPosition(3000, height);
			//	}
			//}

			// Handle a flying log				
			//if (logActive)
			//{

			//	spriteLog.setPosition(
			//		spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
			//		spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

			//	// Has the insect reached the right hand edge of the screen?
			//	if (spriteLog.getPosition().x < -100 ||
			//		spriteLog.getPosition().x > 2000)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		logActive = false;
			//		spriteLog.setPosition(810, 720);
			//	}
			//}

			// has the player been squished by a branch?
			//if (branchPositions_remove[5] == playerSide)
			//{
			//	// death
			//	paused = true;
			//	acceptInput = false;

			//	// Draw the gravestone
			//	spriteRIP.setPosition(525, 760);

			//	// hide the player
			//	spritePlayer.setPosition(2000, 660);

			//	// Change the text of the message
			//	messageText.setString("SQUISHED!!");

			//	// Center it on the screen
			//	FloatRect textRect = messageText.getLocalBounds();

			//	messageText.setOrigin(textRect.left +
			//		textRect.width / 2.0f,
			//		textRect.top + textRect.height / 2.0f);

			//	messageText.setPosition(1920 / 2.0f,
			//		1080 / 2.0f);

			//}


		}// End if(!paused)

		 /*
		 ****************************************
		 Draw the scene
		 ****************************************
		 */

		if (paused) {
			window.clear();
			window.draw(startupScreenSprite);
		} else {
			window.clear();

			// Draw our game scene here
			window.draw(spriteBackground);

			// Draw the screen bottom and top
			window.draw(screenBottom);
			window.draw(screenTop);

			// Draw the starship
			window.draw(spriteStarship);

			// Draw the spider
			window.draw(spriteSpider);

			// Draw the score
			window.draw(scoreText);

			// Iterate over map and draw mushrooms
			map<pair<float, float>, mushroom>::iterator it;
			for (it = mushrooms.begin(); it != mushrooms.end(); it++) {
				window.draw(it->second.spriteMushroom);
			}

			// Draw lives in the corner
			for (int i = 0; i < NUM_LIVES; i++) {
				window.draw(lives[i]);
			}
		}

		// Show everything we just drew
		window.display();
	}

	return 0;
}

//// Function definition
//void updateBranches(int seed)
//{
//	// Move all the branches down one place
//	for (int j = NUM_MUSHROOMS - 1; j > 0; j--) {
//		branchPositions_remove[j] = branchPositions_remove[j - 1];
//	}
//
//	// Spawn a new branch at position 0
//	// LEFT, RIGHT or NONE
//	srand((int)time(0) + seed);
//	int r = (rand() % 5);
//
//	switch (r) {
//	case 0:
//		branchPositions_remove[0] = side::LEFT;
//		break;
//
//	case 1:
//		branchPositions_remove[0] = side::RIGHT;
//		break;
//
//	default:
//		branchPositions_remove[0] = side::NONE;
//		break;
//	}
//
//
//}



