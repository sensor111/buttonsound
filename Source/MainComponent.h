#pragma once

#include <JuceHeader.h>


class MySamplerVoice : public juce::SamplerVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<juce::SamplerSound*>(sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        if (auto* samplerSound = dynamic_cast<juce::SamplerSound*>(sound))
        {

        }
    }
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    void loadAudioFile(const juce::File& audioFile)
    {
        juce::AudioFormatManager formatManager;
        formatManager.registerBasicFormats();

        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(audioFile));

        if (reader)
        {
            juce::BigInteger notes2;
            notes2.setRange (1, 1, true);
            // Create a sampler sound and add it to the sampler
            auto sound = std::make_unique<juce::SamplerSound>("MySample", *reader, notes2, 60, 0.1, 0.1, 10.0);
            sampler.addSound(sound.release());
        }
        else
        {
            juce::Logger::writeToLog("Error loading audio file");
        }
    }

    juce::Synthesiser sampler;

    juce::TextButton button {"Click me!"};

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
