set(GIT_MAIN_SRC main.cpp)
set(TARGET_NAME main)
add_executable(${TARGET_NAME} ${GIT_MAIN_SRC})

target_link_libraries(${TARGET_NAME} PRIVATE libgit2::libgit2)
