
FILE(GLOB
  ATK_CORE_TEST_SRC
  *.cpp
)

FILE(GLOB
  ATK_CORE_TEST_HEADERS
  *.h*
)

ATK_add_test(ATK_CORE_TEST
  NAME ATKCore_test
  FOLDER Core_test
  TESTNAME Core
  LIBRARIES ATKTools ATKMock ATKCore ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  SRC ${ATK_CORE_TEST_SRC}
  HEADERS ${ATK_CORE_TEST_HEADERS}
)
