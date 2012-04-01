#ifndef ANDCELLPROCESSSTRATEGY_H
#define ANDCELLPROCESSSTRATEGY_H

#include "CellProcessStrategy.h"

class AndCellProcessStrategy : public CellProcessStrategy
{
	public:
		virtual CellProcessStrategy* clone() const;

		virtual size_t inodes_min() const;
		virtual size_t inodes_max() const;
		virtual size_t onodes_min() const;
		virtual size_t onodes_max() const;
		virtual const std::wstring& cell_type_name();

	protected:
		virtual void do_process( const ibus_t& in, const obus_t& out );

	private:
		const static std::wstring cellTypeName;
};

#endif // ANDCELLPROCESSSTRATEGY_H
