set(RDKAFKA_LIB_DIR /usr/lib/x86_64-linux-gnu CACHE PATH "librdkafka install dir")


function(setCompileOptions target_name)
target_include_directories(${target_name}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src-oedo>
        $<INSTALL_INTERFACE:include>
)

target_link_directories(${target_name}
    PUBLIC ${RDKAFKA_LIB_DIR}
)
target_link_libraries(${target_name}
    PUBLIC
        artemis::catcore
        artemis::catloop
        artemis::artcont
        artemis::catcmd
        artemis::catmc
        artemis::artdecoder
        artemis::artridf
        artemis::artrdf
        artemis::arthist
        artemis::artparam
        artemis::artshare
        artemis::CAT
        ${YAML_CPP_LIBRARIES}
        oedo
        rdkafka
)
endfunction()

function(addExec exec_name)
    add_executable(${exec_name} ${exec_name}.cpp)
    setCompileOptions(${exec_name})
    install(TARGETS ${exec_name}
        RUNTIME DESTINATION bin
    )
endfunction()

addExec(ridfFile2Stream)
addExec(stream_artemis)

add_library(artemisKafkaStreaming SHARED
    TKafkaDataSource.cpp
    TRIDFEventStoreKafka.cpp
)
set_target_properties(
    artemisKafkaStreaming
    PROPERTIES
        PUBLIC_HEADER
            "TKafkaDataSource.hpp"
)
setCompileOptions(artemisKafkaStreaming)
install(TARGETS artemisKafkaStreaming
    PUBLIC_HEADER DESTINATION include
    LIBRARY DESTINATION lib
)

ROOT_GENERATE_DICTIONARY(G__artemisKafkaStreaming
    "TRIDFEventStoreKafka.hpp"
    LINKDEF "linkdef_kafka.h"
    MODULE artemisKafkaStreaming
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libartemisKafkaStreaming_rdict.pcm
    DESTINATION lib
)
