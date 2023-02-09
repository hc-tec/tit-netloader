
file(GLOB_RECURSE CO_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(net_loader STATIC ${CO_SRC_FILES} url_request/url_request_observer.cc url_request/url_request_observer.h base/weak_container.h)

target_include_directories(net_loader
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
        )

target_link_libraries(net_loader PUBLIC co backtrace http_parser tit_log tit_base)


install(
        TARGETS net_loader
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)




