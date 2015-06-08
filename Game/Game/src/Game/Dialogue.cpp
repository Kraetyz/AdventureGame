#include "Dialogue.h"

Dialogue::~Dialogue()
{
	while (text.size() != 0)
	{
		delete text[text.size() - 1];
		text.pop_back();
	}
}

Dialogue::Dialogue(ifstream &file)
{
	string line = "";
	while (line[0] != '!')
	{
		getline(file, line);
		switch (line[0])
		{
		case '%':
			addMessagesForOption(file);
			break;
		case '!':
			break;
		case '.':
			createTextObject(file);
			break;
		default:
			break;
		}
	}
}

void Dialogue::createTextObject(ifstream &file)
{
	string textToAdd;
	string line = "";
	while (line[0] != '#')
	{
		getline(file, line);
		if (line[0] != '#')
		{
			textToAdd += line += '\n';
		}
	}
	vec2 screenPos = getScreenPosForText();
	TextObject* temp = new TextObject(textToAdd, 16, screenPos);
	text.push_back(temp);
}

void Dialogue::addMessagesForOption(ifstream &file)
{
	string line = "";
	while (line[0] != '#')
	{
		getline(file, line);
		if (line[0] != '#')
		{
			int index = getNrOfOptions()-1;
			messagesForEachOption[index].push_back(line);
		}
	}
}

vec2 Dialogue::getScreenPosForText()
{
	if (text.size() == 0)
		return vec2(50, 150);
	else
		return vec2(Settings::getWidth()/8, (2*Settings::getHeight())/3 + 30*(text.size()-1));
}

vector<string>* Dialogue::getMessagesForOption(int optionIndex)
{
	return &messagesForEachOption[optionIndex];
}

vector<TextObject*> Dialogue::getAllText()
{
	return text;
}