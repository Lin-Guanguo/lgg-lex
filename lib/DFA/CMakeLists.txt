add_library(DFA DFA.cpp)

target_include_directories(DFA
PUBLIC
    ../../include/glex
)

target_link_libraries(DFA
PUBLIC
    Graph
    NFA
)