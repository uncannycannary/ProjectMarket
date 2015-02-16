#ifndef SCENE_H
#define SCENE_H

#include "Keyboard.h"
#include "GLMouse.h"
#include "Sound.h"
#include "Graphics.h"

class Scene
{
protected:
	Keyboard& keyboard;
	GLMouse& mouse;
	Graphics& gfx;
	Sound& snd;
	unsigned screenX;
	unsigned screenY;
public:
	Scene(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx)
		:
	keyboard(keyboard),
	mouse(mouse),
	gfx(gfx),
	snd(snd)
	{
		screenX = 0;
		screenY = 0;
	}
	~Scene() {}

	virtual void Init() = 0;
	void SetWindowSize(unsigned x, unsigned y)
	{
		screenX = x;
		screenY = y;
	}
	virtual bool Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif