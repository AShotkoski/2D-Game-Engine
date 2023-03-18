#pragma once
#include <Binds/VertexBuffer.h>
#include <vector>
#include <memory>
#include <Util/Colors.h>
#include <Physics/Vec2.h>

class PointDrawer
{
	struct Vertex
	{
		Vec2 pos;
		Color col;
	};
public:
	PointDrawer() = default;
	bool Empty() const;
	void AddPoint( Vec2 pt, Color c, Graphics& gfx );
	void Draw( Graphics& gfx ) const;
private:
	void _Init(Graphics& gfx );
	void _AddPoint( Vec2 pt,Color c, Graphics& gfx );
private:
	std::vector<struct Vertex> points;
	std::vector<std::unique_ptr<Bindable>> BindPtrs;
	std::unique_ptr<Binds::VertexBuffer> pVertexBuffer;
};

