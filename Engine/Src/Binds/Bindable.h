#pragma once

#include "GraphicsResource.h"
#include "Graphics.h"
#include <memory>

class Bindable : public GraphicsResource
{
public:
	virtual void Bind( Graphics& gfx ) = 0;
	virtual ~Bindable() = default;
};

