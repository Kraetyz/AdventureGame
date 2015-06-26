#include "Dialogue.h"
#include "StorylineTest.h"
#include <sstream>

Dialogue::~Dialogue()
{
	delete bigText;
	for (int c = 0; c < text.size(); c++)
	{
		delete text[c];
	}
	text.clear();

	clearCurrentButtons();
}

void Dialogue::clearCurrentButtons()
{
	for (int c = 0; c < currentButtons.size(); c++)
	{
		delete currentButtons[c];
	}
	currentButtons.clear();

	for (int c = 0; c < currentMessagesForEachOption.size(); c++)
	{
		currentMessagesForEachOption[c].clear();
	}
	currentMessagesForEachOption.clear();
}

Dialogue::Dialogue(ifstream &file)
{
	bigText = 0;
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
	setupCurrentText();
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
	if (bigText == 0)
		bigText = temp;
	else
		text.push_back(temp);
}

void Dialogue::addMessagesForOption(ifstream &file)
{
	messagesForEachOption.push_back(vector<string>());
	string line = "";
	while (line[0] != '#')
	{
		getline(file, line);
		if (line[0] != '#')
		{
			messagesForEachOption[messagesForEachOption.size()-1].push_back(line);
		}
	}
}

vec2 Dialogue::getScreenPosForText(bool isCurrent)
{
	if (isCurrent)
	{
		return vec2(Settings::getWidth() / 8, (2 * Settings::getHeight()) / 3 + 30 * (currentButtons.size() - 1));
	}
	else
	{
		if (bigText == 0)
			return vec2(50, 150);
		else
			return vec2(Settings::getWidth() / 8, (2 * Settings::getHeight()) / 3 + 30 * (text.size() - 1));
	}
}

vector<string> Dialogue::getMessagesForOption(int optionIndex)
{
	return currentMessagesForEachOption[optionIndex];
}

vector<Button*> Dialogue::getAllButtons()
{
	return currentButtons;
}

void Dialogue::setupCurrentText()
{
	clearCurrentButtons();
	string str; vec2 screenPos; Button* tempButton = 0;
	for (int c = 0; c < text.size(); c++)
	{
		if (meetsRequirements(messagesForEachOption[c]))
		{
			str = text[c]->getText();
			screenPos = getScreenPosForText(true);
			tempButton = new Button(str, 16, screenPos, vec4(1, 0, 0, 0.5), 4);

			currentButtons.push_back(tempButton);
			currentMessagesForEachOption.push_back(vector<string>(messagesForEachOption[c]));
		}
	}
}

bool Dialogue::meetsRequirements(vector<string> messages)
{
	bool meets = true;
	for (int c = 0; c < messages.size(); c++)
	{
		istringstream ss = istringstream(messages[c]);
		string token;
		ss >> token;
		if (token == "NEEDS")
		{
			string varName;
			ss >> varName;
			int val = 0;
			ss >> token;
			val = atoi(token.c_str());
			ss >> token;
			if (token == "MORE")
			{
				if (Storyline::getVariable(varName) >= val)
					meets = true;
				else
					return false;
			}
			else if (token == "LESS")
			{
				if (Storyline::getVariable(varName) <= val)
					meets = true;
				else
					return false;
			}
		}
	}
	return meets;
}