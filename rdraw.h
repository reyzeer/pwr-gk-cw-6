/// Laboratorium: Grafika Komputerowa
/// Prowadzący: Dr inż. Marek Woda
/// Cwiczenie 4
/// Zbigniew Czarnecki 209909

#include "common.h"

typedef float point3[3];

class RDraw
{

public:
	
	static float randIntensity();
	static float randShift(float shift);

	static void setRandColor();

	static void square(float x, float y, float size);
	static void colorfulSquare(float x, float y, float size);

	static void Axes(void);

};