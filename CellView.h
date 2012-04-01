#ifndef CELLVIEW_H
#define CELLVIEW_H

#include <QGraphicsItem>
#include <QObject>
#include <vector>
#include "Cell.h"
#include "ConnectorView.h"

class CellView : public QObject, public QGraphicsItem
{
	Q_OBJECT
	public:
		CellView( Cell* cell, QString title = "", qreal width = 20, qreal height = 30 );
		virtual ~CellView();

	signals:
		void clicked();
		void removed();

	public:
		virtual QRectF boundingRect() const;
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

		virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
		virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

		QString title();
		void set_title( QString titleText );

		void process();
		void stop_process();

		void resize_connectors_count( size_t newInCount, size_t newOutCount );
		void connect_to_in( CellView* targetOutCellView, size_t targetOutId, size_t outId );
		void disconnect_from_in( size_t inId );
		void disconnect_from_out( size_t outId );
		void disconnect_all_connectors();

		QPointF get_in_node_glob_coords( size_t id );
		QPointF get_out_node_glob_coords( size_t id );

		inline size_t in_node_count();
		inline size_t out_node_count();

		inline bool is_selected();
		inline void set_selected( bool selected );

	protected:
		//width_drawing_rect
		static int wdr( int width );
		//height_drawing_rect
		static int hdr( int height );
		//left_in_drawing_rect
		static int lidr( int left );
		//top_in_drawing_rect
		static int tidr( int top );

	private:
		enum {
			GAP_TITLE_TOP = 10 ,
			PADDING_TOP = 8 ,
			PADDING_BOTTOM = PADDING_TOP ,
			MARGIN_SIDE = 5 ,
			MARGIN_MID = 4 ,
			FLAG_SIDE = 5 ,
			PEN_SIZE = 1
		};

		static const QColor grey;

	private:
		void paint_cell( QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget );

		void draw_std_cell_nodes( QPainter *painter );
		template <typename T>
		void draw_std_cell_nodes( QPainter *painter, T& bus, int x, int y );

		void update();

		void calc_rects();
		void calc_cell_rect();
		void calc_title_rect();
		void calc_rects_translation();
		void calc_bounding_rect();

	private:
		QRectF cellRect;

		QString titleText;
		QRectF titleRect;
		QLineF* pins;

		QRectF boundingCellRect;

		Cell* cell;

		bool isSelected;

		std::vector<ConnectorView*> inConnectors;
		std::vector<ConnectorView*> outConnectors;
};

inline bool CellView::is_selected()
{
	return isSelected;
}

inline void CellView::set_selected( bool selected )
{
	isSelected = selected;
	CellView::update();
}

inline size_t CellView::in_node_count()
{
	return cell->in_count();
}

inline size_t CellView::out_node_count()
{
	return cell->out_count();
}

#endif // CELLVIEW_H
