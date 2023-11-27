include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(tiny_rpg_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(tiny_rpg_setup_options)
  option(tiny_rpg_ENABLE_HARDENING "Enable hardening" ON)
  option(tiny_rpg_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    tiny_rpg_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    tiny_rpg_ENABLE_HARDENING
    OFF)

  tiny_rpg_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR tiny_rpg_PACKAGING_MAINTAINER_MODE)
    option(tiny_rpg_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(tiny_rpg_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(tiny_rpg_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(tiny_rpg_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(tiny_rpg_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(tiny_rpg_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(tiny_rpg_ENABLE_PCH "Enable precompiled headers" OFF)
    option(tiny_rpg_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(tiny_rpg_ENABLE_IPO "Enable IPO/LTO" ON)
    option(tiny_rpg_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(tiny_rpg_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(tiny_rpg_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(tiny_rpg_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(tiny_rpg_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(tiny_rpg_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(tiny_rpg_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(tiny_rpg_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(tiny_rpg_ENABLE_PCH "Enable precompiled headers" OFF)
    option(tiny_rpg_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      tiny_rpg_ENABLE_IPO
      tiny_rpg_WARNINGS_AS_ERRORS
      tiny_rpg_ENABLE_USER_LINKER
      tiny_rpg_ENABLE_SANITIZER_ADDRESS
      tiny_rpg_ENABLE_SANITIZER_LEAK
      tiny_rpg_ENABLE_SANITIZER_UNDEFINED
      tiny_rpg_ENABLE_SANITIZER_THREAD
      tiny_rpg_ENABLE_SANITIZER_MEMORY
      tiny_rpg_ENABLE_UNITY_BUILD
      tiny_rpg_ENABLE_CLANG_TIDY
      tiny_rpg_ENABLE_CPPCHECK
      tiny_rpg_ENABLE_COVERAGE
      tiny_rpg_ENABLE_PCH
      tiny_rpg_ENABLE_CACHE)
  endif()

  tiny_rpg_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (tiny_rpg_ENABLE_SANITIZER_ADDRESS OR tiny_rpg_ENABLE_SANITIZER_THREAD OR tiny_rpg_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(tiny_rpg_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(tiny_rpg_global_options)
  if(tiny_rpg_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    tiny_rpg_enable_ipo()
  endif()

  tiny_rpg_supports_sanitizers()

  if(tiny_rpg_ENABLE_HARDENING AND tiny_rpg_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR tiny_rpg_ENABLE_SANITIZER_UNDEFINED
       OR tiny_rpg_ENABLE_SANITIZER_ADDRESS
       OR tiny_rpg_ENABLE_SANITIZER_THREAD
       OR tiny_rpg_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${tiny_rpg_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${tiny_rpg_ENABLE_SANITIZER_UNDEFINED}")
    tiny_rpg_enable_hardening(tiny_rpg_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(tiny_rpg_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(tiny_rpg_warnings INTERFACE)
  add_library(tiny_rpg_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  tiny_rpg_set_project_warnings(
    tiny_rpg_warnings
    ${tiny_rpg_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(tiny_rpg_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(tiny_rpg_options)
  endif()

  include(cmake/Sanitizers.cmake)
  tiny_rpg_enable_sanitizers(
    tiny_rpg_options
    ${tiny_rpg_ENABLE_SANITIZER_ADDRESS}
    ${tiny_rpg_ENABLE_SANITIZER_LEAK}
    ${tiny_rpg_ENABLE_SANITIZER_UNDEFINED}
    ${tiny_rpg_ENABLE_SANITIZER_THREAD}
    ${tiny_rpg_ENABLE_SANITIZER_MEMORY})

  set_target_properties(tiny_rpg_options PROPERTIES UNITY_BUILD ${tiny_rpg_ENABLE_UNITY_BUILD})

  if(tiny_rpg_ENABLE_PCH)
    target_precompile_headers(
      tiny_rpg_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(tiny_rpg_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    tiny_rpg_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(tiny_rpg_ENABLE_CLANG_TIDY)
    tiny_rpg_enable_clang_tidy(tiny_rpg_options ${tiny_rpg_WARNINGS_AS_ERRORS})
  endif()

  if(tiny_rpg_ENABLE_CPPCHECK)
    tiny_rpg_enable_cppcheck(${tiny_rpg_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(tiny_rpg_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    tiny_rpg_enable_coverage(tiny_rpg_options)
  endif()

  if(tiny_rpg_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(tiny_rpg_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(tiny_rpg_ENABLE_HARDENING AND NOT tiny_rpg_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR tiny_rpg_ENABLE_SANITIZER_UNDEFINED
       OR tiny_rpg_ENABLE_SANITIZER_ADDRESS
       OR tiny_rpg_ENABLE_SANITIZER_THREAD
       OR tiny_rpg_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    tiny_rpg_enable_hardening(tiny_rpg_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
