
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources(terrain-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ValueGeneratorTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientGenerator2dTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicGradientGenerator2dTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicPerlinGenerator2dTest.cc
	)
