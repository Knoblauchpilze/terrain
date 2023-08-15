
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
	${CMAKE_CURRENT_SOURCE_DIR}/lattice
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Terrain.cc
	)
