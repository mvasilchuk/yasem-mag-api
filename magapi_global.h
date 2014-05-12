#ifndef MAGAPI_GLOBAL_H
#define MAGAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MAGAPI_LIBRARY)
#  define MAGAPISHARED_EXPORT Q_DECL_EXPORT
#else
#  define MAGAPISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MAGAPI_GLOBAL_H
