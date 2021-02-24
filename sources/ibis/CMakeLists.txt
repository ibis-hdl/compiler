################################################################################
## EDA/ibis project
##
## file: sources/ibis/CMakeLists.txt
################################################################################

project(ibis LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        eda::common
        Boost::system
        Boost::locale
        Boost::filesystem
        Threads::Threads
)


add_dependencies(${PROJECT_NAME} RapidJSON)


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ibis/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/ibis/version.hpp
    @ONLY
)


target_sources(${PROJECT_NAME} 
    PRIVATE
        src/main.cpp
        src/init.cpp
        src/signal_handler.cpp
        $<$<BOOL:${EDA_WITH_GDB_STACKTRACE}>:src/stacktrace_gdb.cpp>
        $<$<BOOL:${EDA_WITH_BOOST_STACKTRACE}>:src/stacktrace_boost.cpp>  
        src/build_info.cpp
)


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME} 
        PRIVATE 
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ibis/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ibis/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CLI11_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${RapidJSON_INCLUDE_DIR}>
)


target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
        $<$<BOOL:${EDA_WITH_GDB_STACKTRACE}>:EDA_WITH_GDB_STACKTRACE>
        $<$<BOOL:${EDA_WITH_BOOST_STACKTRACE}>:EDA_WITH_BOOST_STACKTRACE>  
)


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_compile_options(${PROJECT_NAME} 
        PRIVATE
            -g -fno-omit-frame-pointer
    )    
    set_target_properties(${PROJECT_NAME} 
        PROPERTIES 
            LINK_FLAGS "-g -fno-omit-frame-pointer"
    )
endif()


##
# Boost stacktrace
# [Configuration and Build](
#  https://www.boost.org/doc/libs/1_67_0/doc/html/stacktrace/configuration_and_build.html)
if(EDA_WITH_BOOST_STACKTRACE)
    if(WIN32)
        find_package(Boost REQUIRED COMPONENTS stacktrace_windbg)
        message(STATUS "WinDbg library found.")
        target_compile_definitions(${PROJECT_NAME} 
            PRIVATE
                BOOST_STACKTRACE_USE_WINDBG
        )
        target_include_directories(${PROJECT_NAME} 
            PRIVATE 
                ${Boost_INCLUDE_DIRS}
        )
        target_link_libraries(${PROJECT_NAME} 
            PRIVATE
                dbgeng ole32 
        )
    else()
        find_package(Backtrace REQUIRED)
        message(STATUS "### backtrace library found.")
        message(STATUS "### backtrace include dir is: ${Backtrace_INCLUDE_DIR}")
        message(STATUS "### backtrace library is: ${Backtrace_LIBRARY}")
        target_compile_definitions(${PROJECT_NAME} PRIVATE BOOST_STACKTRACE_USE_BACKTRACE)
        target_include_directories(${PROJECT_NAME} PUBLIC ${Backtrace_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME} INTERFACE ${Backtrace_LIBRARY})
        if(UNIX AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            # [Where is libdl.so on Mac OS X?](
            #  https://stackoverflow.com/questions/20169660/where-is-libdl-so-on-mac-os-x)
            target_link_libraries(${PROJECT_NAME} INTERFACE ${CMAKE_DL_LIBS})
        endif()
    endif()
endif()

 
