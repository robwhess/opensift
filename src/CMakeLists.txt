include_directories(../include ${GTK2_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
set(OPENSIFT_SOURCES
    imgfeatures.c
    utils.c
    sift.c
    kdtree.c
    minpq.c
    xform.c)

add_library(opensift STATIC ${OPENSIFT_SOURCES})

add_executable(siftfeat siftfeat.c)
target_link_libraries(siftfeat opensift m
    ${GTK2_LIBRARIES} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(match match.c)
target_link_libraries(match opensift m
    ${GTK2_LIBRARIES} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(match_num match_num.c)
target_link_libraries(match_num opensift m
    ${GTK2_LIBRARIES} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(dspfeat dspfeat.c)
target_link_libraries(dspfeat opensift m
    ${GTK2_LIBRARIES} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS opensift siftfeat match match_num dspfeat
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(DIRECTORY ../include DESTINATION include/opensift
    FILES_MATCHING PATTERN "*.h")
