#include "../../cfont.h"
#include "qtfont.h"
#include <QFontMetricsF>
#include <QFontDatabase>

namespace VSTGUI {

IPlatformFont* IPlatformFont::create (UTF8StringPtr name, const CCoord& size, const int32_t& style)
{
    return new QtFont(name, size, style);
}

bool IPlatformFont::getAllPlatformFontFamilies (std::list<std::string>& fontFamilyNames)
{
    QFontDatabase database;
    foreach (const QString &family, database.families()) {
        fontFamilyNames.push_back(family.toStdString());
    }
    return true;
}

QtFont::QtFont (UTF8StringPtr name, const CCoord& size, const int32_t& style)
: font(name)
{
    font.setPixelSize (size);
    if (style & kBoldFace)
        font.setWeight (QFont::Bold);
    if (style & kItalicFace)
        font.setItalic (true);
    if (style & kUnderlineFace)
        font.setUnderline (true);
    if (style & kStrikethroughFace)
        font.setStrikeOut (true);
}

QtFont::~QtFont ()
{
}

double QtFont::getAscent () const
{
    QFontMetricsF fm (font);
    return fm.ascent ();
}

double QtFont::getDescent () const
{
    QFontMetricsF fm (font);
    return fm.descent ();
}

double QtFont::getLeading () const
{
    QFontMetricsF fm (font);
    return fm.leading ();
}

double QtFont::getCapHeight () const
{
    return -1;
}

IFontPainter* QtFont::getPainter ()
{
    return nullptr;
}

} // namespace
