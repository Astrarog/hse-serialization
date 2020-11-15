find_path(Libnop_INCLUDE_DIR NAMES nop/serializer.h)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libnop Libnop_INCLUDE_DIR)

if(LIBNOP_FOUND AND NOT TARGET Libnop::Libnop)
    add_library(Libnop::Libnop INTERFACE IMPORTED)
    target_include_directories(Libnop::Libnop INTERFACE "${Libnop_INCLUDE_DIR}")
endif()

mark_as_advanced(Libnop_INCLUDE_DIR)
