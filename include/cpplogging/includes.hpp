#ifdef _MSC_VER
#include <time.h>
#pragma message("Detected MSVC, using gmtime_s.")
#else
#pragma message("MSVC not detected, using own gmtime_s implementation.")
void gmtime_s(tm *tmDest, const time_t *sourceTime)
{
    if (tmDest == NULL || sourceTime == NULL)
    {
        std::terminate();
    }
    gmtime_r(sourceTime, tmDest);
}
#endif