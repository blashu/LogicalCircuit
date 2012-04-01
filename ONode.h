#ifndef __O_NODE__H__
#define __O_NODE__H__

#include "Node.h"

class INode;

class ONode : public Node
{
	public:
//		ONode( Cell* cell );
        ONode();
//		ONode( Cell* cell, const std::string& alias );
        ONode( const std::wstring& alias );

		inline INode* connected_node();
		inline void connect_node( INode* node );
		virtual void disconnect_node();

		//virtual bool value();
		//inline void set_value( bool value );
		virtual operator bool() const;
		ONode& operator=( bool value );

	private:
		inline void _init();

	private:
		INode* _connected_node;
		bool _value;
};

inline INode* ONode::connected_node()
{
	return _connected_node;
}

inline void ONode::connect_node( INode* node )
{
	_connected_node = node;
}

inline void ONode::_init()
{
	_connected_node = NULL;
	_value = false;
}

#endif
