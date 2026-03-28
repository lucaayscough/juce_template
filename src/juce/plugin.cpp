#include "editor.hpp"
#include "plugin.hpp"

#define DEFAULT_BUSES juce::AudioProcessor::BusesProperties() \
  .withInput("Input", juce::AudioChannelSet::stereo()) \
  .withOutput("Output", juce::AudioChannelSet::stereo()) \
  .withInput("Sidechain", juce::AudioChannelSet::stereo())

Plugin::Plugin() : AudioProcessor(DEFAULT_BUSES)
{
}

void Plugin::prepareToPlay(double sampleRate, int blockSize)
{
  (void)sampleRate;
  (void)blockSize;
}

void Plugin::releaseResources()
{
}

bool Plugin::isBusesLayoutSupported(const BusesLayout &layouts) const 
{
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

void Plugin::processBlock(juce::AudioBuffer<float> &audio, juce::MidiBuffer &midi) 
{
  juce::ScopedNoDenormals noDeNormals;
  audio.clear();
  (void)midi;
}

juce::AudioProcessorEditor* Plugin::createEditor() 
{
  return new Editor(*this);
}

const juce::String Plugin::getName() const
{
  return JucePlugin_Name;
}

bool Plugin::acceptsMidi() const
{
  return true;
}

bool Plugin::producesMidi() const
{
  return true;
}

bool Plugin::isMidiEffect() const
{
  return false;
}

bool Plugin::hasEditor() const
{
  return false;
}

double Plugin::getTailLengthSeconds() const
{
  return 0.0;
}

int Plugin::getNumPrograms()
{
  return 1;
}

int Plugin::getCurrentProgram()
{
  return 0;
}

void Plugin::setCurrentProgram(int index)
{
  (void)index;
}

const juce::String Plugin::getProgramName(int index)
{
  (void)index;
  return {};
}

void Plugin::changeProgramName(int index, const juce::String &name)
{
  (void)index;
  (void)name;
}

void Plugin::getStateInformation(juce::MemoryBlock &mb)
{
  (void)mb;
}

void Plugin::setStateInformation(const void *data, int dataSize)
{
  (void)data;
  (void)dataSize;
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new Plugin();
}
