#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

struct Editor : juce::AudioProcessorEditor {
  explicit Editor(juce::AudioProcessor&);

  void paint(juce::Graphics&) override;
};

Editor::Editor(juce::AudioProcessor& p) : AudioProcessorEditor(&p) {
  setSize(600, 600);
}

void Editor::paint(juce::Graphics& g) {
  g.fillAll(juce::Colours::yellow);
}
