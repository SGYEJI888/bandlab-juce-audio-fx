🎛️ Real-Time Audio Effect Processor (Gain + Delay)

This is a real-time audio effect processor built with C++ and JUCE.
It applies both:
- 🎚️ **Gain control** (via slider)
- 🎧 **Echo / delay effect** (using circular buffer)

It is inspired by BandLab's creative workflow and aims to demonstrate practical audio DSP using JUCE.

---

## 🔧 How It Works (Technical Overview)

- A **circular buffer** stores past audio samples.
- We calculate:
  - `writePosition`: where new audio is stored
  - `readPosition`: where delayed audio is read from
- Final output = `(original + delayed * 0.5) * gain`

---

## 🛠️ Tech Stack
- C++
- JUCE Framework
- Visual Studio
- OBS (for recording the demo)
