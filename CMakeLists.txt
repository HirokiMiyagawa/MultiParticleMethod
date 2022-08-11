cmake_minimum_required(VERSION 3.10)
project(MultiParticlMethod CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Ofast -flto -lm -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native -fopenmp")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native -fopenmp")

# target_compile_options(main PUBLIC
#   $<$<CONFIG:Release>:-O3>             # Release
#   $<$<CONFIG:Debug>:-O0 -g>            # Debug
#   $<$<CONFIG:RelWithDebgInfo>:-O3 -g>  # RelWithDebInfo
#   )
# target_compile_definitions(main PUBLIC
#   $<$<NOT:$<CONFIG:Debug>>:NDEBUG>     # Debug以外
#   )

# output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${PROJECT_SOURCE_DIR}/bin>)

# incude path
# include_directories(src/hpp/Base INTERFACE)
# include_directories(src/hpp/DefinitionOfSituation INTERFACE)
# include_directories(src/hpp/Global INTERFACE)
# include_directories(src/hpp/  MultiParticle INTERFACE)
# include_directories(src/hpp/MyLibrary INTERFACE)
# include_directories(src/hpp/Readcsv INTERFACE)

# message(STATUS "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
# message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}")
# target_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/bin/main INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
# add_executable(main src/cpp/main.cpp)

# ヘッダが入ってるディレクトリを洗い出すマクロ
MACRO(HEADER_DIRECTORIES return_list)
   FILE(GLOB_RECURSE new_list *.hpp)
   SET(dir_list "")
   FOREACH(file_path ${new_list})
       GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
       SET(dir_list ${dir_list} ${dir_path})
   ENDFOREACH()
   LIST(REMOVE_DUPLICATES dir_list)
   SET(${return_list} ${dir_list})
ENDMACRO()

# マクロ呼び出し
HEADER_DIRECTORIES(header_dir_list)
# 件数カウント
list(LENGTH header_dir_list header_dir_list_count)
message(STATUS "Count: ${header_dir_list_count}")
# リスト一覧出力
message(${header_dir_list})
# いつもの
include_directories(${header_dir_list})
add_executable(main src/cpp/main.cpp)


message(STATUS "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")

set(MY_INCLUDE_PATH ${header_dir_list})

add_custom_target(document COMMAND "doxygen" "doc/Doxyfile")    

target_compile_options(main PUBLIC
  $<$<CONFIG:Release>:-O3>             # Release
  $<$<CONFIG:Debug>:-O0 -g>            # Debug
  $<$<CONFIG:RelWithDebgInfo>:-O3 -g>  # RelWithDebInfo
)
target_compile_definitions(
    main PUBLIC
  $<$<NOT:$<CONFIG:Debug>>:NDEBUG>     # Debug以外
)

# add_subdirectory(test)
