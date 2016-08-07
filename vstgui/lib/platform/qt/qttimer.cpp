#include "qttimer.h"

namespace VSTGUI {

IPlatformTimer* IPlatformTimer::create (IPlatformTimerCallback* callback)
{
    return new QtTimer (callback);
}

QtTimer::QtTimer (IPlatformTimerCallback* callback)
{
}

QtTimer::~QtTimer ()
{
}

bool QtTimer::start (uint32_t fireTime)
{
    timer.start (fireTime);
    return true;
}

bool QtTimer::stop ()
{
    timer.stop ();
    return true;
}

} // namespace
