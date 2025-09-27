add_library(${PROJECT_NAME} SHARED testkit.c)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_depend)