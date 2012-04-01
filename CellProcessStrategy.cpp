#include "CellProcessStrategy.h"

const std::wstring CellProcessStrategy::noErrorMessage = L"";

const std::wstring CellProcessStrategy::errorMessages[ EMT_EMT_NUMBER ] =
{
	L"Количество входящих узлов больше максимаольно возможного." ,
	L"Количество выходящих узлов больше максимаольно возможного."
};

CellProcessStrategy::CellProcessStrategy()
{
	is_process_in_progress = false;
}

void CellProcessStrategy::process( const ibus_t& in, const obus_t& out )
{
	do_process( in, out );
	is_process_in_progress = true;
}

void CellProcessStrategy::stop_process()
{
	is_process_in_progress = false;
	do_stop_process();
}

const std::wstring& CellProcessStrategy::is_valid_node_count( size_t inCount, size_t outCount ) const
{
	if( inCount > inodes_max() )
	{
		return errorMessages[ EMT_INCOUNT_MORE_THAN_MAX ];
	}
	if( outCount > onodes_max() )
	{
		return errorMessages[ EMT_INCOUNT_MORE_THAN_MAX ];
	}
	return noErrorMessage;
}

const std::wstring& CellProcessStrategy::correct_node_count( NodeTypes updatingType,
																														 size_t &inCount,
																														 size_t &outCount ) const
{
	const std::wstring& msg = is_valid_node_count( inCount, outCount );
	if( noErrorMessage == msg )
	{
		return msg;
	}

	if( inCount > inodes_max() )
	{
		inCount = inodes_max();
	}
	if( outCount > onodes_max() )
	{
		outCount = onodes_max();
	}
	return msg;
}

const std::wstring& CellProcessStrategy::correct_node_count( size_t oldInCount, size_t &newInCount,
																														 size_t oldOutCount, size_t &newOutCount ) const
{
	if( newInCount != oldInCount )
	{
		return correct_node_count( NT_INPUT, newInCount, newOutCount );
	}
	return correct_node_count( NT_OUTPUT, newInCount, newOutCount );
}
