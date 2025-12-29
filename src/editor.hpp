#pragma once

struct Editor : juce::AudioProcessorEditor {
  Editor(juce::AudioProcessor& p) : AudioProcessorEditor(&p) {
    setSize(600, 600);
  }

  void paint(juce::Graphics& g) override {
    g.fillAll(juce::Colours::yellow);
  }
};
