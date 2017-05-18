/*
provides a required part for all components
*/

#include <stdio.h>

#include "compinfo.h"

version newVersion(int major, int minor, int patch)
{

version ret;

snprintf(ret.ver_string, 15, "%d.%d.%d", major, minor, patch);
ret.major = major;
ret.minor = minor;
ret.patch = patch;

return ret;
}