
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources(terrain-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ValueLattice2dTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientLattice2dTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicGradientLattice2dTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicPerlinLattice2dTest.cc
	)
