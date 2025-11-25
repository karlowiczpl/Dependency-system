add_library(unity STATIC unity/unity.c)
target_include_directories(unity PUBLIC unity)

add_executable(dependency_system_tests dependency_system_tests.c hooks.c)
target_link_libraries(dependency_system_tests PRIVATE Dependency_system unity)

add_test(NAME dependency_system_tests COMMAND test_dependency_system)
