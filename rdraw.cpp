/// Laboratorium: Grafika Komputerowa
/// Prowadzący: Dr inż. Marek Woda
/// Cwiczenie 4
/// Zbigniew Czarnecki 209909

#include "common.h"

float RDraw::randIntensity()
{
	return (float)(rand() % 101) / 100;
}

/// \param shift >= 0.5
/// \return
float RDraw::randShift(float shift)
{
	return (float)(rand() % (int)(shift * 2)) - shift;
}

void RDraw::setRandColor()
{
	glColor3f(randIntensity(), randIntensity(), randIntensity());
}

void RDraw::square(float x, float y, float size)
{
	glRectf(x, y, x + size, y + size);
}

void RDraw::colorfulSquare(float x, float y, float size)
{

	glBegin(GL_QUADS);

	setRandColor();
	glVertex2f(x, y);
	setRandColor();
	glVertex2f(x, y + size);
	setRandColor();
	glVertex2f(x + size, y + size);
	setRandColor();
	glVertex2f(x + size, y);

	glEnd();

}

void RDraw::Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// początek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0, 5.0, 0.0 };
	// początek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0, 5.0 };
	//  początek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x

	glVertex3fv(x_min);
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);

	glEnd();

}
