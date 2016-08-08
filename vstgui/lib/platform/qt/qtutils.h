#ifndef __qtutils__
#define __qtutils__

#include "../../crect.h"

#include <QRect>
#include <QRectF>

namespace VSTGUI {

inline QRect makeQRect (const CRect& rect)
{
	return QRect (rect.left, rect.top, rect.getWidth (), rect.getHeight ());
}

inline QRectF makeQRectF (const CRect& rect)
{
	return QRectF (rect.left, rect.top, rect.getWidth (), rect.getHeight ());
}

inline CRect makeCRect (const QRect &rect)
{
	return CRect (rect.x(), rect.y(), rect.width (), rect.height ());
}

inline CRect makeCRect (const QRectF &rect)
{
	return CRect (rect.x(), rect.y(), rect.width (), rect.height ());
}

inline QPoint makeQPoint (const CPoint& pos)
{
	return QPoint (pos.x, pos.y);
}

inline QPoint makeQPointF (const CPoint& pos)
{
	return QPoint (pos.x, pos.y);
}

inline CPoint makeCPoint (const QPointF& pos)
{
	return CPoint (pos.x (), pos.y ());
}

inline CPoint makeCPoint (const QSizeF& size)
{
	return CPoint (size.width (), size.height ());
}

} // namespace

#endif
