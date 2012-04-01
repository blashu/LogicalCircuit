#ifndef IBUSCELLPROCESSSTRATEGY_H
#define IBUSCELLPROCESSSTRATEGY_H

#include "CellProcessStrategy.h"
#include <vector>

class IBusCellProcessStrategy : public CellProcessStrategy
{
	public:
		virtual CellProcessStrategy* clone() const;
		virtual size_t inodes_min() const;
		virtual size_t inodes_max() const;
		virtual size_t onodes_min() const;
		virtual size_t onodes_max() const;
		virtual void do_process( const ibus_t& in, const obus_t& out );
		virtual const std::wstring& cell_type_name();

	private:
		inline void initialize_out( const obus_t& out );
		inline void increment_out( const obus_t& out );

	private:
		const static std::wstring cellTypeName;
};

inline void IBusCellProcessStrategy::initialize_out( const obus_t& out )
{
	for( auto i = out.size(); i --> 0; )
	{
		out[ i ] = false;
	}
}

inline void IBusCellProcessStrategy::increment_out( const obus_t& out )
{
	for( size_t i = 0, end = out.size(); i < end; ++i )
	{
		if( out[ i ] = !out[ i ] )
		{
			break;
		}
	}
}

#endif // IBUSCELLPROCESSSTRATEGY_H
