#
# KDevelop-FlawFinder/CMakeLists.txt
# Builds the FlawFinder plugin
#

project (KDevelopFlawFinder)

	find_package (KDE4)
	find_package (KDevPlatform)

	include (${QT_USE_FILE})
	include_directories (${KDEVPLATFORM_INCLUDE_DIR})
	include_directories (${KDevelopFlawFinder_BINARY_DIR})

	set (KDevelopFlawFinder_HEADERS_MOC
		${KDevelopFlawFinder_SOURCE_DIR}/FlawFinderPlugin.h
		${KDevelopFlawFinder_SOURCE_DIR}/FlawFinderView.h
	)

	set (KDevelopFlawFinder_HEADERS
	)

	set (KDevelopFlawFinder_SOURCES
		${KDevelopFlawFinder_SOURCE_DIR}/FlawFinderPlugin.cpp
		${KDevelopFlawFinder_SOURCE_DIR}/FlawFinderView.cpp
	)

	set (KDevelopFlawFinder_UIS
		${KDevelopFlawFinder_SOURCE_DIR}/ui/FlawFinderView.ui
	)

	qt4_wrap_ui (KDevelopFlawFinder_UIS_OUT ${KDevelopFlawFinder_UIS})

	kde4_add_plugin (KDevelopFlawFinder
		${KDevelopFlawFinder_HEADER} ${KDevelopFlawFinder_SOURCES}
		${KDevelopFlawFinder_HEADERS_MOC}
		${KDevelopFlawFinder_UIS_OUT} ${KDevelopFlawFinder_UIS}
	)

	target_link_libraries (KDevelopFlawFinder
		${KDEVPLATFORM_INTERFACES_LIBRARIES}
		${KDEVPLATFORM_PROJECT_LIBRARIES}
	)

	install (TARGETS KDevelopFlawFinder DESTINATION ${PLUGIN_INSTALL_DIR})
	install (FILES KDevelopFlawFinder.desktop DESTINATION ${SERVICES_INSTALL_DIR})

