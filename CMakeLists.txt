################################################################################

file(STRINGS "VERSION" VERSION)

set(PLUGIN_NAME "Plugin")
set(BUNDLE_ID "com.company.product")
set(PLUGIN_CODE Autf)
set(VST3_PLUGIN_TYPE "Instrument")
set(AU_PLUGIN_TYPE "kAudioUnitType_MusicDevice")

set(PLUGIN_VERSION ${VERSION})
set(PLUGIN_MANUFACTURER_CODE Dmnd)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")

################################################################################

cmake_minimum_required(VERSION 3.22)

set(FORMATS "Standalone;VST3" CACHE STRING "Plugin formats for JUCE to build. Valid formats: VST AU AUv3 Standalone")
message("-- Building formats: ${FORMATS}")

project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION} LANGUAGES C CXX)

add_subdirectory(extern/JUCE)

juce_add_plugin(${PLUGIN_NAME}
  COMPANY_NAME "Company"
  BUNDLE_ID ${BUNDLE_ID} 
  PLUGIN_MANUFACTURER_CODE ${PLUGIN_MANUFACTURER_CODE}
  PLUGIN_CODE ${PLUGIN_CODE}
  FORMATS ${FORMATS}
  PRODUCT_NAME ${PLUGIN_NAME}
  EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD TRUE 
  VST3_CATEGORIES ${VST3_PLUGIN_TYPE}
  AU_MAIN_TYPE ${AU_PLUGIN_TYPE}
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
