#include "Button.h"

Button::Button(string text, int fontSize, vec2 &windowPos, vec4 &boxColor, int boxBorderSize)
{
	myText = new TextObject(text, fontSize, windowPos);

	int botLimit = 0, rightLimit = 0;
	myText->getTextLimits(rightLimit, botLimit);
	vec2 topRight = vec2(rightLimit + boxBorderSize + 4, windowPos.y - fontSize - boxBorderSize - 4);
	vec2 botLeft = vec2(windowPos.x - boxBorderSize - 4, (Settings::getHeight()-botLimit) + boxBorderSize + 4);
	myBox = new BoxObject(topRight, botLeft, boxBorderSize, boxColor);
}

Button::~Button()
{
	delete myText;
	delete myBox;
}