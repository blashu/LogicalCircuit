#ifndef CELLPROCESSSTRATEGY_H
#define CELLPROCESSSTRATEGY_H

#include "Bus.h"
#include <string>

class CellProcessStrategy
{
	public:
		CellProcessStrategy();

		// Поскольку стратегия может содержать поля, которые могут изменяться
		// в зависимости от расчетов и типа ячейки, то был введен этот интерфейс
		// (по мотивам паттерна Prototype).
		virtual CellProcessStrategy* clone() const = 0;

		virtual size_t inodes_min() const = 0;
		virtual size_t inodes_max() const = 0;
		virtual size_t onodes_min() const = 0;
		virtual size_t onodes_max() const = 0;

		void process( const ibus_t& in, const obus_t& out );

		void stop_process();

		virtual const std::wstring& cell_type_name() = 0;

		// Проверяет, корректно ли новое количество входов/выходов.
		//
		// inCount - новое количество входов;
		// outCount - новое количество выходов.
		// Возвращяемое значение: поясняющее сообщение об ошибке.
		//   Если вернет noErrorMessage, то ошибки нет, иначе - есть.
		virtual const std::wstring& is_valid_node_count( size_t inCount, size_t outCount ) const;

		// Корректировка количества входов/выходов.
		//
		// updatingType - тип узла, который был обновлен;
		// inCount - количество входов;
		// outCount - количество выходов.
		// Возвращяемое значение: поясняющее сообщение об ошибке.
		//   Если вернет noErrorMessage, то ошибки нет, иначе - есть.
		virtual const std::wstring& correct_node_count( NodeTypes updatingType,
																										size_t &inCount, size_t &outCount ) const;

		// Корректировка количества входов/выходов.
		//
		// oldInCount - старое количество входов;
		// newInCount - новое количество входов;
		// oldOutCount - старое количество выходов.
		// newOutCount - новое количество выходов.
		// Возвращяемое значение: поясняющее сообщение об ошибке.
		//   Если вернет noErrorMessage, то ошибки нет, иначе - есть.
		const std::wstring& correct_node_count( size_t oldInCount, size_t &newInCount,
                                                size_t oldOutCount, size_t &newOutCount ) const;

	public:
		static const std::wstring noErrorMessage;

	protected:
		// Производится первая инерация расчета элемента после остановки
		//   процесса расчета или нет?
		inline bool has_just_started();

		// Произвести обсчет элемента.
		virtual void do_process( const ibus_t& in, const obus_t& out ) = 0;

		// Функция вызывается, когда процесс расчета остановлен.
		virtual void do_stop_process(){}

	private:
		enum ErrorMessageTypes
		{
			EMT_INCOUNT_MORE_THAN_MAX = 0x00 ,
			EMT_OUTCOUNT_MORE_THAN_MAX ,

			EMT_EMT_NUMBER
		};

		static const std::wstring errorMessages[ EMT_EMT_NUMBER ];

	private:
		bool is_process_in_progress;
};

inline bool CellProcessStrategy::has_just_started()
{
	return !is_process_in_progress;
}

#endif // CELLPROCESSSTRATEGY_H
