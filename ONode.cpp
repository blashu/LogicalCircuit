#include "ONode.h"

//ONode::ONode( Cell* cell ) : Node( cell )
ONode::ONode()
{
	_init();
}

//ONode::ONode( Cell* cell, const std::string& alias ) : Node( cell, alias )
ONode::ONode( const std::wstring& alias ) : Node( alias )
{
	_init();
}

void ONode::disconnect_node()
{
	_connected_node = NULL;
}

//bool ONode::value()
//{
//	return _value;
//}
ONode::operator bool() const
{
	return _value;
}

ONode& ONode::operator=( bool value )
{
	_value = value;
	return *this;
}
