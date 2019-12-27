#pragma once



class Figure {
public:
	int cube1x;
	int cube1y;

	int cube2x;
	int cube2y;

	int cube3x;
	int cube3y;

	int cube4x;
	int cube4y;

	int cubeColor = 1;


	static Figure makeRandomFigure(Figure figure, int figureNumber);

	static int setTurnedFigure(int figureNumber);

	static int assignRandomFigure(int figureNumber);


};