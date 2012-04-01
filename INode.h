#ifndef __I_NODE__H__
#define __I_NODE__H__

#include "Node.h"
#include "ONode.h"

class INode : public Node
{
	public:
		//INode( Cell* cell );
		INode();
		//INode( Cell* cell, const std::string& alias );
		INode( const std::wstring& alias );

		inline ONode* connected_node();
		inline void connect_node( ONode* node );
		virtual void disconnect_node();

		//virtual bool value();
		virtual operator bool() const;

	private:
		inline void _init();

	private:
		ONode* _connected_node;
};

inline ONode* INode::connected_node()
{
	return _connected_node;
}

inline void INode::connect_node( ONode* node )
{
	_connected_node = node;
}

inline void INode::_init()
{
	_connected_node = NULL;
}

#endif
