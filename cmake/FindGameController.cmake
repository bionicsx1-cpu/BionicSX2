# FindGameController.cmake — GameController.framework finder
# AUDIT REFERENCE: Sections 8.3, 10.2

find_library(GameController_LIBRARY GameController)
mark_as_advanced(GameController_LIBRARY)

if(GameController_LIBRARY)
    set(GameController_FOUND TRUE)
    add_library(GameController::GameController UNKNOWN IMPORTED)
    set_target_properties(GameController::GameController PROPERTIES
        IMPORTED_LOCATION "${GameController_LIBRARY}"
    )
else()
    set(GameController_FOUND FALSE)
endif()
