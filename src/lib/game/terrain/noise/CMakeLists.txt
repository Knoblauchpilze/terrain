
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Type.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Noise2d.cc
	${CMAKE_CURRENT_SOURCE_DIR}/WhiteNoise.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Noise2dFactory.cc
	)
