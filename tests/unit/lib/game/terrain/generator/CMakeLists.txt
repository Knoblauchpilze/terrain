
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources(terrain-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ValueGeneratorTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientGeneratorTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicGradientGeneratorTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicPerlinGeneratorTest.cc
	)
