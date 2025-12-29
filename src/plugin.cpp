#include <JuceHeader.h>
#include "editor.hpp"

#define DEFAULT_BUSES juce::AudioProcessor::BusesProperties() \
  .withInput("Input", juce::AudioChannelSet::stereo()) \
  .withOutput("Output", juce::AudioChannelSet::stereo()) \
  .withInput("Sidechain", juce::AudioChannelSet::stereo())

struct Plugin : juce::AudioProcessor
{
  Plugin() : AudioProcessor(DEFAULT_BUSES) {}

  void prepareToPlay(double, int) override {}
  void releaseResources() override {}

  bool isBusesLayoutSupported(const BusesLayout& layouts) const override
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

  void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override
  {
    juce::ScopedNoDenormals noDeNormals;
    buffer.clear();
  }

  juce::AudioProcessorEditor* createEditor() override
  {
    return new Editor(*this);
  }

  const juce::String getName() const override { return JucePlugin_Name; }
  bool acceptsMidi() const override { return true; }
  bool producesMidi() const override { return true; }
  bool isMidiEffect() const override { return false; }
  bool hasEditor() const override { return false; }
  double getTailLengthSeconds() const override { return 0.0; }
  int getNumPrograms() override { return 1; }
  int getCurrentProgram() override { return 0; }
  void setCurrentProgram(int) override {}
  const juce::String getProgramName(int) override { return {}; }
  void changeProgramName(int, const juce::String&) override {}
  void getStateInformation(juce::MemoryBlock&) override {}
  void setStateInformation(const void*, int) override {}
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new Plugin();
}
