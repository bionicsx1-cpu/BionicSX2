# FindUIKit.cmake — UIKit.framework finder
# AUDIT REFERENCE: Sections 4.3, 10.2

find_library(UIKit_LIBRARY UIKit)
mark_as_advanced(UIKit_LIBRARY)

if(UIKit_LIBRARY)
    set(UIKit_FOUND TRUE)
    add_library(UIKit::UIKit UNKNOWN IMPORTED)
    set_target_properties(UIKit::UIKit PROPERTIES
        IMPORTED_LOCATION "${UIKit_LIBRARY}"
    )
else()
    set(UIKit_FOUND FALSE)
endif()
