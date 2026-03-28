#include "editor.hpp"

Editor::Editor(juce::AudioProcessor &proc)
  : AudioProcessorEditor(&proc)
{
  setSize(600, 600);
}

void Editor::paint(juce::Graphics &g)
{
  g.fillAll(juce::Colours::yellow);
}
