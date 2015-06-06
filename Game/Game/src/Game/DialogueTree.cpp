#include "DialogueTree.h"
#include <fstream>
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
		}
	}

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
	return current->getAllText();
}

vector<string>* DialogueTree::dialogueOptionChosen(int index)
{
	vector<string>* ret = current->getMessagesForOption(index);
	//read through messages: switch to new dialogue if prompted
	if (ret->size() > 0)
	{
		istringstream ss = istringstream((*ret)[0]);
		string command;
		ss >> command;
		if (command == "GOTO")
		{
			string index;
			ss >> index;
			int i = atoi(index.c_str());
			current = allDialogues[i];
		}
	}
	return ret;
}