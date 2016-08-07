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
    qDebug() << "loading" << desc.u.name;
    if (desc.type == CResourceDescription::kStringType)
        return pixmap.load(desc.u.name);
    return false;
}

const CPoint& QtBitmap::getSize () const
{
    return size;
}

IPlatformBitmapPixelAccess* QtBitmap::lockPixels (bool alphaPremultiplied)
{
    // XXX
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
