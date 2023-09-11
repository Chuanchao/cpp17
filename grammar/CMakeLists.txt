find_package(Boost COMPONENTS random chrono REQUIED)
aux_source_directory(. grammar_SRCS)
add_library(grammar SHARED ${grammar_SRCS})
target_link_libraries(grammar
        PUBLIC
        Boost::random
        Boost::chrono
        )


