
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/interpolation
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/noise
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/hasher
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/area
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/generator
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/lattice
	)

target_sources(terrain-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/PositiveCyclicIntegerTest.cc
	)
