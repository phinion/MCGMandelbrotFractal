
#include <cmath>
#include <iostream>
#include "MCG_GFX_Lib.h"

void brotSetup(int magnification,int xOffset,int yOffset);
int Mandelbrot(double x, double y, int iterations);
glm::vec3 MandelbrotPixelColour(int iterations);

int main( int argc, char *argv[] )
{

	int repeat = 0;

	do {
		int magnification = 0;
		int xOffset = 0;
		int yOffset = 0;

		

		bool check = false;

		do {

			check = true;

			std::cout << "Hello pleb, i name neekowai, i from romania, u want mandel? how much u wan magnifie?\n";
			std::cout << "chose nombe above 0\n";
			std::cin >> magnification;

			//Validation so that the player does not input something that is not 1 or 2.
			if ((std::cin.fail()) || (magnification < 1)) {

				check = false;
				std::cout << "Invalid input!";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("CLS");

			}

		} while (check == false);

		check = false;

		do {

			check = true;

			std::cout << "chose x offset between 0 and " << magnification - 1 << "\n";
			std::cin >> xOffset;

			//Validation so that the player does not input something that is not 1 or 2.
			if ((std::cin.fail()) || (xOffset < 0) || (xOffset >= magnification)) {

				check = false;
				std::cout << "Invalid input!";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("CLS");

			}

		} while (check == false);

		check = false;

		do {

			check = true;

			std::cout << "chose y offset between 0 and " << magnification - 1 << "\n";
			std::cin >> yOffset;

			//Validation so that the player does not input something that is not 1 or 2.
			if ((std::cin.fail()) || (yOffset < 0) || (yOffset >= magnification)) {

				check = false;
				std::cout << "Invalid input!";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("CLS");

			}

		} while (check == false);

		// Variable for storing window dimensions
		glm::ivec2 windowSize(1000, 1000);

		// Call MCG::Init to initialise and create your window
		// Tell it what size you want the window to be
		if (!MCG::Init(windowSize))
		{
			// We must check if something went wrong
			// (this is very unlikely)
			return -1;
		}

		brotSetup(magnification, xOffset, yOffset);

		// Displays drawing to screen and holds until user closes window
		// You must call this after all your drawing calls
		// Program will exit after this line

		repeat = MCG::ShowAndHold();

		system("CLS");

	} while (repeat == 1);



	// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:

	/*
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		// Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		// Draw the pixel to the screen
		MCG::DrawPixel( pixelPosition, pixelColour );

	}

	return 0;
	*/

}

void brotSetup(int magnification, int xOffset, int yOffset){
// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground( glm::ivec3(0,0,0) );

	// Preparing a position to draw a pixel

	glm::ivec2 pixelPosition;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 255
	glm::ivec3 pixelColour;


	// Draws a single pixel at the specified coordinates in the specified colour!

	// Do any other DrawPixel calls here
	// ...
	
	for (int windowY = 0; windowY < 1000; windowY++) {
		for (int windowX = 0; windowX < 1000; windowX++) {

			double x = ((double)windowX - (500 * magnification) + (xOffset * (1000))) / (250 * magnification);
			double y = ((double)windowY - (500 * magnification) + (yOffset * (1000 ))) / (250 * magnification);

			int numOfIterations = Mandelbrot(x,y,256);

			pixelColour = MandelbrotPixelColour(numOfIterations);

			pixelPosition = glm::vec2(windowX, windowY);

			MCG::DrawPixel(pixelPosition, pixelColour);

		}
	}
}

int Mandelbrot(double x, double y, int iterations ) {

	double x1 = x;
	double y1 = y;
	double x2;
	int counter = 0;

	while (pow(x1, 2.0) + pow(y1, 2.0) <= 4.0 && counter <= iterations) {

		x2 = pow(x1, 2.0) - pow(y1, 2.0) + x;
		y1 = 2.0 * x1 * y1 + y;
		x1 = x2;

		if (x1 == x && y1 == y) {
			return -1; //If the number is in the mandelbrot set, then output -1 so that the coordinates can be coloured black.
		}

		counter += 1;

	}

	
	if (counter == iterations + 1) {
		return -1; //If the counter has maxed out the number of iterations, then the coordinate may still be in the mandelbrot. It returns -1 so it can be coloured black.
	}
	else {
		return counter; //If the coordinate is not in the mandelbrot set, then the counter is returned and used to shade the pixel a specific colour.
	}

}

glm::vec3 MandelbrotPixelColour(int iterations) {

	if (iterations <= 0) {
		return glm::vec3(0, 2, 0);
	}
	else {

		switch (iterations % 16)
		{
		case 0:
			return glm::vec3(66, 30, 15);
			break;
		case 1:
			return glm::vec3(25, 7, 26);
			break;
		case 2:
			return glm::vec3(9, 1, 47);
			break;
		case 3:
			return glm::vec3(4, 4, 73);
			break;
		case 4:
			return glm::vec3(0, 7, 100);
			break;
		case 5:
			return glm::vec3(12, 44, 138);
			break;
		case 6:
			return glm::vec3(24, 82, 177);
			break;
		case 7:
			return glm::vec3(57, 125, 209);
			break;
		case 8:
			return glm::vec3(134, 181, 229);
			break;
		case 9:
			return glm::vec3(211, 236, 248);
			break;
		case 10:
			return glm::vec3(241, 233, 191);
			break;
		case 11:
			return glm::vec3(248, 201, 95);
			break;
		case 12:
			return glm::vec3(255, 170, 0);
			break;
		case 13:
			return glm::vec3(204, 128, 0);
			break;
		case 14:
			return glm::vec3(153, 87, 0);
			break;
		case 15:
			return glm::vec3(106, 52, 3);
			break;
		}

	}

}