
FILE(GLOB_RECURSE
  ATK_SPECIAL_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  ATK_SPECIAL_HEADERS
  *.h*
)

ATK_add_library(ATK_SPECIAL
  NAME ATKSpecial
  FOLDER Special
  LIBRARIES ATKCore ATKUtility
  SRC ${ATK_SPECIAL_SRC}
  HEADERS ${ATK_SPECIAL_HEADERS}
)
