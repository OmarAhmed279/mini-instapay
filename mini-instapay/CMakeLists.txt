cmake_minimum_required (VERSION 3.8)
project ("mini-instapay")

# Add source to this project's executable.
add_executable (mini-instapay "mini-instapay.cpp" "mini-instapay.h")

# add_compile_definitions(_SILENCE_FILESYSTEM_DEPRECATION_WARNING)
# add_definitions(-D_SILENCE_FILESYSTEM_DEPRECATION_WARNING)

cmake_path(SET basedir "${CMAKE_CURRENT_LIST_DIR}")
cmake_path(GET basedir PARENT_PATH parentdir)

target_include_directories(mini-instapay PUBLIC "${parentdir}\\nana-master\\include")
target_link_libraries(mini-instapay "nana_v143_debug_x64")
target_link_directories(mini-instapay PUBLIC "${parentdir}\\nana-master\\build\\bin")
# target_include_directories(mini-instapay PUBLIC "${basedir}\\sqlite")

# include_directories(${CMAKE_CURRENT_LIST_DIR}/sqlite)
# add_library(sqlite3 STATIC sqlite/sqlite3.c sqlite/sqlite3.h sqlite/sqlite3ext.h)
# add_executable(sqlite sqlite/sqlite3.c sqlite/shell.c sqlite/sqlite3.h sqlite/sqlite3ext.h)

# link_directories("${basedir}\\sqlite")
# target_link_libraries(mini-instapay sqlite3)

# TODO: Add tests and install targets if needed.
#if(WIN32)
#  add_custom_command(TARGET sqlite POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sqlite> ${CMAKE_BINARY_DIR}/sqlite3.exe
#    DEPENDS sqlite
#  )
#  install(FILES sqlite3.exe DESTINATION bin)
#endif()

#install(FILES sqlite/sqlite3.h sqlite/sqlite3ext.h DESTINATION include)
#install(TARGETS sqlite3 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
