
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Range.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Area2dGenerator.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Area3dGenerator.cc
	)
