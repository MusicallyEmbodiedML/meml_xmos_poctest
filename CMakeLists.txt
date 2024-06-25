message(VERBOSE "")

message("-- Processing project 'meml_xmos_poctest'")

# --- LIBRARY includes
list(APPEND APP_INCLUDES ${MEML_PROJECT_DIR_RELATIVE}/include)

message(VERBOSE APP_INCLUDES="${APP_INCLUDES}")

# --- C files
file(GLOB_RECURSE all_C_SRCS
        "${CMAKE_CURRENT_LIST_DIR}/src/*.c"
)
list(TRANSFORM all_C_SRCS
        REPLACE ${CMAKE_CURRENT_LIST_DIR}
        ${MEML_PROJECT_DIR_RELATIVE})
list(APPEND APP_C_SRCS ${all_C_SRCS})

message(VERBOSE APP_C_SRCS="${APP_C_SRCS}")

# --- C++ files
file(GLOB_RECURSE all_CXX_SRCS
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cc"
)
list(TRANSFORM all_CXX_SRCS
        REPLACE ${CMAKE_CURRENT_LIST_DIR}
        ${MEML_PROJECT_DIR_RELATIVE})
list(APPEND APP_CXX_SRCS ${all_CXX_SRCS})

message(VERBOSE APP_CXX_SRCS="${APP_CXX_SRCS}")

# --- Elevate changes to parent scope
set(APP_INCLUDES ${APP_INCLUDES} PARENT_SCOPE)
set(APP_C_SRCS ${APP_C_SRCS} PARENT_SCOPE)
set(APP_CXX_SRCS ${APP_CXX_SRCS} PARENT_SCOPE)

# --- DEBUG
message(VERBOSE "")
