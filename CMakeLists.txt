# ------------ project setup ------------ #
project(cpasswordcheck)
set(CMAKE_C_FLAGS "-O3")


# ------------ main executable ------------ #
FILE(GLOB SOURCE_FILES src/**.c)

add_executable(check ${SOURCE_FILES})

target_include_directories(check PRIVATE
	src
)
