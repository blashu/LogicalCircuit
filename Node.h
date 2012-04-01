#ifndef __NODE__H__
#define __NODE__H__

//class Cell;

#include <string>
#include <stdexcept>

// узел входа/выхода
class Node
{
	public:
		// cell - ячейка, которой пренадлежит создаваемый узел.
		//
		// Предполагается, что память под cell выделяется извне,
		//    и не очищается на протяжении всего существования экземпляра
		//	  текущего класса.
		// Node( Cell* cell );
		Node();

		// cell - ячейка, которой пренадлежит создаваемый узел;
		// alias - псевдоним узла.
		//
		// Предполагается, что память под cell выделяется извне,
		//    и не очищается на протяжении всего существования экземпляра
		//	  текущего класса.
		// Node( Cell* cell, const std::string& alias );
		Node( const std::wstring& alias );


		// Получить ячейку, содержащую данный вход/выход.
		//inline Cell* get_cell();

		// Псевдоним узла.
		inline const std::wstring& get_alias();

		// Получить значение, которое содержит узел.
		//virtual bool value() = 0;
		virtual operator bool() const = 0;

		virtual void disconnect_node() = 0;

	private:
		//inline void _init( Cell* _cell, const std::wstring& _alias );
		inline void _init( const std::wstring& _alias );

	private:
		//Cell* _cell;
		std::wstring _alias;

};

//inline Cell* Node::get_cell()
//{
//	return _cell;
//}

inline const std::wstring& Node::get_alias()
{
	return _alias;
}

//inline void Node::_init( Cell* cell, const std::string& alias )
inline void Node::_init( const std::wstring& alias )
{
	//_cell = cell;
	_alias = alias;
}

#endif
