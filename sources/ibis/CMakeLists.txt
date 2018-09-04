################################################################################
## sources/ibis/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL project
################################################################################

project(ibis LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")



# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


add_dependencies(${PROJECT_NAME} RapidJSON)


target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/signal.cpp
    src/init.cpp
    $<$<BOOL:${EDA_WITH_GDB_STACKTRACE}>:src/stacktrace_gdb.cpp>
    $<$<BOOL:${EDA_WITH_BOOST_STACKTRACE}>:src/stacktrace_boost.cpp>  
)


target_include_directories(${PROJECT_NAME} 
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/external/CLI>
        $<BUILD_INTERFACE:${RapidJSON_INCLUDE_DIR}>
    PUBLIC
        $<INSTALL_INTERFACE:include>
)


target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<BOOL:${EDA_WITH_GDB_STACKTRACE}>:EDA_WITH_GDB_STACKTRACE>
    $<$<BOOL:${EDA_WITH_BOOST_STACKTRACE}>:EDA_WITH_BOOST_STACKTRACE>  
)


if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE
		/W4
	)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE
		-Wall 
		-Wextra
	)
endif()


#target_compile_options(${PROJECT_NAME} PRIVATE
#    -g -fsanitize=address -fno-omit-frame-pointer
#)
#
#set_target_properties(${PROJECT_NAME} PROPERTIES 
#    LINK_FLAGS "-g -fsanitize=address -fno-omit-frame-pointer"
#)


if(CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Weverything
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
        )
    endif()
endif(CLANG_WARN_EVERYTHING)


# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


##
# Boost stacktrace
# [Configuration and Build](
#  https://www.boost.org/doc/libs/1_67_0/doc/html/stacktrace/configuration_and_build.html)
if(EDA_WITH_BOOST_STACKTRACE)
    if(WIN32)
        find_package(WinDbg REQUIRED)
        message(STATUS "WinDbg library found.")
        message(STATUS "WinDbg library is: ${DbgEng_LIBRARY}")
        target_compile_definitions(BOOST_STACKTRACE_USE_WINDBG)
        target_include_directories(${PROJECT_NAME} PUBLIC foooo)
        target_link_libraries(${PROJECT_NAME} INTERFACE WinDbg::WinDbg)
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


# Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
    Boost::system
    Boost::locale
    Boost::filesystem
)


##
# Install 
install(TARGETS ${PROJECT_NAME}
    EXPORT eda-ibis
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#install(DIRECTORY include/ 
#    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/eda
#)

