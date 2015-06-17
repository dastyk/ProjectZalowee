#include "NullState.h"


NullState::NullState()
{
}


NullState::~NullState()
{
}

int NullState::Init()
{
	return 0;
}

int NullState::HandleInput()
{
	return 0;
}

int NullState::Update(float dt)
{
	return 0;
}

int NullState::Render()
{
	return 0;
}
