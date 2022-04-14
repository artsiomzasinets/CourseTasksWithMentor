project(redBlackTree)



add_library(redBlackTree_lib STATIC Tree.h)

set_target_properties(redBlackTree_lib PROPERTIES
        LINKER_LANGUAGE CXX)#for fix the error because there is no "*.cpp" files, there is only tepmplates