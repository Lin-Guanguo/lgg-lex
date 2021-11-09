add_library(NFA NFA.cpp)

target_include_directories(NFA 
PUBLIC
    ../../include/glex
)

target_link_libraries(NFA 
PUBLIC
    Graph
)