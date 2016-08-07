#include "qtstring.h"

#include <algorithm>

namespace VSTGUI {

IPlatformString* IPlatformString::createWithUTF8String (UTF8StringPtr utf8String)
{
	return new QtString (utf8String);
}

QtString::QtString (UTF8StringPtr utf8String)
: string (QString::fromUtf8 (utf8String))
{
}

QtString::~QtString ()
{
}

void QtString::setUTF8String (UTF8StringPtr utf8String)
{
    string = QString::fromUtf8 (utf8String);
}

} // namespace
