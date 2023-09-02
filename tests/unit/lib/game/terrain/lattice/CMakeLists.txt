
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources(terrain-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ValueLatticeTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientLatticeTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicGradientLatticeTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicPerlinLatticeTest.cc
	)
