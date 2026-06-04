if (KWIN_BUILD_KCMS)
    add_subdirectory(kcm)
endif()
kwin_add_scripted_effect(cube package)
