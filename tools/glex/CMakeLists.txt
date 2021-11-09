add_executable(glex glex.cpp)

target_link_libraries(glex 
PRIVATE
    Regex
    DFA
)
