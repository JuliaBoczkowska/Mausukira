include(FetchContent)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 2.5.1
#        GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab # 2.5.1
)

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.10.3
        GIT_PROGRESS TRUE
)

add_subdirectory(sfml)
add_subdirectory(entt)