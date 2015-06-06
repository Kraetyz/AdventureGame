#include "Scene.h"
#include "../Settings.h"

Scene::Scene()
{
	background = new AVIstream("villagehq.avi");
	tree = new DialogueTree("scene.txt");
	characterName = new TextObject("Girl by docks", 18, vec2(Settings::getWidth()-300, Settings::getHeight()/12));
}

Scene::~Scene()
{
	delete background;
	delete tree;
	delete characterName;

}

AVIstream* Scene::getBackground()
{
	return background;
}

vector<TextObject*> Scene::getText()
{
	vector<TextObject*> ret = tree->getCurrentDialogueText();
	ret.push_back(characterName);
	return ret;
}

void Scene::sceneClick(int x, int y)
{
	int nrOfOptions = tree->currentNrOfOptions();
	//Logic for clicking buttons
	if (x == 0)
	{
		vector<string>* messages = tree->dialogueOptionChosen(0);
	}
	else if (x == 1)
	{
		vector<string>* messages = tree->dialogueOptionChosen(1);
	}
}