#ifndef MAG_MACROS_H
#define MAG_MACROS_H

#include "stbprofile.h"

#define CHECK_PLAYER_VOID if(!player()) return;
#define CHECK_PLAYER(value) if(!player()) return value;

#define CONFIG_INNER_PORTAL_URL "inner_portal_url"

#endif // MAG_MACROS_H
