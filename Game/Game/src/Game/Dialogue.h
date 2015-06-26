#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "../DebugLog.h"
#include "../Engine/TextObject.h"
#include "Button.h"
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Dialogue
{
private:
	TextObject* bigText; //The big text box

	vector<vector<string>> messagesForEachOption; //The messages held by each dialogue option
	vector<TextObject*> text; //Potential options for the dialogue

	vector<Button*> currentButtons;
	vector<vector<string>> currentMessagesForEachOption;

	void createTextObject(ifstream &file);
	void addMessagesForOption(ifstream &file);
	vec2 getScreenPosForText(bool isCurrent = false);

	void clearCurrentButtons();

	bool meetsRequirements(vector<string> messages);
public:
	Dialogue(ifstream &file);
	~Dialogue();

	int getNrOfOptions()
	{
		return currentButtons.size();
	}
	vector<string> getMessagesForOption(int optionIndex);
	vector<Button*> getAllButtons();
	TextObject* getTextMessage(){ return bigText; }

	void setupCurrentText();
};

#endif