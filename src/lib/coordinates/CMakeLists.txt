
target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/CoordinateFrame.cc
	${CMAKE_CURRENT_SOURCE_DIR}/TransformedViewFrame.cc
	)

target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
