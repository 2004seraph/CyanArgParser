SET( APP_EXE testApp )

ADD_EXECUTABLE( ${APP_EXE}
                main.cpp ) 

target_include_directories(${APP_EXE} PRIVATE ${SOURCE_SUBDIR})

TARGET_LINK_LIBRARIES( ${APP_EXE}
                       CyanArgParser )

add_test(NAME testApp
         COMMAND testApp)