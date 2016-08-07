#include "qtframe.h"

#include <QWidget>
#include <QElapsedTimer>
#include <QGuiApplication>
#include <QToolTip>
#include "../../cdropsource.h"
#include "../../cgradient.h"

namespace VSTGUI {

static inline QRect makeQRect (const CRect& rect)
{
    return QRect (rect.left, rect.top, rect.getWidth (), rect.getHeight ());
}

static inline QPoint makeQPoint (const CPoint& pos)
{
    return QPoint (pos.x, pos.y);
}

IPlatformFrame* IPlatformFrame::createPlatformFrame (IPlatformFrameCallback* frame, const CRect& size, void* parent, PlatformType parentType)
{
	return new QtFrame (frame, size, (QWidget*)parent);
}

CGradient* CGradient::create (const ColorStopMap& colorStopMap)
{
    vstgui_assert (false, "not implemented");
    return NULL;
}

uint32_t IPlatformFrame::getTicks ()
{
    QElapsedTimer timer;
    timer.start ();
    return timer.msecsSinceReference ();
}

QtFrame::QtFrame (IPlatformFrameCallback* frame, const CRect& size, QWidget* parent)
: IPlatformFrame (frame)
, widget (new QWidget(parent))
{
    widget->setGeometry(size.left, size.top, size.getWidth(), size.getHeight());
}

QtFrame::~QtFrame ()
{
}

bool QtFrame::getGlobalPosition (CPoint& pos) const
{
    QPoint p = widget->mapToGlobal(QPoint(0, 0));
    pos.x = p.x();
    pos.y = p.y();
    return true;
}

bool QtFrame::getSize (CRect& size) const
{
    QRect g = widget->geometry();
    size.left = g.left();
    size.top = g.top();
    size.right = g.right();
    size.bottom = g.bottom();
    return true;
}

bool QtFrame::setSize (const CRect& newSize)
{
    widget->setGeometry(newSize.left, newSize.top, newSize.getWidth(), newSize.getHeight());
}

bool QtFrame::getCurrentMousePosition (CPoint& mousePosition) const
{
    QPoint p = widget->mapFromGlobal (QCursor::pos ());
    mousePosition.x = p.x ();
    mousePosition.y = p.y ();
    return true;
}

bool QtFrame::getCurrentMouseButtons (CButtonState& buttons) const
{
    Qt::MouseButtons b = qApp->mouseButtons ();
    buttons = 0;
    if (b & Qt::LeftButton)
        buttons |= kLButton;
    if (b & Qt::RightButton)
        buttons |= kRButton;
    if (b & Qt::MiddleButton)
        buttons |= kMButton;
    return true;
}

bool QtFrame::setMouseCursor (CCursorType type)
{
    switch (type) {
	    case kCursorDefault:
            widget->setCursor (Qt::ArrowCursor);
            return true;
        case kCursorWait:
            widget->setCursor (Qt::WaitCursor);
            return true;
        case kCursorHSize:
            widget->setCursor (Qt::SizeHorCursor);
            return true;
        case kCursorVSize:
            widget->setCursor (Qt::SizeVerCursor);
            return true;
        case kCursorSizeAll:
            widget->setCursor (Qt::SizeAllCursor);
            return true;
        case kCursorNESWSize:
            widget->setCursor (Qt::SizeBDiagCursor);
            return true;
        case kCursorNWSESize:
            widget->setCursor (Qt::SizeFDiagCursor);
            return true;
        case kCursorCopy:
            widget->setCursor (Qt::DragCopyCursor);
            return true;
        case kCursorNotAllowed:
            widget->setCursor (Qt::ForbiddenCursor);
            return true;
        case kCursorHand:
            widget->setCursor (Qt::OpenHandCursor);
            return true;
    }
    return false;
}

bool QtFrame::invalidRect (const CRect& rect)
{
    widget->update (makeQRect (rect));
    return true;
}

bool QtFrame::scrollRect (const CRect& src, const CPoint& distance)
{
    widget->scroll (distance.x, distance.y, makeQRect (src));
    return true;
}

bool QtFrame::showTooltip (const CRect& rect, const char* utf8Text)
{
    QToolTip::showText (makeQPoint(rect.getTopLeft ()), QString::fromUtf8 (utf8Text), widget, makeQRect (rect));
}

bool QtFrame::hideTooltip ()
{
    QToolTip::hideText ();
}

void* QtFrame::getPlatformRepresentation () const
{
    return widget;
}

IPlatformTextEdit* QtFrame::createPlatformTextEdit (IPlatformTextEditCallback* textEdit)
{
    vstgui_assert (false, "not implemented");
    return NULL;
}

IPlatformOptionMenu* QtFrame::createPlatformOptionMenu ()
{
    vstgui_assert (false, "not implemented");
    return NULL;
}

IPlatformViewLayer* QtFrame::createPlatformViewLayer (IPlatformViewLayerDelegate* drawDelegate, IPlatformViewLayer* parentLayer)
{
    vstgui_assert (false, "not implemented");
    return NULL;
}

COffscreenContext* QtFrame::createOffscreenContext (CCoord width, CCoord height, double scaleFactor)
{
    vstgui_assert (false, "not implemented");
    return NULL;
}

DragResult QtFrame::doDrag (IDataPackage* source, const CPoint& offset, CBitmap* dragBitmap)
{
    vstgui_assert (false, "not implemented");
    return kDragError;
}

void QtFrame::setClipboard (IDataPackage* data)
{
    vstgui_assert (false, "not implemented");
}

IDataPackage* QtFrame::getClipboard ()
{
    vstgui_assert (false, "not implemented");
    return NULL;
}

} // namespace
