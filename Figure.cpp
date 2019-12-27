#include "Figure.h"

Figure Figure::makeRandomFigure(Figure figure, int figureNumber)
{
	{

		//set starting figure's cubes coordiantes
		if (figureNumber == 1) {
			figure.cube1x = 4;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 4;
			figure.cube3y = 2;
			figure.cube4x = 4;
			figure.cube4y = 3;
			figure.cubeColor = 1;
		}
		else if (figureNumber == 2) {
			figure.cube1x = 3;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 0;
			figure.cube3x = 5;
			figure.cube3y = 0;
			figure.cube4x = 6;
			figure.cube4y = 0;
			figure.cubeColor = 1;
		}
		else if (figureNumber == 3) {
			figure.cube1x = 4;
			figure.cube1y = 0;
			figure.cube2x = 5;
			figure.cube2y = 0;
			figure.cube3x = 4;
			figure.cube3y = 1;
			figure.cube4x = 5;
			figure.cube4y = 1;
			figure.cubeColor = 4;
		}
		else if (figureNumber == 4) {
			figure.cube1x = 3;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 0;
			figure.cube3x = 5;
			figure.cube3y = 0;
			figure.cube4x = 3;
			figure.cube4y = 1;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 5) {
			figure.cube1x = 4;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 4;
			figure.cube3y = 2;
			figure.cube4x = 3;
			figure.cube4y = 0;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 6) {
			figure.cube1x = 5;
			figure.cube1y = 1;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 3;
			figure.cube3y = 1;
			figure.cube4x = 5;
			figure.cube4y = 0;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 7) {
			figure.cube1x = 3;
			figure.cube1y = 2;
			figure.cube2x = 3;
			figure.cube2y = 1;
			figure.cube3x = 3;
			figure.cube3y = 0;
			figure.cube4x = 4;
			figure.cube4y = 2;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 8) {
			figure.cube1x = 3;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 0;
			figure.cube3x = 5;
			figure.cube3y = 0;
			figure.cube4x = 5;
			figure.cube4y = 1;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 9) {
			figure.cube1x = 4;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 4;
			figure.cube3y = 2;
			figure.cube4x = 3;
			figure.cube4y = 2;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 10) {
			figure.cube1x = 5;
			figure.cube1y = 1;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 3;
			figure.cube3y = 1;
			figure.cube4x = 3;
			figure.cube4y = 0;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 11) {
			figure.cube1x = 4;
			figure.cube1y = 2;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 4;
			figure.cube3y = 0;
			figure.cube4x = 5;
			figure.cube4y = 0;
			figure.cubeColor = 3;
		}
		else if (figureNumber == 12) {
			figure.cube1x = 3;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 0;
			figure.cube3x = 5;
			figure.cube3y = 0;
			figure.cube4x = 4;
			figure.cube4y = 1;
			figure.cubeColor = 2;
		}
		else if (figureNumber == 13) {
			figure.cube1x = 5;
			figure.cube1y = 0;
			figure.cube2x = 5;
			figure.cube2y = 1;
			figure.cube3x = 5;
			figure.cube3y = 2;
			figure.cube4x = 4;
			figure.cube4y = 1;
			figure.cubeColor = 2;
		}
		else if (figureNumber == 14) {
			figure.cube1x = 5;
			figure.cube1y = 1;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 3;
			figure.cube3y = 1;
			figure.cube4x = 4;
			figure.cube4y = 0;
			figure.cubeColor = 2;
		}
		else if (figureNumber == 15) {
			figure.cube1x = 4;
			figure.cube1y = 2;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 4;
			figure.cube3y = 0;
			figure.cube4x = 5;
			figure.cube4y = 1;
			figure.cubeColor = 2;
		}
		else if (figureNumber == 16) {
			figure.cube1x = 4;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 5;
			figure.cube3y = 1;
			figure.cube4x = 5;
			figure.cube4y = 2;
			figure.cubeColor = 5;
		}
		else if (figureNumber == 17) {
			figure.cube1x = 3;
			figure.cube1y = 1;
			figure.cube2x = 4;
			figure.cube2y = 1;
			figure.cube3x = 4;
			figure.cube3y = 0;
			figure.cube4x = 5;
			figure.cube4y = 0;
			figure.cubeColor = 5;
		}
		else if (figureNumber == 18) {
			figure.cube1x = 5;
			figure.cube1y = 0;
			figure.cube2x = 5;
			figure.cube2y = 1;
			figure.cube3x = 4;
			figure.cube3y = 1;
			figure.cube4x = 4;
			figure.cube4y = 2;
			figure.cubeColor = 5;
		}
		else if (figureNumber == 19) {
			figure.cube1x = 3;
			figure.cube1y = 0;
			figure.cube2x = 4;
			figure.cube2y = 0;
			figure.cube3x = 4;
			figure.cube3y = 1;
			figure.cube4x = 5;
			figure.cube4y = 1;
			figure.cubeColor = 5;
		}



		return figure;
	}
}

int Figure::setTurnedFigure(int figureNumber)
{
	if (figureNumber == 1) {
		return 2;
	}
	else if (figureNumber == 2) {
		return 1;
	}
	else if (figureNumber == 4) {
		return 5;
	}
	else if (figureNumber == 5) {
		return 6;
	}
	else if (figureNumber == 6) {
		return 7;
	}
	else if (figureNumber == 7) {
		return 4;
	}
	else if (figureNumber == 8) {
		return 9;
	}
	else if (figureNumber == 9) {
		return 10;
	}
	else if (figureNumber == 10) {
		return 11;
	}
	else if (figureNumber == 11) {
		return 8;
	}
	else if (figureNumber == 12) {
		return 13;
	}
	else if (figureNumber == 13) {
		return 14;
	}
	else if (figureNumber == 14) {
		return 15;
	}
	else if (figureNumber == 15) {
		return 12;
	}
	else if (figureNumber == 16) {
		return 17;
	}
	else if (figureNumber == 17) {
		return 16;
	}
	else if (figureNumber == 18) {
		return 19;
	}
	else if (figureNumber == 19) {
		return 18;
	}
	else {
		return figureNumber;
	}

}

int Figure::assignRandomFigure(int figureNumber)
{
	if (figureNumber == 1) {
		return 2;
	}
	else if (figureNumber == 2) {
		return 3;
	}
	else if (figureNumber == 3) {
		return 4;
	}
	else if (figureNumber == 4) {
		return 8;
	}
	else if (figureNumber == 5) {
		return 12;
	}
	else if (figureNumber == 6) {
		return 16;
	}
	else if (figureNumber == 7) {
		return 18;
	}
}
