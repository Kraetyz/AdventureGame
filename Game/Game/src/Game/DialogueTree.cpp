#include "DialogueTree.h"
#include "StorylineTest.h"
#include <sstream>

DialogueTree::DialogueTree(string sceneFileName)
{
	string path = "Scenes/";
	path.append(sceneFileName);
	ifstream file;
	file.open(path.c_str());
	if (file.is_open())
	{
		Dialogue* temp = 0;

		string line = "";
		while (line[0] != ';')
		{
			getline(file, line);
			if (line[0] == '!')
			{
				temp = new Dialogue(file);
				allDialogues.push_back(temp);
			}
			else if (line[0] == '<')
			{
				getline(file, line);
				bgAviName = line;
			}
			else if (line[0] == '>')
			{
				getline(file, line);
				charName = line;
			}
		}
	}
	file.close();
	current = allDialogues[0];
}

DialogueTree::~DialogueTree()
{
	while (allDialogues.size() != 0)
	{
		delete allDialogues[allDialogues.size() - 1];
		allDialogues.pop_back();
	}
}

vector<TextObject*> DialogueTree::getCurrentDialogueText()
{
	vector<Button*> buttons = current->getAllButtons();
	vector<TextObject*> text;
	text.push_back(current->getTextMessage());
	for (int c = 0; c < buttons.size(); c++)
		text.push_back(buttons[c]->getTextObject());
	return text;
}

vector<BoxObject*> DialogueTree::getBoxes()
{
	vector<Button*> buttons = current->getAllButtons();
	vector<BoxObject*> boxes;
	for (int c = 0; c < buttons.size(); c++)
		boxes.push_back(buttons[c]->getBoxObject());
	return boxes;
}

vector<string> DialogueTree::dialogueOptionChosen(int index)
{
	vector<string> ret = current->getMessagesForOption(index);
	//read through messages: switch to new dialogue if prompted

	int i = -1;

	for (int c = 0; c < ret.size(); c++)
	{
		istringstream ss = istringstream(ret[c]);
		string token;
		ss >> token;
		if (token == "GIVE")
		{
			string varName;
			ss >> varName;
			int val;
			ss >> token;
			val = atoi(token.c_str());
			Storyline::increaseVariable(varName, val);
		}
		else if (token == "GOTO")
		{
			ss >> token;
			i = atoi(token.c_str());
		}
	}

	if (i != -1)
	{
		current = allDialogues[i];
		current->setupCurrentText();
	}

	return ret;
}