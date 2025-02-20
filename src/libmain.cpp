#include "version.h"

// Library version number.
struct wax::str::__version wax::str::lib_version {
  .str   = WAX_STRING_LIB_VERSION_STR,
  .major = WAX_STRING_LIB_VERSION_MAJOR,
  .minor = WAX_STRING_LIB_VERSION_MINOR,
  .patch = WAX_STRING_LIB_VERSION_PATCH
};
