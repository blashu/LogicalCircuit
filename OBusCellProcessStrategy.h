#ifndef OBUSCELLPROCESSSTRATEGY_H
#define OBUSCELLPROCESSSTRATEGY_H

#include "CellProcessStrategy.h"
#include <vector>

class OBusCellProcessStrategy : public CellProcessStrategy
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

	private:
		const static std::wstring cellTypeName;
};
#endif // OBUSCELLPROCESSSTRATEGY_H
