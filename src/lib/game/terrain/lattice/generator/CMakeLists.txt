
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/ValueGenerator.cc
	${CMAKE_CURRENT_SOURCE_DIR}/AbstractGradientGenerator.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientGenerator.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicPerlinGenerator.cc
	)
