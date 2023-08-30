
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/hasher
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/generator
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/AreaGenerator.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ValueLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicGradientLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PeriodicPerlinLattice.cc
	)
