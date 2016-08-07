#include "../../cpoint.h"
#include "../../cresourcedescription.h"
#include "qtbitmap.h"

#include <QDebug>

namespace VSTGUI {

IPlatformBitmap* IPlatformBitmap::create (CPoint* size)
{
    if (size)
        return new QtBitmap (*size);
    return new QtBitmap ();
}

QtBitmap::QtBitmap ()
{
}

QtBitmap::QtBitmap (const CPoint& size)
: pixmap(size.x, size.y)
, size(size)
{
}

QtBitmap::~QtBitmap ()
{
}

bool QtBitmap::load (const CResourceDescription& desc)
{
    if (desc.type == CResourceDescription::kStringType) {
        const bool result = pixmap.load (desc.u.name);
		if (result) {
			size.x = pixmap.size ().width ();
			size.y = pixmap.size ().height ();
		} else {
			size.x = size.y = 0;
		}
		return result;
	}
    return false;
}

const CPoint& QtBitmap::getSize () const
{
    return size;
}

IPlatformBitmapPixelAccess* QtBitmap::lockPixels (bool alphaPremultiplied)
{
	qDebug() << "lockPixels";
    return nullptr;
}

void QtBitmap::setScaleFactor (double)
{
}

double QtBitmap::getScaleFactor () const
{
    return 1;
}

} // namespace
