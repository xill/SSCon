set(MATHLIB_Sources
	math/math.h
	math/vec2.h
	math/vec3.h
)

add_library(mathlib ${MATHLIB_Sources})

add_subdirectory(terminal)
add_subdirectory(textbuilder)