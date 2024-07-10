
function(addExec exec_name)
add_executable(${exec_name} ${exec_name}.cpp)
target_include_directories(${exec_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src-oedo)
target_link_libraries(${exec_name} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES}
    artemis::catcmd artemis::catloop artemis::catcore artemis::artcont artemis::catmc
    artemis::artdecoder artemis::artridf artemis::artrdf artemis::arthist
    artemis::artparam artemis::artshare artemis::CAT oedo
    GETDecoder
    artget_sh12
)

install(TARGETS ${exec_name}
    RUNTIME DESTINATION bin
)
endfunction()

# Add filenames without their .cpp extension to compile and generate executables. 
addExec(run_artemis)
addExec(RDataFrameAnalysis)
addExec(srppacRDataFrameAna)

if(BUILD_PARQUET)
find_package(Arrow REQUIRED)
find_package(Parquet REQUIRED)

function(addParquetExec exec_name)
    add_executable(${exec_name} ${exec_name}.cpp)
    target_include_directories(${exec_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src-oedo ${CMAKE_CURRENT_SOURCE_DIR}/src-parquet)
    target_link_libraries(${exec_name} arrow parquet ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES}
    artemis::catcmd artemis::catloop artemis::catcore artemis::artcont artemis::catmc
    artemis::artdecoder artemis::artridf artemis::artrdf artemis::arthist
    artemis::artparam artemis::artshare artemis::CAT oedo
    GETDecoder
    artget_sh12
    parquetDump
    )

    install(TARGETS ${exec_name}
        RUNTIME DESTINATION bin)
endfunction()

addParquetExec(DumpParquet)

endif()
