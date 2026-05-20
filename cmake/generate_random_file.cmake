if(NOT DEFINED OUTPUT)
    message(FATAL_ERROR "OUTPUT is required")
endif()

if(NOT DEFINED SIZE_BYTES)
    message(FATAL_ERROR "SIZE_BYTES is required")
endif()

get_filename_component(output_dir "${OUTPUT}" DIRECTORY)
file(MAKE_DIRECTORY "${output_dir}")

# Repeat a fixed byte pattern so large example fixtures do not need to be
# stored in the source tree.
set(pattern "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")
string(LENGTH "${pattern}" pattern_size)
file(WRITE "${OUTPUT}" "")

# Append in pattern sized chunks, then write the final partial chunk.
set(remaining "${SIZE_BYTES}")
while(remaining GREATER 0)
    if(remaining GREATER pattern_size)
        file(APPEND "${OUTPUT}" "${pattern}")
        math(EXPR remaining "${remaining} - ${pattern_size}")
    else()
        string(SUBSTRING "${pattern}" 0 "${remaining}" tail)
        file(APPEND "${OUTPUT}" "${tail}")
        set(remaining 0)
    endif()
endwhile()
