# Sign Language to Speech Glove 🤖🧤🔊

This Arduino-based project converts sign language gestures into speech using flex sensors and a DFPlayer Mini audio module. It is designed to assist individuals with hearing or speech impairments by providing an accessible, offline communication tool.

## 👨‍💻 Project Description

- **Microcontroller**: Arduino (Uno/Nano)
- **Sensors**: 5x Flex Sensors (connected to A0–A4)
- **Audio Output**: DFPlayer Mini with microSD card and speaker
- **Communication**: Offline, no internet required
- **Libraries Used**:
  - `SoftwareSerial.h`
  - `DFRobotDFPlayerMini.h`

Each finger is mapped to a specific audio track that plays when the finger is bent beyond a calibrated threshold.

## 🛠️ Features

- Calibrates baseline values for flex sensors at startup
- Detects bending of each finger individually
- Plays pre-recorded audio clips corresponding to each gesture
- Ignores further input while audio is playing
- Displays readings and threshold status in Serial Monitor

## 📁 Files

- `sign_language_glove.ino` — Main Arduino sketch
- `README.md` — Project description
- (Optional) Audio files (`001.mp3`, `002.mp3`, ...) on SD card

## 🙋 Contributors

- 👨‍💻 [Yash Chaudhari](https://github.com/progyash) — Core Developer & Hardware Integration

- 🔧 [Satyveer Chauhan](https://github.com/satyveer2005) — Flex Sensor Calibration & Testing

- 🎨 [Ahad Bhati](https://github.com/AhadBhati1) — Audio Design & Documentation

## 📷 Preview

https://github.com/user-attachments/assets/48899d36-0059-4ba8-b01e-8baca9b4ccf3

## 📝 License

MIT License. Feel free to use, modify, and share.

---

### 📣 Note

Make sure your SD card contains audio files named in `001.mp3`, `002.mp3`, ..., `005.mp3` format corresponding to each finger.
