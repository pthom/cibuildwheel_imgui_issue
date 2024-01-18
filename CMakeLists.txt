cmake_minimum_required(VERSION 3.17)

project(cibuildwheel_abi_study VERSION "0.0.1")
set(CMAKE_CXX_STANDARD 20)

####################################################
# Add pybind11
####################################################
# if pybind11 is installed via pip, then add its path to CMAKE_PREFIX_PATH
function(_lg_add_pybind11_pip_cmake_prefix_path)
    if(NOT DEFINED PYTHON_EXECUTABLE)
        find_package(Python3)
        if (NOT Python3_FOUND)
            message(FATAL_ERROR "Python3 not found")
        endif()
        set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
    endif()
    execute_process(
        COMMAND "${PYTHON_EXECUTABLE}" -c
        "import pybind11; print(pybind11.get_cmake_dir())"
        OUTPUT_VARIABLE pybind11_cmake_dir
        OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT
        RESULT_VARIABLE _result
    )
    if(NOT _result EQUAL 0)
        message(FATAL_ERROR "
            Make sure pybind11 is installed via pip:
                pip install pybind11
            Also, make sure you are using the correct python executable:
                -DPYTHON_EXECUTABLE=/path/to/your/venv/bin/python
        ")
    endif()
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${pybind11_cmake_dir}" PARENT_SCOPE)
endfunction()


if(SKBUILD)
    _lg_add_pybind11_pip_cmake_prefix_path()
endif()
find_package(pybind11 CONFIG REQUIRED)


####################################################
# Build mylib
####################################################
add_library(mylib STATIC mylib.cpp mylib.h)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(mylib PRIVATE -fPIC)


#########################################################################
# Build python module that provides bindings to the library implot
#########################################################################
include(litgen_cmake/litgen_setup_module.cmake)


pybind11_add_module(_mylib bindings/module.cpp bindings/pybind_mylib.cpp)
target_compile_definitions(_mylib PRIVATE VERSION_INFO=${PROJECT_VERSION})
litgen_setup_module(mylib mylib)
