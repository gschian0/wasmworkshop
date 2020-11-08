#pragma once

#include "MidiSynth.h"
#include "Oscillator.h"
#include "ADSREnvelope.h"
#include "SawtoothOscillator.h"
#include "StateVariableFilter.h"


inline double midi2CPS(double pitch)
{
  return 440. * pow(2., (pitch - 69.) / 12.);
}

class MySynthVoice : public MidiSynth::Voice
{
public:  
  void Trigger(double level, bool isRetrigger) override
  {
    mEnv.Start(level);
  }

  void Release() override
  {
    mEnv.Release();
  }
  
  bool GetBusy() const override
  {
    return mEnv.GetBusy();
  }
  
  bool GetReleased() const override
  {
    return mEnv.GetReleased();
  }
  
  void ProcessSamples(sample** inputs, sample** outputs, int nInputs, int nOutputs, int startIdx, int nFrames, double pitchBend) override
  {
    // for each sample in this block, starting at startIdx
    for (auto s = startIdx; s < startIdx + nFrames; s++)
    {
      // generate 1 samples worth of audio
      sample y = mEnv.Process(mSustainLevel) * mOsc.Process(midi2CPS(mBasePitch + pitchBend));

      //sample y = mEnv.Process(mSustainLevel) * mSawToothOsc.Process(midi2CPS(mBasePitch + pitchBend), 44100.f);
      
      outputs[0][s] = outputs[0][s] + y; // accumulate the output of this voice into the
    }
  }

public:
  SawToothOscillator mSawToothOsc;
  FastSinOscillator<sample> mOsc;
  ADSREnvelope<sample> mEnv;
  SVF<sample> mFilter;
  sample mSustainLevel = 0.;
};
