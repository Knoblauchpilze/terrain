
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/InterpolationStrategy.cc
	${CMAKE_CURRENT_SOURCE_DIR}/InterpolationAxis.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Bilinear2d.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Bilinear3d.cc
	)
