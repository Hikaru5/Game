// RoadCrossing : frog game 

#include "stdafx.h" 
#include <SFML/Graphics.hpp>   //using namespace sf 
#include <time.h> 

//dimensions for window size and background 
int num_vertBox = 20, num_horzBox = 40;
int size = 16; //number of pixels 
int w = size * num_horzBox;  //background number of pixels in width 
int h = size * num_vertBox;    //background number of pixels in height 
bool end = false;	//Ends the program if true

//Frog variable to determine direction
int direction;

//Obstacle variables to determine length
int obst_length1 = 10; //initial size is 10 
int obst_length2 = 12;	//initial size is 12
int obst_length3 = 15;	//initial size is 15

//Actual Obstacles in game are arrays of coordinates
struct Obst1
{
	int x, y;        //each sprite of obstacle needs an x,y coordinate 
}s[100];

struct Obst2
{
	int x, y;
}s2[100];

struct Obst3
{
	int x, y;
}s3[100];

//***NEW*** this is the player controlled frog 
struct Frog
{
	int x, y;    // only one sprite needed for player 
}frog;

//move obstacles at a constant rate
void move() {

	//1st update body so everything updates in proper order 
	//move the body only!  s[0] = head will not be changed here 
	//initializes x value
	for (int i = obst_length1; i > 0; i--)
	{
		s[i].x = 10;
		s[i].y = s[i - 1].y;
	}
	s[0].x = 10;
	s[0].y -= 1;
	//1st update body so everything updates in proper order 
	//move the body only!  s2[0] = head will not be changed here 
	//initializes x value
	for (int i = obst_length2; i > 0; i--)
	{
		s2[i].x = 19;
		s2[i].y = s2[i - 1].y;
	}
	s2[0].x = 19;
	s2[0].y -= 1;
	//1st update body so everything updates in proper order 
	//move the body only!  s3[0] = head will not be changed here 
	//initializes x value
	for (int i = obst_length3; i > 0; i--)
	{
		s3[i].x = 29;
		s3[i].y = s3[i - 1].y;
	}
	s3[0].x = 29;
	s3[0].y -= 1;
	//Update the frog
	//Frog, frog depends on direction user inputs  
	//if user presses up 
	if (direction == 0)
		frog.y -= 1;

	//if user presses down 
	if (direction == 1)
		frog.y += 1;

	//if user presses left 
	if (direction == 2)
		frog.x -= 1;

	//if user presses right 
	if (direction == 3)
		frog.x += 1;
	direction = -1;

	//***NEW*** Boundary Checking obstacle1 as it hits screen end 
	//loop obstacle back on other side 
	//TOP and BOTTOM 
	if (s[0].y > num_vertBox)
		s[0].y = 0;
	if (s[0].y < 0)
		s[0].y = num_vertBox;

	//***NEW*** Boundary Checking obstacle2 as is hits screen end 
	//loop obstacle back on other side 
	//TOP and BOTTOM 
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;
	if (s2[0].y < 0)
		s2[0].y = num_vertBox;

	//***NEW*** Boundary Checking obstacle3 as is hits screen end 
	//loop obstacle back on other side 
	//TOP and BOTTOM 
	if (s3[0].y > num_vertBox)
		s3[0].y = 0;
	if (s3[0].y < 0)
		s3[0].y = num_vertBox;

	//***NEW*** Boundary Checking frog as is hits screen end 
	//prevent player from moving off-screen
	//TOP and BOTTOM 
	if (frog.y > 19)
		frog.y=19;
	if (frog.y < 0)
		frog.y = 0;
	//LEFT and RIGHT
	if (frog.x < 0)
		frog.x = 0;
	if (frog.x >= num_horzBox)
		end = true;

	//***NEW*** Check if obstacle1 hits player 
	for (int i = 0; i < obst_length1; i++)
	{
		if (frog.y == s[i].y && frog.x == s[i].x)
		{
			end = true;
		}
	}

	//***NEW*** Check if obstacle2 hits player 
	for (int i = 0; i < obst_length2; i++)
	{
		if (frog.x == s2[i].x && frog.y == s2[i].y)
			end = true;
	}

	//***NEW*** Check if obstacle3 hits player 
	for (int i = 0; i < obst_length3; i++)
	{
		if (frog.x == s3[i].x && frog.y == s3[i].y)
			end = true;
	}
}

int main()
{
	//Initializes obstacles at bottom of screen
	for (int i = 0; i < obst_length1; i++)
	{
		s[i].y = 19;
	}
	for (int i = 0; i < obst_length2; i++)
	{
		s2[i].y = 19;
	}
	for (int i = 0; i < obst_length3; i++)
	{
		s3[i].y = 19;
	}
	//Setting pseudorandom time, TODO:discuss true random vs pseudorandom  
	srand(time(0));

	//Window that we can play the game in  
	sf::RenderWindow window(sf::VideoMode(w, h), "Road Crossing Game");

	//Textures load an image into the GPU Memory 
	sf::Texture t1, t2, t3;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");

	//Sprite has physical dimmensions that can be set in  
	//coordinate system, setPosition(x,y), and drawn on screen 
	sf::Sprite sprite1(t1);
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);
	sf::Sprite sprite4(t2);
	sf::Sprite sprite5(t2);

	//***NEW*** initially place frog somewhere on screen 
	frog.x = 0;
	frog.y = 10;

	sf::Clock clock;
	float timer = 0, delay = 0.1f;
	while (window.isOpen())
	{
		//End if frog collides with obstacle or player makes it across the screen
		if (end)
		{
			window.close();
		}
		//Error in class I placed this before the while loop 
		//Should be placed in while loop as shown here to update 
		//timer  
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something 
		sf::Event e;

		//Check when the window is closed 
		while (window.pollEvent(e))
		{
			//If user presses x in the top right, Windows, top left, Mac,  close the window 
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Control for Frog by User 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = 3;

		
		
		if (timer > delay)
		{
			timer = 0; //reset timer 
			move();    //move Obstacles one sprite forward 
		}
		/*****************
		//Draw in window
		*****************/
		window.clear();    //clear the window so new frame can be drawn in 

		
		//NOTE: Order matters as we will draw over items listed first.  
		//Hence the background should be the first thing you will always do 
		//1st: Draw Background first 
		for (int i = 0; i < num_horzBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				//Set position of sprite1 one at a time 
				sprite1.setPosition(i*size, j*size);
				//Draw sprite1 but, do not show it on screen.  
				window.draw(sprite1);
			}
		}

		//2nd: Then Draw obstacles otherwise background will be drawn over obstacles if order was reversed with background 
		for (int i = 0; i < obst_length1; i++)
		{
			//position sprite2 one at a time 
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			//Draw sprite2 one at a time by drawing over background 
			window.draw(sprite2);
		}

		for (int i = 0; i < obst_length2; i++)
		{
			//position sprite4 one at a time 
			sprite4.setPosition(s2[i].x*size, s2[i].y*size);
			//Draw sprite4 one at a time by drawing over background 
			window.draw(sprite4);
		}

		for (int i = 0; i < obst_length3; i++)
		{
			//position sprite5 one at a time 
			sprite5.setPosition(s3[i].x*size, s3[i].y*size);
			//Draw sprite5 one at a time by drawing over background 
			window.draw(sprite5);
		}
		//***NEW*** 3rd: Draw Frog
		sprite3.setPosition(frog.x*size,frog.y*size);
		window.draw(sprite3);

		//Show everything we have drawn on the screen 
		window.display();
	}
	return 0;
}