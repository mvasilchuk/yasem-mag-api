#ifndef MAG_MACROS_H
#define MAG_MACROS_H

#include "stbprofile.h"

#define CHECK_PLAYER_VOID Q_ASSERT(profile->getProfilePlugin()->player());
#define CHECK_PLAYER(value) Q_ASSERT(profile->getProfilePlugin()->player());

#define CONFIG_INNER_PORTAL_URL "InnerPortal/URL"

#endif // MAG_MACROS_H
