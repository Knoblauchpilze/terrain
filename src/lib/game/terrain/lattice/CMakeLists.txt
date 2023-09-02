
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/ValueLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/AbstractGradientLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicGradientLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicPerlinLattice.cc
	)
