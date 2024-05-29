find_package(Arrow REQUIRED)
find_package(Parquet REQUIRED)

set(LIB_NAME parquetDump)

set(SOURCES
    TDataBuilderBase.cpp
    TSimpleDataBuilder.cpp
    TTimingChargeDataBuilder.cpp
    TSRPPACPlaneDataBuilder.cpp
    TParquetFileWriter.cpp
)

set(HEADERS
    TDataBuilderBase.hpp
    TSimpleDataBuilder.hpp
    TTimingChargeDataBuilder.hpp
    TSRPPACPlaneDataBuilder.hpp
    TParquetFileWriter.hpp
)

add_library(${LIB_NAME} SHARED ${SOURCES})

target_include_directories(${LIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${LIB_NAME}
    PRIVATE
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
        arrow
        parquet
)

set_target_properties(
    ${LIB_NAME}
    PROPERTIES
        PUBLIC_HEADER "${headers}"
)

install(TARGETS ${LIB_NAME}
    INCLUDES DESTINATION include
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    LIBRARY DESTINATION lib
)

function(addParquetExec exec_name)
    add_executable(${exec_name} ${exec_name}.cpp)
    target_include_directories(${exec_name} PRIVATE /opt/artemis/include ${CMAKE_CURRENT_SOURCE_DIR}/src-oedo)
    target_link_directories(${exec_name} PRIVATE /opt/artemis/lib )
    target_link_libraries(${exec_name} arrow parquet ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES}
    artemis::catcmd artemis::catloop artemis::catcore artemis::artcont artemis::catmc
    artemis::artdecoder artemis::artridf artemis::artrdf artemis::arthist
    artemis::artparam artemis::artshare artemis::CAT oedo
    GETDecoder
    artget_sh12)

    install(TARGETS ${exec_name}
        RUNTIME DESTINATION bin)
endfunction()

