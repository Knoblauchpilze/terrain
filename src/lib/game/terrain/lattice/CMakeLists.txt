
target_include_directories (terrain_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources (terrain_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Hasher.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ValueLattice.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GradientLattice.cc
	)
