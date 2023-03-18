add_executable (
    metal
    metal.cpp
)

target_compile_features ( metal PRIVATE cxx_std_20 )

target_link_libraries (
    metal
    ${MICROSTRUCTURE_FRAMEWORK_NAME}
)