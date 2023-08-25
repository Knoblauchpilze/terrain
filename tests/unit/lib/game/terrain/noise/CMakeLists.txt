
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources(terrain-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/WhiteNoiseTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicNoiseTest.cc
	)