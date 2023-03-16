#pragma once
#include <Binds/VertexBuffer.h>
#include <vector>
#include <memory>

class Point;
class Color;

class PointDrawer
{
public:
	PointDrawer() = default;
	bool Empty() const;
	void AddPoint( Point pt, Graphics& gfx );
	void Draw( Graphics& gfx ) const;
private:
	void _Init(Graphics& gfx );
	void _AddPoint( Point pt, Graphics& gfx );
private:
	std::vector<Point> points;
	std::vector<std::unique_ptr<Bindable>> BindPtrs;
	std::unique_ptr<Binds::VertexBuffer> pVertexBuffer;
};

