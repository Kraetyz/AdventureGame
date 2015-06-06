#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "../DebugLog.h"
#include "../Engine/TextObject.h"
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Dialogue
{
private:
	vector<string> messagesForEachOption[4];
	vector<TextObject*> text; //0 = Talky text box. 1-4 = Options

	void createTextObject(ifstream &file);
	void addMessagesForOption(ifstream &file);

	vec2 getScreenPosForText();
public:
	Dialogue(ifstream &file);
	~Dialogue();

	int getNrOfOptions()
	{
		return text.size() - 1;
	}
	vector<string>* getMessagesForOption(int optionIndex);
	vector<TextObject*> getAllText();
};

#endif