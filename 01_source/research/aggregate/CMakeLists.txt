cmake_minimum_required(VERSION 3.16)
project(prismsun_reconstruction LANGUAGES CXX)

if(NOT ANDROID)
  message(FATAL_ERROR "This aggregate target is intended for the Android NDK toolchain.")
endif()

get_filename_component(RESEARCH_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(DETECTION_POINT_ROOT "${RESEARCH_ROOT}/detection_points")
function(resolve_point_source category name output_variable)
  set(classified "${DETECTION_POINT_ROOT}/${category}/src/${name}")
  if(EXISTS "${classified}")
    set("${output_variable}" "${classified}" PARENT_SCOPE)
  else()
    if(category STREQUAL "accessibility")
      set(legacy "${RESEARCH_ROOT}/accessibility/src")
    elseif(category STREQUAL "device_identity")
      set(legacy "${RESEARCH_ROOT}/device_identity/src")
    elseif(category STREQUAL "environment_memory")
      set(legacy "${RESEARCH_ROOT}/environment_memory/src")
    elseif(category STREQUAL "proc_fd_clock_mcp")
      set(legacy "${RESEARCH_ROOT}/mcp_clock/src")
    else()
      set(legacy "${RESEARCH_ROOT}/src")
    endif()
    set("${output_variable}" "${legacy}/${name}" PARENT_SCOPE)
  endif()
endfunction()
resolve_point_source(aarch64_entry_classifier verified_helpers.cpp SRC_HELPERS)
resolve_point_source(tracer_filter_policy observed_models.cpp SRC_FILTER)
resolve_point_source(shared_ring_reader shared_ring_model.cpp SRC_RING)
resolve_point_source(jni_class_probe class_probe_model.cpp SRC_PROBE)
resolve_point_source(jni_class_probe jni_layout_check.cpp SRC_JNI_LAYOUT)
function(resolve_point_dir category legacy output_variable)
  set(classified "${DETECTION_POINT_ROOT}/${category}/src")
  if(EXISTS "${classified}")
    set("${output_variable}" "${classified}" PARENT_SCOPE)
  else()
    set("${output_variable}" "${RESEARCH_ROOT}/${legacy}/src" PARENT_SCOPE)
  endif()
endfunction()
resolve_point_dir(accessibility accessibility DIR_ACCESSIBILITY)
resolve_point_dir(device_identity device_identity DIR_DEVICE_IDENTITY)
resolve_point_dir(environment_memory environment_memory DIR_ENVIRONMENT)
resolve_point_dir(proc_fd_clock_mcp mcp_clock DIR_MCP_CLOCK)
resolve_point_source(accessibility accessibility_core.cpp SRC_ACCESSIBILITY_CORE)
resolve_point_source(accessibility accessibility_jni.cpp SRC_ACCESSIBILITY_JNI)
resolve_point_source(accessibility accessibility_env.cpp SRC_ACCESSIBILITY_ENV)
resolve_point_source(accessibility accessibility_monitor.cpp SRC_ACCESSIBILITY_MONITOR)
resolve_point_source(device_identity crypto.cpp SRC_IDENTITY_CRYPTO)
resolve_point_source(device_identity identity.cpp SRC_IDENTITY)
resolve_point_source(device_identity android_adapter.cpp SRC_ANDROID_ADAPTER)
resolve_point_source(environment_memory environment_memory.cpp SRC_ENVIRONMENT)
resolve_point_source(environment_memory input_methods_jni.cpp SRC_INPUT_METHODS)
resolve_point_source(proc_fd_clock_mcp mcp_chain.cpp SRC_MCP_CHAIN)
resolve_point_source(proc_fd_clock_mcp clock_chain.cpp SRC_CLOCK_CHAIN)
resolve_point_source(proc_fd_clock_mcp crypto.cpp SRC_CLOCK_CRYPTO)

add_library(prismsun_reconstruction SHARED
  ${SRC_HELPERS}
  ${SRC_FILTER}
  ${SRC_RING}
  ${SRC_PROBE}
  ${SRC_ACCESSIBILITY_CORE}
  ${SRC_ACCESSIBILITY_JNI}
  ${SRC_ACCESSIBILITY_ENV}
  ${SRC_ACCESSIBILITY_MONITOR}
  ${SRC_IDENTITY_CRYPTO}
  ${SRC_IDENTITY}
  ${SRC_ANDROID_ADAPTER}
  ${SRC_ENVIRONMENT}
  ${SRC_INPUT_METHODS}
  ${SRC_MCP_CHAIN}
  ${SRC_CLOCK_CHAIN}
  ${SRC_CLOCK_CRYPTO}
  ${SRC_JNI_LAYOUT}
)

target_compile_features(prismsun_reconstruction PRIVATE cxx_std_17)
target_compile_options(prismsun_reconstruction PRIVATE -Wall -Wextra -Werror)
target_include_directories(prismsun_reconstruction PRIVATE
  ../src
  ${DETECTION_POINT_ROOT}/aarch64_entry_classifier/src
  ${DETECTION_POINT_ROOT}/tracer_filter_policy/src
  ${DETECTION_POINT_ROOT}/shared_ring_reader/src
  ${DETECTION_POINT_ROOT}/jni_class_probe/src
  ${DIR_ACCESSIBILITY}
  ${DIR_DEVICE_IDENTITY}
  ${DIR_ENVIRONMENT}
  ${DIR_MCP_CLOCK}
)
target_link_libraries(prismsun_reconstruction PRIVATE dl)
set_target_properties(prismsun_reconstruction PROPERTIES
  OUTPUT_NAME prismsun_reconstruction
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
)
