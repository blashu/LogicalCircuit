#include "Node.h"

//Node::Node( Cell* cell )
Node::Node()
{
	_init( L"" );
}

//Node::Node( Cell* cell, const std::string& alias )
Node::Node( const std::wstring& alias )
{
	_init( alias );
}
