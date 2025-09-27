add_executable(examples demo.c)
target_link_libraries(examples PRIVATE ${PROJECT_NAME}_depend ${PROJECT_NAME})