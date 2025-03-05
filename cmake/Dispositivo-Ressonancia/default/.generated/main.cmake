include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Dispositivo_Ressonancia_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(Dispositivo_Ressonancia_default_default_XC8_FILE_TYPE_assemble)
add_library(Dispositivo_Ressonancia_default_default_XC8_assemble OBJECT ${Dispositivo_Ressonancia_default_default_XC8_FILE_TYPE_assemble})
    Dispositivo_Ressonancia_default_default_XC8_assemble_rule(Dispositivo_Ressonancia_default_default_XC8_assemble)
    list(APPEND Dispositivo_Ressonancia_default_library_list "$<TARGET_OBJECTS:Dispositivo_Ressonancia_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(Dispositivo_Ressonancia_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(Dispositivo_Ressonancia_default_default_XC8_assemblePreprocess OBJECT ${Dispositivo_Ressonancia_default_default_XC8_FILE_TYPE_assemblePreprocess})
    Dispositivo_Ressonancia_default_default_XC8_assemblePreprocess_rule(Dispositivo_Ressonancia_default_default_XC8_assemblePreprocess)
    list(APPEND Dispositivo_Ressonancia_default_library_list "$<TARGET_OBJECTS:Dispositivo_Ressonancia_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(Dispositivo_Ressonancia_default_default_XC8_FILE_TYPE_compile)
add_library(Dispositivo_Ressonancia_default_default_XC8_compile OBJECT ${Dispositivo_Ressonancia_default_default_XC8_FILE_TYPE_compile})
    Dispositivo_Ressonancia_default_default_XC8_compile_rule(Dispositivo_Ressonancia_default_default_XC8_compile)
    list(APPEND Dispositivo_Ressonancia_default_library_list "$<TARGET_OBJECTS:Dispositivo_Ressonancia_default_default_XC8_compile>")
endif()

add_executable(${Dispositivo_Ressonancia_default_image_name} ${Dispositivo_Ressonancia_default_library_list})

target_link_libraries(${Dispositivo_Ressonancia_default_image_name} PRIVATE ${Dispositivo_Ressonancia_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
Dispositivo_Ressonancia_default_link_rule(${Dispositivo_Ressonancia_default_image_name})


# Post build target to copy built file to the output directory.
add_custom_command(TARGET ${Dispositivo_Ressonancia_default_image_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${Dispositivo_Ressonancia_default_output_dir}
                    COMMAND ${CMAKE_COMMAND} -E copy ${Dispositivo_Ressonancia_default_image_name} ${Dispositivo_Ressonancia_default_output_dir}/${Dispositivo_Ressonancia_default_original_image_name}
                    BYPRODUCTS ${Dispositivo_Ressonancia_default_output_dir}/${Dispositivo_Ressonancia_default_original_image_name})
