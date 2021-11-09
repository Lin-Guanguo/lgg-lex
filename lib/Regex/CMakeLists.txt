add_library(Regex RegexReader.cpp)

target_include_directories(Regex 
PUBLIC 
    ../../include/glex
)