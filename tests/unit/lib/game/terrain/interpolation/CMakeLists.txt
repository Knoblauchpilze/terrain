
target_include_directories(terrain-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

target_sources(terrain-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ConstexprPowImplTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/InterpolationAxisTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Bilinear2dTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Bilinear3dTest.cc
	)
