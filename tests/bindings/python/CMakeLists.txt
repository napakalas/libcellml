# Copyright libCellML Contributors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.cmake_minimum_required (VERSION 3.1)

set(TEST_SRCS
  test_component.py
  test_generator.py
  test_generator_profile.py
  test_import_source.py
  test_issue.py
  test_model.py
  test_parser.py
  test_printer.py
  test_reset.py
  test_units.py
  test_variable.py
  test_validator.py
  test_version.py
  test_docstrings.py
)

include(test_resources.cmake)

foreach(_TEST ${TEST_SRCS})
  configure_file(${_TEST} ${_TEST} COPYONLY)
  get_filename_component(_TEST_NAME ${_TEST} NAME_WE)
  set(_TEST_NAME python_${_TEST_NAME})
  add_test(NAME ${_TEST_NAME} COMMAND ${Python_EXECUTABLE} ${_TEST})
  if(WIN32)
    if(TARGET xml2)
      set(GEN_EXP_XML2_TARGET_FILE_DIR "\;\$<TARGET_FILE_DIR:xml2>")
    endif()
    if(NOT POLICY CMP0078)
      set(_PYTHON_MODULE_TARGET _entity)
	else()
      set(_PYTHON_MODULE_TARGET entity)
    endif()
    set_tests_properties(${_TEST_NAME} PROPERTIES
      ENVIRONMENT "PATH=$<TARGET_FILE_DIR:cellml>\;$<TARGET_FILE_DIR:${_PYTHON_MODULE_TARGET}>${GEN_EXP_XML2_TARGET_FILE_DIR}\;%PATH%;PYTHONPATH=${PROJECT_BINARY_DIR}/src/bindings/python/$<CONFIG>")
  else()
    set_tests_properties(${_TEST_NAME} PROPERTIES
      ENVIRONMENT "PYTHONPATH=${PROJECT_BINARY_DIR}/src/bindings/python")
  endif()
  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${_TEST}c
    ${CMAKE_CURRENT_BINARY_DIR}/${_TEST})
endforeach()

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/__pycache__)
