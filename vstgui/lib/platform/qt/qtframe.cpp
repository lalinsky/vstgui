#include "qtframe.h"
#include "qtdrawcontext.h"
#include "qtutils.h"

#include <QWidget>
#include <QElapsedTimer>
#include <QGuiApplication>
#include <QToolTip>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "../../cdropsource.h"
#include "../../cgradient.h"

namespace VSTGUI {

inline CButtonState convertMouseButtons (const Qt::MouseButtons& b)
{
	CButtonState buttons = 0;
	if (b & Qt::LeftButton)
		buttons |= kLButton;
	if (b & Qt::RightButton)
		buttons |= kRButton;
	if (b & Qt::MiddleButton)
		buttons |= kMButton;
	return buttons;
}

class QtFrame::ProxyWidget : public QWidget
{
public:
	ProxyWidget (QWidget* parent, IPlatformFrameCallback* callback);

protected:
	virtual void paintEvent (QPaintEvent* event) override;
	virtual void mousePressEvent (QMouseEvent* event) override;
	virtual void mouseReleaseEvent (QMouseEvent* event) override;
	virtual void mouseMoveEvent (QMouseEvent* event) override;
	virtual void leaveEvent (QEvent* event) override;
	virtual void wheelEvent (QWheelEvent* event) override;

private:
	IPlatformFrameCallback* callback;
	CPoint lastMousePos;
	CButtonState lastMouseButtons;
};

QtFrame::ProxyWidget::ProxyWidget (QWidget* parent, IPlatformFrameCallback* callback)
: QWidget(parent)
, callback(callback)
{
	setMouseTracking(true);
}

void QtFrame::ProxyWidget::paintEvent (QPaintEvent* event)
{
	QPainter painter (this);
	QtDrawContext* dc = new QtDrawContext (&painter);
	callback->platformDrawRect (dc, makeCRect (event->rect ()));
}

void QtFrame::ProxyWidget::mousePressEvent (QMouseEvent* event)
{
	lastMousePos = makeCPoint (event->pos ());
	lastMouseButtons = convertMouseButtons (event->buttons ());
	callback->platformOnMouseDown (lastMousePos, lastMouseButtons);
}

void QtFrame::ProxyWidget::mouseReleaseEvent (QMouseEvent* event)
{
	lastMousePos = makeCPoint (event->pos ());
	lastMouseButtons = convertMouseButtons (event->buttons ());
	callback->platformOnMouseUp (lastMousePos, lastMouseButtons);
}

void QtFrame::ProxyWidget::mouseMoveEvent (QMouseEvent* event)
{
	lastMousePos = makeCPoint (event->pos ());
	lastMouseButtons = convertMouseButtons (event->buttons ());
	callback->platformOnMouseMoved (lastMousePos, lastMouseButtons);
}

void QtFrame::ProxyWidget::leaveEvent (QEvent* event)
{
	callback->platformOnMouseExited (lastMousePos, lastMouseButtons);
}

void QtFrame::ProxyWidget::wheelEvent (QWheelEvent* event)
{
	lastMousePos = makeCPoint (event->pos ());
	lastMouseButtons = convertMouseButtons (event->buttons ());
	const auto degrees = event->angleDelta () / 8;
	if (degrees.x() != 0)
		callback->platformOnMouseWheel (lastMousePos, kMouseWheelAxisX, degrees.x() / 15, lastMouseButtons);
	if (degrees.y() != 0)
		callback->platformOnMouseWheel (lastMousePos, kMouseWheelAxisY, degrees.y() / 15, lastMouseButtons);
}

IPlatformFrame* IPlatformFrame::createPlatformFrame (IPlatformFrameCallback* frame, const CRect& size, void* parent, PlatformType parentType)
{
	if (parentType == kQWidget || parentType == kDefaultNative)
		return new QtFrame (frame, size, (QWidget*)parent);
	return nullptr;
}

CGradient* CGradient::create (const ColorStopMap& colorStopMap)
{
	return new CGradient (colorStopMap);
}

uint32_t IPlatformFrame::getTicks ()
{
	QElapsedTimer timer;
	timer.start ();
	return timer.msecsSinceReference ();
}

QtFrame::QtFrame (IPlatformFrameCallback* frame, const CRect& size, QWidget* parent)
: IPlatformFrame (frame)
, widget (new ProxyWidget(parent, frame))
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
	return true;
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
	buttons = convertMouseButtons (qApp->mouseButtons ());
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
	QToolTip::showText (makeQPoint (rect.getTopLeft ()), QString::fromUtf8 (utf8Text), widget, makeQRect (rect));
	return true;
}

bool QtFrame::hideTooltip ()
{
	QToolTip::hideText ();
	return true;
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
