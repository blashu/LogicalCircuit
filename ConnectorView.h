#ifndef CONNECTORVIEW_H
#define CONNECTORVIEW_H

#include <QGraphicsItem>

class CellView;

class ConnectorView : public QGraphicsItem
{
	public:
			ConnectorView( CellView* fromCell, size_t outId,
										 CellView* toCell, size_t inId,
										 QPointF worldFrom, QPointF worldTo );

			virtual QRectF boundingRect() const;
			virtual void paint( QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget );

			CellView* from();
			CellView* to();
			size_t out_id();
			size_t in_id();

			void set_from( QPointF point );
			void set_to( QPointF point );

			void update();
			void calc_bounding_and_line_rect();

	private:
			CellView* _fromCell;
			CellView* _toCell;
			QPointF _worldFrom;
			QPointF _worldTo;
			size_t _outId;
			size_t _inId;

			QRectF boundingConnectorRect;
			QLineF resLine;
};

#endif // CONNECTORVIEW_H
