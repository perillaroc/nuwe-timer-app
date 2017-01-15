#pragma once

#include <QtCore/qglobal.h>

#if defined(PROGRESS_UTIL_LIBRARY)
#  define PROGRESS_UTIL_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define PROGRESS_UTIL_SHARED_EXPORT Q_DECL_IMPORT
#endif
