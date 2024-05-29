cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(artemis-oedo)

# ROOT 6 installation
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Default installation dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/ CACHE PATH "install dir" FORCE)

# Build options
option(BUILD_PARQUET "option to build with parquet outputs (requires Apache Arrow libraries)" OFF)
message("BUILD_PARQUET:" ${BUILD_PARQUET})
option(BUILD_KAFKA "option to build with Apache Kafka streaming (requires librdkafka)" OFF)
message("BUILD_KAFKA:" ${BUILD_KAFKA})


# path definitions
find_package(artemis HINTS ${TARTSYS} REQUIRED)
if(NOT ${ARTEMIS_BUILD_GET})
    message(SEND_ERROR "artemis is not built with GETDecoder which is required by src-oedo. Rebuild artemis with BUILD_GET=ON")
endif()

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net Physics Minuit Minuit2 Geom Gui Genetic)
find_package(yaml-cpp REQUIRED HINTS ${ARTEMIS_YAML_CPP_LIB_DIR}/../)

#-fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

link_directories(${ARTEMIS_GET_LIB_DIR})

add_subdirectory(src-oedo)
add_subdirectory(src-get)
if(${BUILD_PARQUET})
    add_subdirectory(src-parquet)
endif()
add_subdirectory(analysis)
if(${BUILD_KAFKA})
    add_subdirectory(kafka-streaming)
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/thisartemis-oedo.sh.in"
    "${CMAKE_SOURCE_DIR}/thisartemis-oedo.sh"
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/artemislogon.C.in"
    "${CMAKE_SOURCE_DIR}/artemislogon.C"
    @ONLY
)
