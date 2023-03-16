#pragma once
#include <Binds/Bindable.h>
#include <vector>
#include <memory>

class Graphics;

class Drawable
{
public:
	virtual void Draw( Graphics& gfx ) const = 0;
protected:
	Drawable( Graphics& gfx ) {};
	void AddBind( std::unique_ptr<Bindable> bind )
	{
		BindPtrs.push_back( std::move(bind) );
	}
	virtual void BindAll( Graphics& gfx ) const
	{		
		for ( auto& b : BindPtrs )
		{
			b->Bind( gfx );
		}	
	}
private:
	std::vector<std::unique_ptr<Bindable>> BindPtrs;
};