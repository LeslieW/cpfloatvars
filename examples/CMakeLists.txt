
include_directories(${CPFloatVars_SOURCE_DIR})

set(SRC_FILES)
macro(build_examples)
  set(TARGET_NAMES ${ARGV})
  foreach(value ${TARGET_NAMES})
    add_executable(${value} "${value}.cpp")
    if(BUILD_SHARED_LIB)
      target_link_libraries(${value} float ${GECODE_LIBRARY})
    else(BUILD_STATIC_LIB)
      target_link_libraries(${value} float-static ${GECODE_LIBRARY})
    endif(BUILD_SHARED_LIB)
		if (GECODE_GIST)
			target_link_libraries(${value} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY})
		endif()
    list(APPEND SRC_FILES "${value}.cpp")
  endforeach(value ${TARGET_NAMES})
endmacro(build_examples)

set(EX_SRCS clone )
build_examples(${EX_SRCS})

install(TARGETS ${EX_SRCS}
  RUNTIME
  DESTINATION bin/cpfloat-examples
  COMPONENT examples)

