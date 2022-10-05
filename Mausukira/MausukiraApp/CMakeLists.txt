add_executable(MausukiraApp main.cpp)

if(WIN32)
    add_custom_command(TARGET MausukiraApp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:MausukiraApp>)
endif()

target_link_libraries(MausukiraApp
        PRIVATE
        sfml-graphics
        sfml-system
        sfml-window
        )

