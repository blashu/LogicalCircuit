#ifndef __BUS__H__
#define __BUS__H__

#include "INode.h"
#include "ONode.h"

#include <vector>

typedef enum _NodeTypes
{
	NT_INPUT ,
	NT_OUTPUT
} NodeTypes;

enum
{
	MAX_NODE_COUNT = 0x20
};

// "шина" входов-выходов
template <typename T>
class Bus
{
	public:
		// Используя такой подход мы комбинируем плюсы от вектора
		//    и от использования динамической памяти.
		//    Вектор позволяет обращаться по индексу, а указатель - делать ссылки в других
		//    узлах.
		typedef std::vector<T*> value_type;
//		typedef value_type::const_iterator const_iterator;

	public:
		template <typename N>
		static void disconnect( N* node );

	public:
		Bus(){}
		//Bus( Cell* cell, size_t minSize, size_t maxSize );
		Bus( size_t minSize, size_t maxSize );
		~Bus();

		inline size_t size() const;
		inline size_t min_size() const;
		inline size_t max_size() const;
		inline T& operator[] ( size_t i ) const;

		// Подсоеденить узел.
		template <typename N>
		bool connect( N node, size_t outId );

		void disconnect_all();

		// Изменить количество узлов.
		bool resize( size_t size );

	protected:
		size_t minSize;
		size_t maxSize;
		value_type nodes;
		//Cell* cell;
};

typedef Bus<INode> ibus_t;
typedef Bus<ONode> obus_t;

template <typename T>
template <typename N>
void Bus<T>::disconnect( N* node )
{
	if( NULL != node->connected_node() )
	{
		node->connected_node()->disconnect_node();
		node->disconnect_node();
	}
}

// TODO добавить проверку, что размер не может быть больше MAX_NODE_COUNT
template <typename T>
//Bus<T>::Bus( Cell* cell, size_t minSize, size_t maxSize )
Bus<T>::Bus( size_t minSize, size_t maxSize )
{
	this->minSize = minSize;
	this->maxSize = maxSize;
	//this->cell = cell;

	for( size_t i = 0; i < minSize; ++i )
	{
		//nodes.push_back( new T( cell ) );
		nodes.push_back( new T() );
	}
}

template <typename T>
Bus<T>::~Bus()
{
	disconnect_all();
}

template <typename T>
inline size_t Bus<T>::size() const
{
	return nodes.size();
}

template <typename T>
inline size_t Bus<T>::min_size() const
{
	return minSize;
}

template <typename T>
inline size_t Bus<T>::max_size() const
{
	return maxSize;
}

template <typename T>
inline T& Bus<T>::operator[] ( size_t i ) const
{
	return *( nodes.at( i ) );
}

template <typename T>
template <typename N>
bool Bus<T>::connect( N node, size_t id )
{
	if( NULL == node )
	{
		return false;
	}
	disconnect( nodes[ id ] );
	disconnect( node );
	nodes[ id ]->connect_node( node );
	node->connect_node( nodes[ id ] );
	return true;
}

template <typename T>
void Bus<T>::disconnect_all()
{
	for( auto it = nodes.begin(), end = nodes.end(); it != end; ++it )
	{
		disconnect( *it );
	}
}

template <typename T>
bool Bus<T>::resize( size_t size )
{
	size_t oldSize = nodes.size();
	if( ( ( size < minSize ) &&
				( size > maxSize ) ) ||
			( size == nodes.size() ) )
	{
		return false;
	}

	if( size < nodes.size() )
	{
		for( auto i = nodes.size(); i --> size;) // hello from c# 4.0 new specification
		{
			disconnect( nodes[ i ] );
			delete nodes[ i ];
		}
	}
	nodes.resize( size );
	for( auto i = oldSize, end = nodes.size(); i < end; ++i )
	{
		nodes[ i ] = new T();
	}
	return true;
}
#endif
