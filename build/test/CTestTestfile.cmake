# CMake generated Testfile for 
# Source directory: /home/raptel/workspace/research/MultiParticleMethod/test
# Build directory: /home/raptel/workspace/research/MultiParticleMethod/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/raptel/workspace/research/MultiParticleMethod/build/test/test[1]_include.cmake")
add_test(test_test "/home/raptel/workspace/research/MultiParticleMethod/bin/test")
set_tests_properties(test_test PROPERTIES  _BACKTRACE_TRIPLES "/home/raptel/workspace/research/MultiParticleMethod/test/CMakeLists.txt;29;add_test;/home/raptel/workspace/research/MultiParticleMethod/test/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
