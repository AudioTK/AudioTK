
FILE(GLOB_RECURSE JUCE_MODULES_SRC JUCE/*.cpp JUCE/*.mm JUCE/*.h)

SOURCE_GROUP_BY_FOLDER(JUCE_MODULES)

add_custom_target(JUCE-modules SOURCES ${JUCE_MODULES_SRC})
