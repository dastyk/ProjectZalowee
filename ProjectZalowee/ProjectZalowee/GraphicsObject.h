#ifndef _GRAPHICSOBJECT_H_
#define _GRAPHICSOBJECT_H_
#pragma once
//////////////////
//	Includes	//
//////////////////

//////////////////////////
//	My Class Includes	//
//////////////////////////
class GraphicsObject
{
protected:
	GraphicsObject();
	virtual ~GraphicsObject();

	virtual int Update(float dt);
	virtual int Render();
	virtual void GetTranslation();
};

#endif