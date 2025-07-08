add_executable(${PROJECT_NAME}
  main.c
  player.c
  levels.c
  )

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

if(BOZOENGINE_COPY_ASSETS)
  add_custom_command(TARGET bozoengine POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/assets
          $<TARGET_FILE_DIR:bozoengine>/assets
  )
endif()