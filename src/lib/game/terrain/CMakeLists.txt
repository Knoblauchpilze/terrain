
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/interpolation
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/noise
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/point
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

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/PositiveCyclicInteger.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Type.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Terrain.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Map.cc
	)
