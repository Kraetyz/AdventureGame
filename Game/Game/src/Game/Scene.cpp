#include "Scene.h"
#include "../Settings.h"
#include "StorylineTest.h"
#include <sstream>

Scene::Scene(string scenePath)
{
	tree = new DialogueTree(scenePath);
	string bgName;
	tree->giveInfoToScene(charName, bgName);
	background = new AVIstream(bgName);
	characterName = new TextObject(charName, 18, vec2(Settings::getWidth()-charName.size()*18-50, Settings::getHeight()/12));

	vector<TextObject*> dialogues = tree->getCurrentDialogueText();

	textBox = new BoxObject(vec2(800, 125), vec2(40, 450), 4, vec4(0, 0, 1, 0.5));

	charBox = new BoxObject(vec2(Settings::getWidth() - 35, Settings::getHeight() / 12 - 28),
		vec2(Settings::getWidth() - charName.size() * 18 - 65, Settings::getHeight() / 12 + 10),
		4, vec4(0, 0, 1, 0.5));

	setupBoxes();
}

void Scene::setupBoxes()
{
	clearBoxes();
	vec2 topRight;
	vec2 botLeft;

	vector<BoxObject*> boxes = tree->getBoxes();
	for (int c = 0; c < boxes.size(); c++)
	{
		sceneBoxes.push_back(boxes[c]);
	}
	sceneBoxes.push_back(textBox);

	sceneBoxes.push_back(charBox);
}

Scene::~Scene()
{
	clearBoxes();
	delete background;
	delete tree;
	delete characterName;
	delete charBox;
	delete textBox;

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

bool Scene::intersectWithSceneBox(int index, vec2 mousePos)
{
	vec4 borders = sceneBoxes[index]->getBorders();
	if (mousePos.x > borders.y &&
		mousePos.x < borders.w &&
		mousePos.y > borders.z &&
		mousePos.y < borders.x)
		return true;
	return false;
}

void Scene::sceneClick(int x, int y)
{
	y = Settings::getHeight() - y;
	vec2 halfScreen = vec2(Settings::getWidth() / 2, Settings::getHeight() / 2);
	vec2 mousePos = vec2(x, y);
	mousePos -= halfScreen;
	mousePos /= halfScreen;
	int nrOfOptions = tree->currentNrOfOptions();
	bool clickedSomething = false;
	int optionClicked = -1;
	for (int c = 0; c < nrOfOptions && !clickedSomething; c++)
	{
		if (intersectWithSceneBox(c, mousePos))
		{
			clickedSomething = true;
			optionClicked = c;
		}
		
	}

	if (optionClicked != -1)
	{
		vector<string> messages = tree->dialogueOptionChosen(optionClicked);
		setupBoxes();
	}
}

void Scene::clearBoxes()
{
	sceneBoxes.clear();
}

vector<BoxObject*> Scene::getBoxes()
{
	return sceneBoxes;
}

void Scene::update(int mx, int my)
{
	my = Settings::getHeight() - my;
	vec2 halfScreen = vec2(Settings::getWidth() / 2, Settings::getHeight() / 2);
	vec2 mousePos = vec2(mx, my);
	mousePos -= halfScreen;
	mousePos /= halfScreen;
	int nrOfOptions = tree->currentNrOfOptions();
	for (int c = 0; c < nrOfOptions; c++)
	{
		if (intersectWithSceneBox(c, mousePos))
		{
			sceneBoxes[c]->setColor(1, 0, 0, 0.5);
		}
		else
		{
			sceneBoxes[c]->setColor(0, 0, 1, 0.5);
		}
	}
}