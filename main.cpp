#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>

#include "TileMap.h"
#include "Figure.h"

using namespace std;


bool isBigger(string highscore1, string highscore2) {

	string both = highscore1 + highscore2;

	std::istringstream iss(both);
	vector<int> values;
	for (int n = 0; n < 4; n++)
	{
		if (n == 0 || n == 2) {
			string val;
			iss >> val;
		}
		else {
			int val;
			iss >> val;
			values.push_back(val);
		}

	}	

	return values[0] > values[1];

}


int main()
{
	setlocale(LC_ALL, "");
	//random number generator
	srand(time(0));
	


	// create the window
	sf::RenderWindow window(sf::VideoMode(640, 640), "Tilemap");

	// define the level with an array of tile indices
	int level[] = // Const was before int and I removed it
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0


	};

	int levelNextFigure[] = { 0,0,0,0,
							  0,0,0,0,
							  0,0,0,0,
							  0,0,0,0 };

	// create the tilemap from the level definition
	TileMap map;
	if (!map.load("palette3D.png", sf::Vector2u(32, 32), level, 10, 20))
		return -1;

	// create a map for next figure
	TileMap nextFigureMap;
	if (!nextFigureMap.load("palette3D.png", sf::Vector2u(32, 32), levelNextFigure, 4, 4))
		return -1;

	nextFigureMap.setPosition(418.f, 474.f);


	sf::Font font;
	if (!font.loadFromFile("SF_Automaton_Condensed.ttf"))
	{
		cout << "Font not uploaded" << endl;
		return -1;
	}

	//Upload Sounds
	sf::SoundBuffer bufferCubeTurn;
	if (!bufferCubeTurn.loadFromFile("Sounds/cubeTurn.wav"))
		return -1;
	sf::Sound cubeTurn;
	cubeTurn.setBuffer(bufferCubeTurn);

	sf::SoundBuffer bufferCubePlaced;
	if (!bufferCubePlaced.loadFromFile("Sounds/cubePlaced.wav"))
		return -1;
	sf::Sound cubePlaced;
	cubePlaced.setBuffer(bufferCubePlaced);

	sf::SoundBuffer bufferMoveNotAllowed;
	if (!bufferMoveNotAllowed.loadFromFile("Sounds/moveNotAllowed.wav"))
		return -1;
	sf::Sound moveNotAllowed;
	moveNotAllowed.setBuffer(bufferMoveNotAllowed);

	sf::SoundBuffer bufferSpeedUp;
	if (!bufferSpeedUp.loadFromFile("Sounds/speedUp.wav"))
		return -1;
	sf::Sound speedUp;
	speedUp.setBuffer(bufferSpeedUp);

	sf::SoundBuffer bufferRowDestroyed;
	if (!bufferRowDestroyed.loadFromFile("Sounds/rowDestroyed.wav"))
		return -1;
	sf::Sound rowDestroyed;
	rowDestroyed.setBuffer(bufferRowDestroyed);

	sf::SoundBuffer bufferGameOver;
	if (!bufferGameOver.loadFromFile("Sounds/gameOver.wav"))
		return -1;
	sf::Sound gameOverSound;
	gameOverSound.setBuffer(bufferGameOver);



	int score = 0;
	float movingDownSpeed = 1.0f;
	

	sf::Text startText;
	sf::Text pauseText;	
	sf::Text soundOnText;
	sf::Text displayNextText;
	sf::Text scoreText;
	sf::Text exitText;
	sf::Text levelText;
	
	vector<sf::Text> texts = { startText,pauseText,soundOnText,displayNextText,exitText,scoreText,levelText };

	for (int i = 0; i < texts.size(); i++) {
		
		texts[i].setFont(font);
		texts[i].setCharacterSize(22);
		texts[i].setFillColor(sf::Color(255, 255, 102,255));
		texts[i].setLetterSpacing(1.4);
		
	}


	// set the string to display
	texts[0].setString("Start new game");
	texts[1].setString("Pause"); //Press \"P\" to pause	
	texts[2].setString("Sound: On");
	texts[3].setString("Display next: On");
	texts[4].setString("Exit");
	texts[5].setString("Score: "+to_string(score));
	texts[6].setString("Level: " + to_string(int((1.0f - movingDownSpeed + 0.1) * (10))));
	
		

	int textDistance = 60.f;
	texts[0].setPosition(480.f - texts[0].getLocalBounds().width / 2, 100.f);
	texts[1].setPosition(480.f - texts[1].getLocalBounds().width / 2, texts[0].getPosition().y + textDistance);
	texts[2].setPosition(480.f - texts[2].getLocalBounds().width / 2, texts[1].getPosition().y + textDistance);
	texts[3].setPosition(480.f - texts[3].getLocalBounds().width / 2, texts[2].getPosition().y + textDistance);
	texts[4].setPosition(480.f - texts[4].getLocalBounds().width / 2, texts[3].getPosition().y + textDistance);	
	texts[5].setPosition(480.f, 0.f);
	texts[6].setPosition(484.f, 25.f);
	
	

	//Rectangles for buttons	
	
	sf::RectangleShape startRectangle(sf::Vector2f(210.f, 35.f));
	sf::RectangleShape pauseRectangle(sf::Vector2f(210.f, 35.f));	
	sf::RectangleShape soundOnRectangle(sf::Vector2f(210.f, 35.f));
	sf::RectangleShape displayNextRectangle(sf::Vector2f(210.f, 35.f));
	sf::RectangleShape exitRectangle(sf::Vector2f(210.f, 35.f));

	vector<sf::RectangleShape> rectangles = { startRectangle , pauseRectangle , soundOnRectangle , displayNextRectangle , exitRectangle };

	for (int i = 0; i < rectangles.size(); i++) {
		rectangles[i].setPosition(380.f, texts[i].getPosition().y - 3.f);
		rectangles[i].setOutlineThickness(3.f);
		rectangles[i].setOutlineColor(sf::Color::Red);
		rectangles[i].setFillColor(sf::Color::Transparent);
		

	}

		

	sf::Clock clock;
	float timeDifference = 0.0f;
	
	
	Figure figure1;	
	figure1.cube1y = 0;

	Figure nextFigure;
	
	int nextCube1 = 0;
	int nextCube2 = 0;
	int nextCube3 = 0;
	int nextCube4 = 0;

	int cube1;
	int cube2;
	int cube3;
	int cube4;

	int cube1old;
	int cube2old;
	int cube3old;
	int cube4old;
	int figureCounter = 1;
	int oldFigureCounter = 0;
	
	int randomFigureNumber = 1;
	int nextRandomFigureNumber = 1;
	int random5Figures;
	bool isPause = true;
	bool gameOver = false;
	bool displayNext = true;
	bool soundOn = true;
	bool displayHighscore = true;
	
	
	//Lambda function with capture by reference. It's displaing all components of the window	

	auto drawWindow = [&]() {
		window.clear();
		window.draw(map);
		window.draw(nextFigureMap);

		for (int i = 0; i < texts.size(); i++) {
			window.draw(texts[i]);
		}

		for (int i = 0; i < rectangles.size(); i++) {
			window.draw(rectangles[i]);
		}
		
		window.display();
	};	
	
	while (window.isOpen())
	{
		if (figure1.cube1y ==0 && (oldFigureCounter != figureCounter)){
			cout << "Figure Counter number: ----------> " << figureCounter << endl; 
			

			cout << "moving down speed: " << to_string(int((1.0f - movingDownSpeed + 0.1)* (10))) << endl;
			
			
			//int this case we can use only 7 main figures, and the others are just turned main figures
			int random5Figures = (rand() % 7) + 1;

			
			//assigning current figure to choosen earlier figure and choosing next figure 
			if (figureCounter == 1 ) {		
				random5Figures = (rand() % 7) + 1;
				randomFigureNumber = Figure::assignRandomFigure(random5Figures);
				figure1 = figure1.makeRandomFigure(figure1, randomFigureNumber);
			}
			else {
				figure1 = nextFigure;
				randomFigureNumber = nextRandomFigureNumber;
			}
			
			random5Figures = (rand() % 7) + 1;
			nextRandomFigureNumber = Figure::assignRandomFigure(random5Figures);
			nextFigure = nextFigure.makeRandomFigure(nextFigure, nextRandomFigureNumber);


			oldFigureCounter = figureCounter;

			//Getting positions of cubes in new figure 
			cube1 = figure1.cube1x + figure1.cube1y * 10;
			cube2 = figure1.cube2x + figure1.cube2y * 10;
			cube3 = figure1.cube3x + figure1.cube3y * 10;
			cube4 = figure1.cube4x + figure1.cube4y * 10;

			//Checking if there's space for new figure
			if (level[cube1] > 0 || level[cube2] > 0 || level[cube3] > 0 || level[cube4] > 0) {
				gameOver = true;
				//play gameOver sound
				if (soundOn) { gameOverSound.play(); }

			}

			cout << "!gameOver: "<<!gameOver << endl;

			//assembling figure in the first row base on returned cubes coordinates from makeRandomFigure method
			if (!gameOver) {
				level[cube1] = figure1.cubeColor;
				level[cube2] = figure1.cubeColor;
				level[cube3] = figure1.cubeColor;
				level[cube4] = figure1.cubeColor;
			}

			//levelNextFigure - remove old figure from next figure field and fill it with new one
			for (int i = 0; i < 16; i++) {
				levelNextFigure[i] = 0;
			}

			

			nextCube1 = nextFigure.cube1x - 3 + nextFigure.cube1y * 4;
			nextCube2 = nextFigure.cube2x - 3 + nextFigure.cube2y * 4;
			nextCube3 = nextFigure.cube3x - 3 + nextFigure.cube3y * 4;
			nextCube4 = nextFigure.cube4x - 3 + nextFigure.cube4y * 4;
			
			if (displayNext) {
				levelNextFigure[nextCube1] = nextFigure.cubeColor;
				levelNextFigure[nextCube2] = nextFigure.cubeColor;
				levelNextFigure[nextCube3] = nextFigure.cubeColor;
				levelNextFigure[nextCube4] = nextFigure.cubeColor;
			}

						

			//update map with new figure
			if (!map.load("palette3D.png", sf::Vector2u(32, 32), level, 10, 20))
				return -1;

			//update map with next figure
			if (!nextFigureMap.load("palette3D.png", sf::Vector2u(32, 32), levelNextFigure, 4, 4))
				return -1;

			drawWindow();
					
		}





		//Writing "GAME OVER" on game board
		if (gameOver && !isPause) {
			int positionGAME[] = { 1,2,3,11,21,23,31,32,33,51,52,53,61,63,71,72,73,81,83,101,104,111,112,113,114,121,124,131,134,151,152,153,161,171,172,181,191,192,193 }; 

			int positionOVER[] = { 6,7,8,16,18,26,27,28,46,48,56,58,66,68,77,96,97,98,106,116,117,126,136,137,138,156,157,158,156,158,166,168,176,177,178,186,187,196,198 };

			for (int i = 0; i < 200; i++) {
				level[i] = 0;
			}

			for (int i = 0; i < 39; i++) {
				level[positionGAME[i]] = 2;
			}

			for (int i = 0; i < 39; i++) {
				level[positionOVER[i]] = 3;
			}


			//update map with "GAME OVER"
			if (!map.load("palette3D.png", sf::Vector2u(32, 32), level, 10, 20))
				return -1;

			drawWindow();
			
			
			Sleep(3000);

			/////////////////////////////// Highscore mode
			sf::String playerInput;
			sf::Text playerText;


			
			//handeling higgscores
			while (displayHighscore) {


				//creating texts
				sf::Text saveText;
				saveText.setString("Save");
				saveText.setFont(font);
				saveText.setCharacterSize(22);
				saveText.setFillColor(sf::Color(255, 255, 102, 255));
				saveText.setLetterSpacing(1.4);
				saveText.setPosition(150, 270);

				sf::Text okText;
				okText.setString("OK");
				okText.setFont(font);
				okText.setCharacterSize(22);
				okText.setFillColor(sf::Color(255, 255, 102, 255));
				okText.setLetterSpacing(1.4);
				okText.setPosition(500, 550);

				sf::Text scoreValueText;
				scoreValueText.setString("Your score is: " + to_string(score));
				scoreValueText.setFont(font);
				scoreValueText.setCharacterSize(22);
				scoreValueText.setFillColor(sf::Color(255, 255, 102, 255));
				scoreValueText.setLetterSpacing(1.4);
				scoreValueText.setPosition(20, 100);


				sf::Text nameEnterHeader;
				nameEnterHeader.setString("Enter your name: ");
				nameEnterHeader.setFont(font);
				nameEnterHeader.setCharacterSize(22);
				nameEnterHeader.setFillColor(sf::Color(255, 255, 102, 255));
				nameEnterHeader.setLetterSpacing(1.4);
				nameEnterHeader.setPosition(20, 150);

				sf::Text highscoreHeadText;
				highscoreHeadText.setString("Highscores: ");
				highscoreHeadText.setFont(font);
				highscoreHeadText.setCharacterSize(30);				
				highscoreHeadText.setLetterSpacing(1.4);
				highscoreHeadText.setPosition(340, 50);

				
				//creating rectangles for buttons
				sf::RectangleShape saveRectangle(sf::Vector2f(100.f, 35.f));
				sf::RectangleShape okRectangle(sf::Vector2f(100.f, 35.f));

				saveRectangle.setPosition(saveText.getPosition().x + saveText.getLocalBounds().width / 2 - saveRectangle.getLocalBounds().width / 2, saveText.getPosition().y - 3.f);
				saveRectangle.setOutlineThickness(3.f);
				saveRectangle.setOutlineColor(sf::Color::Red);
				saveRectangle.setFillColor(sf::Color::Transparent);

				okRectangle.setPosition(okText.getPosition().x + okText.getLocalBounds().width / 2 - okRectangle.getLocalBounds().width / 2, okText.getPosition().y - 3.f);
				okRectangle.setOutlineThickness(3.f);
				okRectangle.setOutlineColor(sf::Color::Red);
				okRectangle.setFillColor(sf::Color::Transparent);

				//geting highscore list form txt file
				vector<string> highscoreList;
				ifstream inputStream;
				inputStream.open("highscores.txt");				
				while (inputStream.good()) {
					
					string line;
					getline(inputStream, line);
					if (!line.empty()) {
						highscoreList.push_back(line);
					}										
					
				}
				inputStream.close();	
				
				//sorting highscore vector using custom function
				sort(highscoreList.begin(), highscoreList.end(), &isBigger);

				//vector for 10 highest highscores
				vector<string> selectedHighscoreList;

				//filling the vector with 10 highest highscores
				if (highscoreList.size() > 10) {
					for (int i = 0; i < 10; i++) {
						selectedHighscoreList.push_back(highscoreList[i]);
					}
				}
				else {
					for (int i = 0; i < highscoreList.size(); i++) {
						selectedHighscoreList.push_back(highscoreList[i]);
					}
				}

				//creating text with highscores to display
				int firstPositionHighscore = 100.f;
				vector< sf::Text> highscoreTexts;
				for (int i = 0; i < selectedHighscoreList.size(); i++) {
					sf::Text highscore;
					highscore.setFont(font);
					highscore.setCharacterSize(22);
					highscore.setFillColor(sf::Color(255, 255, 102, 255));
					highscore.setLetterSpacing(1.4);
					highscore.setString(selectedHighscoreList[i]);
					highscore.setPosition(340, firstPositionHighscore + i * 30);
					highscoreTexts.push_back(highscore);
				}

				//creating events 
				sf::Event event2;
				while (window.pollEvent(event2))
				{
					//detecting text written by user and saving as a variable
					if (event2.type == sf::Event::TextEntered)
					{
						playerInput += event2.text.unicode;						
						playerText.setString(playerInput);
						playerText.setFont(font);
						playerText.setCharacterSize(22);						
						playerText.setLetterSpacing(1.4);
						playerText.setPosition(20, 200);
					}

					//detecting buttons pressed and taking actions 
					if (event2.type == sf::Event::MouseButtonPressed)
					{
						if (event2.mouseButton.button == sf::Mouse::Left)
						{
							std::cout << "the left button was pressed" << std::endl;
							std::cout << "mouse x: " << event2.mouseButton.x << std::endl;
							std::cout << "mouse y: " << event2.mouseButton.y << std::endl;


							//save the userename and highscore to highscore list after pressing "save" button
							if ((event2.mouseButton.x > saveRectangle.getPosition().x) && (event2.mouseButton.x < saveRectangle.getPosition().x + saveRectangle.getLocalBounds().width) &&
								(event2.mouseButton.y > saveRectangle.getPosition().y) && (event2.mouseButton.y < saveRectangle.getPosition().y + saveRectangle.getLocalBounds().height)) {
																
								playerInput = playerInput + " " + to_string(score);	
								highscoreList.push_back(playerInput);
								ofstream outputStream;
								outputStream.open("highscores.txt");
								for (int i = 0; i < highscoreList.size(); i++) {
									outputStream << highscoreList[i] << endl;
								}
								outputStream.close();														

							}
							//exit highscore mode after pressing ok
							else if ((event2.mouseButton.x > okRectangle.getPosition().x) && (event2.mouseButton.x < okRectangle.getPosition().x + okRectangle.getLocalBounds().width) &&
									(event2.mouseButton.y > okRectangle.getPosition().y) && (event2.mouseButton.y < okRectangle.getPosition().y + okRectangle.getLocalBounds().height)) {

								displayHighscore = false;

							}						
							
						}
					}

				}				

				//displying window with all components
				window.clear();
				window.draw(playerText);
				window.draw(scoreValueText);
				window.draw(saveText);
				window.draw(okText);
				window.draw(highscoreHeadText);
				window.draw(saveRectangle);
				window.draw(okRectangle);
				window.draw(nameEnterHeader);

				for (int i = 0; i < highscoreTexts.size(); i++) {
					window.draw(highscoreTexts[i]);
				}

				
				window.display();
			}
						
			
			//////////////////////////////
		}
				
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
								   			 

			
			bool allowToMove;

			//Checking Mouse buttons
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

													

					if ((event.mouseButton.x > rectangles[1].getPosition().x) && (event.mouseButton.x < rectangles[1].getPosition().x + rectangles[1].getLocalBounds().width) &&
						(event.mouseButton.y > rectangles[1].getPosition().y) && (event.mouseButton.y < rectangles[1].getPosition().y + rectangles[1].getLocalBounds().height)) {
						
									
						if (isPause == true) {
							isPause = false;
							texts[1].setString("Pause");
						}
						else if (isPause == false) {
							isPause = true;
							texts[1].setString("Resume");
						}
						
					}					
					else if ((event.mouseButton.x > rectangles[0].getPosition().x) && (event.mouseButton.x < rectangles[0].getPosition().x + rectangles[0].getLocalBounds().width) &&
						(event.mouseButton.y > rectangles[0].getPosition().y) && (event.mouseButton.y < rectangles[0].getPosition().y + rectangles[0].getLocalBounds().height)) {
						
						isPause = false;

						
						for (int i = 0; i < 200; i++) {
							level[i] = 0;
						}

						figure1.cube1y = 0;
						oldFigureCounter = 0;
						figureCounter = 1;
						gameOver = false;
						movingDownSpeed = 1.0f;
						score = 0;
						texts[5].setString("Score: " + to_string(score));
						
					}
					else if ((event.mouseButton.x > rectangles[4].getPosition().x) && (event.mouseButton.x < rectangles[4].getPosition().x + rectangles[4].getLocalBounds().width) &&
						(event.mouseButton.y > rectangles[4].getPosition().y) && (event.mouseButton.y < rectangles[4].getPosition().y + rectangles[4].getLocalBounds().height)) {
						window.close();

					}
					else if ((event.mouseButton.x > rectangles[3].getPosition().x) && (event.mouseButton.x < rectangles[3].getPosition().x + rectangles[3].getLocalBounds().width) &&
						(event.mouseButton.y > rectangles[3].getPosition().y) && (event.mouseButton.y < rectangles[3].getPosition().y + rectangles[3].getLocalBounds().height)) {


						if (displayNext == true) {
							displayNext = false;
							texts[3].setString("Display next: Off");
							for (int i = 0; i < 16; i++) {
								levelNextFigure[i] = 0;
							}
						}
						else if (displayNext == false) {
							displayNext = true;
							texts[3].setString("Display next: On");

							levelNextFigure[nextCube1] = nextFigure.cubeColor;
							levelNextFigure[nextCube2] = nextFigure.cubeColor;
							levelNextFigure[nextCube3] = nextFigure.cubeColor;
							levelNextFigure[nextCube4] = nextFigure.cubeColor;
						}
					}
					else if ((event.mouseButton.x > rectangles[2].getPosition().x) && (event.mouseButton.x < rectangles[2].getPosition().x + rectangles[2].getLocalBounds().width) &&
						(event.mouseButton.y > rectangles[2].getPosition().y) && (event.mouseButton.y < rectangles[2].getPosition().y + rectangles[2].getLocalBounds().height)) {
						

						if (soundOn == true) {
							soundOn = false;
							texts[2].setString("Sound: Off");
						}
						else if (soundOn == false) {
							soundOn = true;
							texts[2].setString("Sound: On");
						}
					}
				}

				//update map with next figure
				if (!nextFigureMap.load("palette3D.png", sf::Vector2u(32, 32), levelNextFigure, 4, 4))
					return -1;

				drawWindow();
			}

			//checking keyboard keys 
			if (event.type == sf::Event::KeyPressed && !gameOver) {

				//Pressing "R" key
				if (event.key.code == sf::Keyboard::R) {
					cout << "R key has been pressed" << endl;
					for (int i = 0; i < 200; i++) {
						level[i] = 0;
					}

					figure1.cube1y = 0;
					oldFigureCounter = 0;
					figureCounter = 1;
				}


				//Pressing "P" key				
				if (event.key.code == sf::Keyboard::P) {
					cout << "P key has been pressed" << endl;
					if (isPause == true) {
						isPause = false;
						texts[1].setString("Pause");
					}
					else if (isPause == false) {
						isPause = true;
						texts[1].setString("Resume");
					}
				}

				if (!isPause){
					//Pressing Up arrow key
					if (event.key.code == sf::Keyboard::Up) {
						cout << "Up arrow key was pressed." << endl;

						Figure turnedFigure;

						
						//Getting new figure number base on current figure
						randomFigureNumber = Figure::setTurnedFigure(randomFigureNumber); 

						
						turnedFigure = Figure::makeRandomFigure(turnedFigure, randomFigureNumber); 
					
						
						int cube2col = cube2 % 10;
						int cube2row = (cube2 - cube2col) / 10;
					
						//Calculating the difference between starting coordinates of figure and current coordinates of figure
						int colCube2PositionDifference = cube2col - turnedFigure.cube2x;
						int rowCube2PositionDifference = cube2row - turnedFigure.cube2y;
					
						cout << "Cube2 col: " << cube2col << ", cube2 row: " << cube2row << endl;
						
					
						turnedFigure.cube1x = turnedFigure.cube1x + colCube2PositionDifference;
						turnedFigure.cube1y = turnedFigure.cube1y + rowCube2PositionDifference;
						turnedFigure.cube2x = turnedFigure.cube2x + colCube2PositionDifference;
						turnedFigure.cube2y = turnedFigure.cube2y + rowCube2PositionDifference;
						turnedFigure.cube3x = turnedFigure.cube3x + colCube2PositionDifference;
						turnedFigure.cube3y = turnedFigure.cube3y + rowCube2PositionDifference;
						turnedFigure.cube4x = turnedFigure.cube4x + colCube2PositionDifference;
						turnedFigure.cube4y = turnedFigure.cube4y + rowCube2PositionDifference;


						//here we need to check if there's place on the right, left and down side (no other cubes or wall) in order to turn the figure
						cube1old = cube1;
						cube2old = cube2;
						cube3old = cube3;
						cube4old = cube4;

						//getting cubes coordinates from new figure 
						int cube1ToTurn = turnedFigure.cube1x + turnedFigure.cube1y * 10;
						int cube2ToTurn = turnedFigure.cube2x + turnedFigure.cube2y * 10;
						int cube3ToTurn = turnedFigure.cube3x + turnedFigure.cube3y * 10;
						int cube4ToTurn = turnedFigure.cube4x + turnedFigure.cube4y * 10;

						allowToMove = true;
					
						//if there's filed cube in future positon of the figure then the figure shouldn't turn
						//exceptions are other positions of current figure cubes
						//The figure should't turn eighter when the coubes will go beyond the game border
						if (((cube1ToTurn != cube1) && (cube1ToTurn != cube2) && 
							 (cube1ToTurn != cube3) && (cube1ToTurn != cube4) && 
							(level[cube1ToTurn] > 0)) || ((cube1ToTurn % 10 - cube1 % 10) > 5) || ((cube1 % 10 - cube1ToTurn % 10) > 5)) {
							allowToMove = false;
						}
						//cube2 is always in the same posiion while turning figure, so no risk to go beyond game border
						if (((cube2ToTurn % 10 - cube2 % 10) > 5) || ((cube2 % 10 - cube2ToTurn % 10) > 5))  {
							allowToMove = false;
						}
						if (((cube3ToTurn != cube1) && (cube3ToTurn != cube2) && 
							 (cube3ToTurn != cube3) && (cube3ToTurn != cube4) && 
							(level[cube3ToTurn] > 0)) || ((cube3ToTurn % 10 - cube3 % 10) > 5) || ((cube3 % 10 - cube3ToTurn % 10) > 5)) {
							allowToMove = false;
						}
						if (((cube4ToTurn != cube1) && (cube4ToTurn != cube2) && 
							 (cube4ToTurn != cube3) && (cube4ToTurn != cube4) && 
							(level[cube4ToTurn] > 0)) || ((cube4ToTurn % 10 - cube4 % 10) > 5) || ((cube4 % 10 - cube4ToTurn % 10) > 5)) {
							allowToMove = false;
						}
						if (figureCounter == 1 && figure1.cube1y < 2) {
							allowToMove = false;
						}
					
						cout << "Alow to turn: <---------------------" << allowToMove << endl;
						if (allowToMove) {
							//removing old position of figure
							level[cube1old] = 0;
							level[cube2old] = 0;
							level[cube3old] = 0;
							level[cube4old] = 0;

							//assigning turned figure to current figure
							figure1 = turnedFigure;

							//getting cubes coordinates from new figure 
							cube1 = figure1.cube1x + figure1.cube1y * 10;
							cube2 = figure1.cube2x + figure1.cube2y * 10;
							cube3 = figure1.cube3x + figure1.cube3y * 10;
							cube4 = figure1.cube4x + figure1.cube4y * 10;

							//updating level array with new figure
							level[cube1] = figure1.cubeColor;
							level[cube2] = figure1.cubeColor;
							level[cube3] = figure1.cubeColor;
							level[cube4] = figure1.cubeColor;

							//play sound cubeTurn
							if (soundOn) { cubeTurn.play(); }
						}
						else {
							if (soundOn) { moveNotAllowed.play(); }
						}
					
					}

					//Pressing Left arrow key
					if (event.key.code == sf::Keyboard::Left) {
						cout << "Left key was pressed." << endl;

						//vector containing cubes on left side of figure
						vector<int> cubesOnLeft;

						//Checking, which cube/s is/are on the left side of the figure
						if ((cube1 - 1 != cube2) && (cube1 - 1 != cube3) && (cube1 - 1 != cube4)){ 
							cubesOnLeft.push_back(cube1);
						}
						if ((cube2 - 1 != cube1) && (cube2 - 1 != cube3) && (cube2 - 1 != cube4)){
							cubesOnLeft.push_back(cube2);
						}
						if ((cube3 - 1 != cube1) && (cube3 - 1 != cube2) && (cube3 - 1 != cube4)) {
							cubesOnLeft.push_back(cube3);
						}
						if ((cube4 - 1 != cube1) && (cube4 - 1 != cube2) && (cube4 - 1 != cube3)) {
							cubesOnLeft.push_back(cube4);
						}
						//if statement for all cubes should be added here

						

						//Checking if for every single cube on the left side of figue is space on the left side 
						allowToMove =true;
						for (int i = 0; i < cubesOnLeft.size(); i++) {
							if ((level[cubesOnLeft[i] - 1] > 0) || ((cubesOnLeft[i] % 10 - 1) < 0)) {
								allowToMove = false;
							}
						}

						cout << "Alow to move left: <---------------------" << allowToMove << endl;
						//moving all cubes from the figure one position left
						if (allowToMove) {
							cube1old = cube1;
							cube2old = cube2;
							cube3old = cube3;
							cube4old = cube4;
							
							figure1.cube1x--;
							figure1.cube2x--;
							figure1.cube3x--;
							figure1.cube4x--;
													
							cube1--;
							cube2--;
							cube3--;
							cube4--;
																					
							level[cube1old] = 0;	
							level[cube2old] = 0;
							level[cube3old] = 0;
							level[cube4old] = 0;

							level[cube1] = figure1.cubeColor;
							level[cube2] = figure1.cubeColor;
							level[cube3] = figure1.cubeColor;
							level[cube4] = figure1.cubeColor;
						}
						else {
							if (soundOn) { moveNotAllowed.play(); }
						}
					}
					//Pressing Right arrow key
					if (event.key.code == sf::Keyboard::Right) {
						cout << "Right key was pressed." << endl;

						//vector containing cubes on right side of figure
						vector<int> cubesOnRight;
					
						//Checking, which cube/s is/are on the right side ofthe figure
						if ((cube1 + 1 != cube2) && (cube1 + 1 != cube3) && (cube1 + 1 != cube4)){
							cubesOnRight.push_back(cube1);
						}
						if ((cube2 + 1 != cube1) && (cube2 + 1 != cube3) && (cube2 + 1 != cube4)){
							cubesOnRight.push_back(cube2);
						}
						if ((cube3 + 1 != cube1) && (cube3 + 1 != cube2) && (cube3 + 1 != cube4)) {
							cubesOnRight.push_back(cube3);
						}
						if ((cube4 + 1 != cube1) && (cube4 + 1 != cube2) && (cube4 + 1 != cube3)) {
							cubesOnRight.push_back(cube4);
						}
						

						//Checking if for every single cube on the right side of figue is space on the right side 
						allowToMove = true;
						for (int i = 0; i < cubesOnRight.size(); i++) {						
							if ((level[cubesOnRight[i] + 1] > 0) || ((cubesOnRight[i] % 10 + 1) > 9)) {
								allowToMove = false;

							}
						}

						cout << "Alow to move right: <---------------------" << allowToMove << endl;

						//moving all cubes from the figure one position right
						if (allowToMove) {
							cube1old = cube1;
							cube2old = cube2;
							cube3old = cube3;
							cube4old = cube4;
							
							figure1.cube1x++;
							figure1.cube2x++;
							figure1.cube3x++;
							figure1.cube4x++;

							
							cube1++;
							cube2++;
							cube3++;
							cube4++;
							

							level[cube1old] = 0;
							level[cube2old] = 0;
							level[cube3old] = 0;
							level[cube4old] = 0;

							level[cube1] = figure1.cubeColor;
							level[cube2] = figure1.cubeColor;
							level[cube3] = figure1.cubeColor;
							level[cube4] = figure1.cubeColor;							
						}
						else {
							if (soundOn) { moveNotAllowed.play(); }
						}
					}

					//Pressing Down arrow key
					if (event.key.code == sf::Keyboard::Down&& figure1.cube1y <19) {
						cout << "Down key was pressed." << endl;

						//vector containing cubes on the bottom of the figure
						vector<int> cubesOnBottom;
						//checking, which cubes are on the bottom of figure
						if ((cube1 + 10 != cube2) && (cube1 + 10 != cube3) && (cube1 + 10 != cube4)) {
							cubesOnBottom.push_back(cube1);
						}
						if ((cube2 + 10 != cube1) && (cube2 + 10 != cube3) && (cube2 + 10 != cube4)) {
							cubesOnBottom.push_back(cube2);
						}
						if ((cube3 + 10 != cube1) && (cube3 + 10 != cube2) && (cube3 + 10 != cube4)) {
							cubesOnBottom.push_back(cube3);
						}
						if ((cube4 + 10 != cube1) && (cube4 + 10 != cube2) && (cube4 + 10 != cube3)) {
							cubesOnBottom.push_back(cube4);
						}
						
						
						allowToMove = true;
						for (int i = 0; i < cubesOnBottom.size(); i++) {
							if (level[cubesOnBottom[i] + 10] != 0) {
								allowToMove = false;
							}
						}

						cout << "Alow to move down: <---------------------" << allowToMove << endl;

						if (allowToMove) {
							cube1old = cube1;
							cube2old = cube2;
							cube3old = cube3;
							cube4old = cube4;
							
							figure1.cube1y++;
							figure1.cube2y++;
							figure1.cube3y++;
							figure1.cube4y++;

							
							cube1 = figure1.cube1x + figure1.cube1y * 10;
							cube2 = figure1.cube2x + figure1.cube2y * 10;
							cube3 = figure1.cube3x + figure1.cube3y * 10;
							cube4 = figure1.cube4x + figure1.cube4y * 10;
							

							level[cube1old] = 0;
							level[cube2old] = 0;
							level[cube3old] = 0;
							level[cube4old] = 0;

							level[cube1] = figure1.cubeColor;
							level[cube2] = figure1.cubeColor;
							level[cube3] = figure1.cubeColor;
							level[cube4] = figure1.cubeColor;
							
						}
					}

				
					//update map after presing a key
					if (!map.load("palette3D.png", sf::Vector2u(32, 32), level, 10, 20))
						return -1;

					drawWindow();

				}
			}

		}

		
		
		//////////////////////////// Figure goes down every X (movingDownSpeed) second //////////////////////////////////
				
		
		

		sf::Time elapsed1 = clock.getElapsedTime();

		
		
		
		//run this loop only after one full second
		if ((elapsed1.asSeconds()- timeDifference >= movingDownSpeed) && !gameOver && !isPause) {
			

			//getting cubes position
			cube1 = figure1.cube1x + figure1.cube1y * 10;
			cube2 = figure1.cube2x + figure1.cube2y * 10;
			cube3 = figure1.cube3x + figure1.cube3y * 10;
			cube4 = figure1.cube4x + figure1.cube4y * 10;

			
			bool allowToMove;			

			//vector containing cubes on the bottom of the figure
			vector<int> cubesOnBottom;

			//checking, which cubes are on the bottom of figure
			if ((cube1 + 10 != cube2) && (cube1 + 10 != cube3) && (cube1 + 10 != cube4)){
				cubesOnBottom.push_back(cube1);
			}
			if ((cube2 + 10 != cube1) && (cube2 + 10 != cube3) && (cube2 + 10 != cube4)){
				cubesOnBottom.push_back(cube2);
			}
			if ((cube3 + 10 != cube1) && (cube3 + 10 != cube2) && (cube3 + 10 != cube4)) {
				cubesOnBottom.push_back(cube3);
			}
			if ((cube4 + 10 != cube1) && (cube4 + 10 != cube2) && (cube4 + 10 != cube3)) {
				cubesOnBottom.push_back(cube4);
			}

			
			allowToMove = true;
			for (int i = 0; i < cubesOnBottom.size(); i++) {
				if (level[cubesOnBottom[i] + 10] != 0) {
					allowToMove = false;
				}
			}

			cout << "Alow to move down: <---------------------" << allowToMove << endl;



			//checking if next position below the figure is empty 			
			//if (level[cube1 + 10] == 0&& level[cube2 + 10] == 0) {
			if (allowToMove) {
				figure1.cube1y++;
				figure1.cube2y++;
				figure1.cube3y++;
				figure1.cube4y++;
					
					
				//specifying a cube position in level array to be changed (filled) in next round
				cube1 = figure1.cube1x + figure1.cube1y * 10;
				cube2 = figure1.cube2x + figure1.cube2y * 10;
				cube3 = figure1.cube3x + figure1.cube3y * 10;
				cube4 = figure1.cube4x + figure1.cube4y * 10;

				//moving cubes down - to the function or method?

				

				//Empting tile of previous position of cube. In case the cube is on the top there's no position cubeX-10, therefore condition if
				if (figure1.cube1y > 0) {
					cube1old = cube1 - 10;					
					level[cube1old] = 0;
				}
				if (figure1.cube2y > 0) {
					cube2old = cube2 - 10;					
					level[cube2old] = 0;
				}
				if (figure1.cube3y > 0) {
					cube3old = cube3 - 10;					
					level[cube3old] = 0;
				}
				if (figure1.cube4y > 0) {
					cube4old = cube4 - 10;					
					level[cube4old] = 0;
				}

				level[cube1] = figure1.cubeColor;
				level[cube2] = figure1.cubeColor;
				level[cube3] = figure1.cubeColor;
				level[cube4] = figure1.cubeColor;
				cout << "Figure went down" << endl;

				
				//update map after figure went down
				if (!map.load("palette3D.png", sf::Vector2u(32, 32), level, 10, 20))
					return -1;

				drawWindow();
			}
			else {
				figure1.cube1y = 0;
				figure1.cube2y = 0; //////////////////////////////// Here has to be 0 and method from Figure class will adjust correct value after choosing figure
				figure1.cube3y = 0;
				figure1.cube4y = 0;
				figureCounter++;
				displayHighscore = true;

				//play sound cubePlaced
				if (soundOn) { cubePlaced.play(); }


				vector<int> levelRow; 
				vector<int> fullRows;
				 
				//removing full line/s in the bottom
				for (int i = 19; i >= 0; i--) {					
					levelRow.clear();
					for (int k = 0 + 10 * i; k < 10 + 10 * i; k++) {													
						levelRow.push_back(level[k]);							
					}
						
					if (find(levelRow.begin(), levelRow.end(), 0) == levelRow.end()) {
						cout << "Vector doesn't include 0, destroying row" << endl;						
						fullRows.push_back(i);
						//Play sound rowDestroyed
						if (soundOn) { rowDestroyed.play(); }

						//Increase score after destroying row and if 1000 gained speed up figures going down
						score += 100;
						texts[5].setString("Score: " + to_string(score));
						if (score % 1000 == 0) {
							movingDownSpeed -= 0.1f;							
							texts[6].setString("Level: " + to_string(int((1.0f - movingDownSpeed + 0.1) * (10))));
							//Play sound speedUp
							if (soundOn) { speedUp.play(); }
						}
						
					}						
				}
				
				//Empting row, which was full
				for (int i = 0; i < fullRows.size(); i++) {					
					for (int j = fullRows[i] * 10; j < fullRows[i] * 10+10; j++) {
						level[j] = 0;
					}
				}

				//Pushing cubes above empty row down
				for (int i = fullRows.size()-1; i>=0; i--) {
					for (int k = fullRows[i] * 10 - 1; k >= 0; k--) {
						if (level[k] > 0) { //////////////////////////////////////here logic was changed from ==1 to > 0
							level[k + 10] = level[k];
							level[k] = 0;
						}
					}
				}				
				
				//update map after destroying full row/rows and pushing cubes down	
				if (!map.load("palette3D.png", sf::Vector2u(32, 32), level, 10, 20))
					return -1;

				drawWindow();

			}					
			
			//reseting time 
			timeDifference = elapsed1.asSeconds();				
		}		

	}
	return 0;
}


//http://www.myfont.de/fonts/alphabet/ttf-fonts-S-12.html - font website

//SF_Automaton_Condensed.ttf