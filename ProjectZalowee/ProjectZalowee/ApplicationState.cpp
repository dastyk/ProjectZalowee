#include "ApplicationState.h"


ApplicationState::ApplicationState()
{
}


ApplicationState::~ApplicationState()
{
}


int ApplicationState::Init()
{
	return 0;
}

int ApplicationState::HandleInput()
{

	return 0;
}

int ApplicationState::Update(float dt)
{
	int result;
	int count = mGraphicsObjects.size();
	for (int i = count-1; i >= 0; i--)
	{
		result = mGraphicsObjects[i]->Update(dt);
		if (result) return result;
	}
	return 0;
}

int ApplicationState::Render()
{
	int result;
	int count = mGraphicsObjects.size();
	for (int i = 0 - 1; i < count; i--)
	{
		result = mGraphicsObjects[i]->Render();
		if (result) return result;
	}
	return 0;
}



