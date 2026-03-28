#pragma once

#include <JuceHeader.h>

class Editor : public juce::AudioProcessorEditor
{
public:
  Editor(juce::AudioProcessor &proc);
  void paint(juce::Graphics& g) override;
};
