#include "BoxObject.h"

BoxObject::BoxObject(vec2 tR, vec2 bL, int thickness, vec4 &color)
{
	this->color = color;
	vec2 topRight = vec2(tR.x, Settings::getHeight() - tR.y);
	vec2 botRight = vec2(tR.x, Settings::getHeight() - bL.y);
	vec2 topLeft = vec2(bL.x, Settings::getHeight() - tR.y);
	vec2 botLeft = vec2(bL.x, Settings::getHeight() - bL.y);

	vec2 halfScreen = vec2(Settings::getWidth() / 2, Settings::getHeight() / 2);

	borders = vec4(topRight.y - thickness, topLeft.x + thickness, botLeft.y + thickness, topRight.x - thickness);
	borders.x -= halfScreen.y;
	borders.x /= halfScreen.y;

	borders.y -= halfScreen.x;
	borders.y /= halfScreen.x;

	borders.z -= halfScreen.y;
	borders.z /= halfScreen.y;

	borders.w -= halfScreen.x;
	borders.w /= halfScreen.x;


	topRight -= halfScreen;
	topRight /= halfScreen;

	botRight -= halfScreen;
	botRight /= halfScreen;

	topLeft -= halfScreen;
	topLeft /= halfScreen;

	botLeft -= halfScreen;
	botLeft /= halfScreen;

	float temp[] =
	{
		topRight.x, topRight.y, -0.5f,
		botRight.x, botRight.y, -0.5f,
		topLeft.x, topLeft.y, -0.5f,
		botLeft.x, botLeft.y, -0.5f
	};

	for (int c = 0; c < 12; c++)
		quad[c] = temp[c];
}

BoxObject::~BoxObject()
{
}

void BoxObject::getBoxAttributes(vec4 &color, vec4 &borders, float* &quad)
{
	color = this->color; borders = this->borders;
	for (int c = 0; c < 12; c++)
		quad[c] = this->quad[c];
}