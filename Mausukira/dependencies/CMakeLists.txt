include(FetchContent)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 2.5.1
)

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.10.3
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        JsonCpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
        GIT_TAG 1.9.5
)

FetchContent_Declare(
        poly2tri
        GIT_REPOSITORY https://github.com/jhasse/poly2tri
        GIT_TAG 81612cb108b54c14c695808f494f432990b279fd
)


add_subdirectory(sfml)
add_subdirectory(entt)
add_subdirectory(jsoncpp)
add_subdirectory(poly2tri)