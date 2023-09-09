
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/common
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/app
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/coordinates
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/game
	)
