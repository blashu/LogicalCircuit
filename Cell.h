#ifndef __CELL__H__
#define __CELL__H__

#include "Bus.h"
#include "CellProcessStrategy.h"

// логический элемент
class Cell
{
	public:
		Cell( CellProcessStrategy* ps );
		virtual ~Cell();

		inline const ibus_t& ibus() const;
		inline const obus_t& obus() const;

		// Функция, производящая обсчет ячейки.
		virtual void process();
		void stop_process();

		// Получить количество входящих узлов.
		size_t in_count() const;
		// Получить минимальное количество входящих узлов.
		size_t in_min_size() const;
		// Получить максимальное количество входящих узлов.
		size_t in_max_size() const;
		// Получить значение на входящем узле.
		// id - номер узла, значение которого требуется получить.
		bool in_node( size_t id );

		// Подсоеденить узел входа к внешнему узлу выхода.
		void connect_to_in( Cell& targetCell, size_t targetOutId, size_t inId );
		// Подсоеденить узел входа к внешнему узлу выхода.
		void connect_to_in( ONode* oNode, size_t inId );
		// Отсоеденить узел входа от внешнего узла.
		void disconnect_from_in( size_t inId );

		// Получить количество исходящих узлов.
		size_t out_count() const;
		// Получить минимальное количество исходящих узлов.
		size_t out_min_size() const;
		// Получить максимальное количество исходящих узлов.
		size_t out_max_size() const;
		// Получить значение на исходящем узле.
		// id - номер узла, значение которого требуется получить.
		bool out_node( size_t id );

		// Подсоеденить узел выхода к внешнему узлу входа.
		void connect_to_out( Cell& targetCell, size_t targetInId, size_t outId );
		// Подсоеденить узел выхода к внешнему узлу входа.
		void connect_to_out( INode* iNode, size_t outId );
		// Отсоеденить узел выхода от внешнего узла.
		void disconnect_from_out( size_t outId );

		void resize_node_count( size_t newInCount, size_t newOutCount );

		inline const CellProcessStrategy* process_strategy() const;
		inline bool in_is_min_equal_max() const;
		inline bool out_is_min_equal_max() const;

		inline const std::wstring title();
		inline void set_title( const std::wstring& title );

	protected:
		ibus_t iBus;
		obus_t oBus;
		std::wstring _title;

	private:
		CellProcessStrategy* processStrategy;
};

inline const ibus_t& Cell::ibus() const
{
	return iBus;
}

inline const obus_t& Cell::obus() const
{
	return oBus;
}

const CellProcessStrategy* Cell::process_strategy() const
{
	return processStrategy;
}

inline bool Cell::in_is_min_equal_max() const
{
	return in_min_size() == in_max_size();
}

inline bool Cell::out_is_min_equal_max() const
{
	return out_min_size() == out_max_size();
}

inline const std::wstring Cell::title()
{
	return _title;
}

inline void Cell::set_title( const std::wstring& title )
{
	_title = title;
}

#endif
