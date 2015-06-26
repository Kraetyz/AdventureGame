#ifndef DIALOGUETREE_H
#define DIALOGUETREE_H

#include "../DebugLog.h"
#include "Dialogue.h"

#include <vector>
#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

class DialogueTree
{
private:
	Dialogue* current;
	vector<Dialogue*> allDialogues;
	string charName;
	string bgAviName;
public:
	DialogueTree(string sceneFileName);
	~DialogueTree();

	vector<TextObject*> getCurrentDialogueText();
	vector<BoxObject*> getBoxes();

	vector<string> dialogueOptionChosen(int index);

	int currentNrOfOptions()
	{
		return current->getNrOfOptions();
	}

	void giveInfoToScene(string &name, string &avipath)
	{
		name = charName;
		avipath = bgAviName;
	}
};

#endif