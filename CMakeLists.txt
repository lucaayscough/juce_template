################################################################################

file(STRINGS "VERSION" VERSION)

set(PLUGIN_NAME "Plugin")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")

################################################################################

cmake_minimum_required(VERSION 3.22)

option(ASAN "Enable the Address Sanitizer" OFF)
if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif()

option(TSAN "Enable the Thread Sanitizer" OFF)
if (TSAN)
  if (ASAN)
    message("Skipping thread sanitizer. Turn off the address sanitizer if you want to use the thread sanitizer.")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=thread")
  endif()
endif()

set(FORMATS "Standalone;VST3" CACHE STRING "Plugin formats for JUCE to build. Valid formats: VST AU AUv3 Standalone")

message("-- Building formats: ${FORMATS}")

project(${PLUGIN_NAME} VERSION ${VERSION} LANGUAGES C CXX)

add_subdirectory(extern/JUCE)

juce_add_plugin(${PLUGIN_NAME}
  COMPANY_NAME "Company"
  BUNDLE_ID "com.company.product" 
  PLUGIN_MANUFACTURER_CODE Manf 
  PLUGIN_CODE Plug
  FORMATS ${FORMATS}
  PRODUCT_NAME ${PLUGIN_NAME}
  EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD TRUE 
  VST3_CATEGORIES "Fx" 
  AU_MAIN_TYPE "kAudioUnitType_Effect"
  MICROPHONE_PERMISSION_ENABLED FALSE 
  NEEDS_MIDI_INPUT TRUE
  NEEDS_MIDI_OUTPUT TRUE 
  IS_MIDI_EFFECT FALSE)

juce_generate_juce_header(${PLUGIN_NAME})

#juce_add_binary_data(Assets SOURCES)

target_sources(${PLUGIN_NAME} PRIVATE src/plugin.cpp)

target_compile_definitions(${PLUGIN_NAME} PUBLIC
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PLUGIN_NAME} PRIVATE
  #Assets
  juce::juce_audio_utils
  juce::juce_audio_devices
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags)
