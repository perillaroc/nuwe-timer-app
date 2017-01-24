#pragma once

#include <QtCore/qglobal.h>

#if defined(PYTHON_ENV_LIBRARY)
#  define PYTHON_ENV_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define PYTHON_ENV_SHARED_EXPORT Q_DECL_IMPORT
#endif

