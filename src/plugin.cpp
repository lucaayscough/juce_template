#include "plugin.hpp"

#define DEFAULT_BUSES juce::AudioProcessor::BusesProperties() \
  .withInput("Input", juce::AudioChannelSet::stereo()) \
  .withOutput("Output", juce::AudioChannelSet::stereo()) \
  .withInput("Sidechain", juce::AudioChannelSet::stereo())

Plugin::Plugin() : AudioProcessor(DEFAULT_BUSES) {}

void Plugin::prepareToPlay(double, int) {}

void Plugin::releaseResources() {}

void Plugin::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
  juce::ScopedNoDenormals noDeNormals;

  buffer.clear();
}

bool Plugin::isBusesLayoutSupported(const BusesLayout& layouts) const {
  auto outputLayout = layouts.getMainOutputChannelSet();

  std::vector<juce::AudioChannelSet> supportedLayouts = {
    juce::AudioChannelSet::stereo(),
  };

  for (auto& layout : supportedLayouts) {
    if (outputLayout == layout)
      return true;
  }

  return false;
}

const juce::String Plugin::getName() const { return JucePlugin_Name; }

bool Plugin::acceptsMidi()  const { return true; }
bool Plugin::producesMidi() const { return true; }
bool Plugin::isMidiEffect() const { return false; }
bool Plugin::hasEditor()    const { return false; }

juce::AudioProcessorEditor* Plugin::createEditor() {
  return new Editor(*this);
}

void Plugin::getStateInformation(juce::MemoryBlock&) {}
void Plugin::setStateInformation(const void*, int) {}

double  Plugin::getTailLengthSeconds() const      { return 0.0; }
int     Plugin::getNumPrograms()                  { return 1; }
int     Plugin::getCurrentProgram()               { return 0; }
void    Plugin::setCurrentProgram(int)            {}
const   juce::String Plugin::getProgramName(int)  { return {}; }
void    Plugin::changeProgramName(int, const juce::String&) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new Plugin();
}

#undef DEFAULT_BUSES
