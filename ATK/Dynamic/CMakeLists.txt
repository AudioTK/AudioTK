
FILE(GLOB_RECURSE
  ATK_DYNAMIC_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  ATK_DYNAMIC_HEADERS
  *.h*
)

ATK_add_library(ATK_DYNAMIC
  NAME ATKDynamic
  FOLDER Dynamic
  LIBRARIES ATKCore
  SRC ${ATK_DYNAMIC_SRC}
  HEADERS ${ATK_DYNAMIC_HEADERS}
)
