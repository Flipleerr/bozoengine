add_executable(${PROJECT_NAME}
  main.c
  player.c
  )

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)