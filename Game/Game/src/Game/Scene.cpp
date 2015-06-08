#include "Scene.h"
#include "../Settings.h"

Scene::Scene()
{
	background = new AVIstream("villagehq.avi");
	tree = new DialogueTree("scene.txt");
	charName = "Girl by docks";
	characterName = new TextObject(charName, 18, vec2(Settings::getWidth()-charName.size()*18-50, Settings::getHeight()/12));

	vector<TextObject*> dialogues = tree->getCurrentDialogueText();
	setupBoxes(dialogues.size());
}

void Scene::setupBoxes(int nrOfTextObjects)
{
	clearBoxes();
	vec2 topRight = vec2(Settings::getWidth() - 35, Settings::getHeight() / 12 - 28);
	vec2 botLeft = vec2(Settings::getWidth() - charName.size() * 18 - 65, Settings::getHeight() / 12 + 10);
	BoxObject* temp = new BoxObject(topRight, botLeft, 4, vec4(0, 0, 1, 0.5));
	sceneBoxes.push_back(temp);

	switch (nrOfTextObjects)
	{
	case 5:
	case 4:
	case 3:
		topRight = vec2(Settings::getWidth() / 8 + 400, 2 * (Settings::getHeight() / 3) - 23 + 30);
		botLeft = vec2(Settings::getWidth() / 8 - 10, 2 * (Settings::getHeight() / 3) + 36);
		temp = new BoxObject(topRight, botLeft, 4, vec4(0, 0, 1, 0.5));
		sceneBoxes.push_back(temp);
	case 2:
		topRight = vec2(Settings::getWidth() / 8 + 400, 2 * (Settings::getHeight() / 3) -  23);
		botLeft = vec2(Settings::getWidth() / 8 - 10, 2 * (Settings::getHeight()/3) + 6);
		temp = new BoxObject(topRight, botLeft, 4, vec4(0, 0, 1, 0.5));
		sceneBoxes.push_back(temp);
	case 1:
		topRight = vec2(650, 125);
		botLeft = vec2(40, 450);
		temp = new BoxObject(topRight, botLeft, 4, vec4(0, 0, 1, 0.5));
		sceneBoxes.push_back(temp);
	default:
		break;
	}
}

Scene::~Scene()
{
	clearBoxes();
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
		setupBoxes(tree->getCurrentDialogueText().size());
	}
	else if (x == 1)
	{
		vector<string>* messages = tree->dialogueOptionChosen(1);
		setupBoxes(tree->getCurrentDialogueText().size());
	}
}

void Scene::clearBoxes()
{
	for (int c = 0; c < sceneBoxes.size(); c++)
	{
		delete sceneBoxes[c];
	}
	sceneBoxes.clear();
}

vector<BoxObject*> Scene::getBoxes()
{
	return sceneBoxes;
}