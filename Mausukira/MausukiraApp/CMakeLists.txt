set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(MausukiraApp main.cpp Game.cpp Window.cpp ecs/systems/CollisionSystem/CollisionSystem.cpp ecs/systems/CollisionSystem/CollisionSystem.h dungeon/algorithms/Coordinate.h dungeon/algorithms/AlgorithmsHelper.h ecs/components/EntityComponent.h)

add_subdirectory(ecs)
add_subdirectory(dungeon)
add_subdirectory(states_stack)
add_subdirectory(utils)

target_link_libraries(MausukiraApp
        PRIVATE
        sfml-graphics
        sfml-system
        sfml-window
        EnTT::EnTT
        jsoncpp_lib
        poly2tri
        tgui
        )

if (WIN32)
    add_custom_command(TARGET MausukiraApp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:MausukiraApp>)
endif ()

# Ensure resource files are available by copying
add_custom_command(
        TARGET MausukiraApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying resources to binary directory."
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:MausukiraApp>/resources
)