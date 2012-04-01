#include "INode.h"

//INode::INode( Cell* cell ): Node( cell )
INode::INode()
{
	_init();
}

//INode::INode( Cell* cell, const std::string& alias ) : Node( cell, alias )
INode::INode( const std::wstring& alias ) : Node( alias )
{
	_init();
}

//bool INode::value()
//{
//	return ( NULL != _connected_node ) && ( _connected_node->value() );
//}
INode::operator bool() const
{
	return ( NULL != _connected_node ) && ( *_connected_node );
}

void INode::disconnect_node()
{
	_connected_node = NULL;
}
