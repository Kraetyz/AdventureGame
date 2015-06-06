#ifndef DIALOGUETREE_H
#define DIALOGUETREE_H

#include "../DebugLog.h"
#include "Dialogue.h"

#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

class DialogueTree
{
private:
	Dialogue* current;
	vector<Dialogue*> allDialogues;
public:
	DialogueTree(string sceneFileName);
	~DialogueTree();

	vector<TextObject*> getCurrentDialogueText();

	vector<string>* dialogueOptionChosen(int index);

	int currentNrOfOptions()
	{
		return current->getNrOfOptions();
	}
};

#endif