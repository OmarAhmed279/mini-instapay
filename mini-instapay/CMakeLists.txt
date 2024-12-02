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
target_include_directories(mini-instapay PUBLIC "${basedir}\\sqlite")

# TODO: Add tests and install targets if needed.
