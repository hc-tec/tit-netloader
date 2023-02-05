
file(GLOB_RECURSE CO_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(net_loader ${CO_SRC_FILES})

target_include_directories(net_loader
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
        )

install(
        TARGETS net_loader
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(WITH_OPENSSL)
    find_package(OpenSSL 1.1.0 REQUIRED)
    target_compile_definitions(net_loader PRIVATE HAS_OPENSSL)
    target_link_libraries(net_loader PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    if(WIN32)
        # FindOpenSSL.cmake shipped in CMake < 3.21.0 doesn't properly propagate
        # crypt32. We should also handle ws2_32 but cocoyaxi link to it later.
        target_link_libraries(net_loader PRIVATE crypt32)
    endif()
endif()

