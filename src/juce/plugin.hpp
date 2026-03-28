#include <JuceHeader.h>

struct Plugin : juce::AudioProcessor
{
  Plugin();
  void prepareToPlay(double sampleRate, int blockSize) override;
  void releaseResources() override;
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
  void processBlock(juce::AudioBuffer<float> &audio, juce::MidiBuffer &midi) override;
  juce::AudioProcessorEditor* createEditor() override;
  const juce::String getName() const override;
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  bool hasEditor() const override;
  double getTailLengthSeconds() const override;
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &name) override;
  void getStateInformation(juce::MemoryBlock &mb) override;
  void setStateInformation(const void* data, int dataSize) override;
};
