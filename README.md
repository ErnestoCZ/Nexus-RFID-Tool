# Nexus RFID Tool

Ein modulares System zum Lesen, Schreiben und Analysieren von RFID-Tags (MIFARE Classic). 
Das Projekt kombiniert eine Arduino-basierte Hardware-Shell mit einer grafischen Benutzeroberfläche in Qt.

## Architektur

Das Projekt ist als Monorepo strukturiert:
* **firmware/**: C++ Code für den Mikrocontroller (PlatformIO). Implementiert ein textbasiertes Shell-Interface über die serielle Schnittstelle.
* **gui/**: Desktop-Applikation in C++ (Qt 6). Bietet eine Hex-View und Steuerungsmöglichkeiten für die Firmware.

## Features

- **Serielle Shell**: Direkte Steuerung des RFID-Moduls über Textbefehle (z. B. `READ_BLOCK:4`).
- **Hex-View**: Tabellarische Darstellung der Karteninhalte inklusive ASCII-Vorschau.
- **Cross-Platform**: Die GUI ist dank Qt unter Windows, Linux und macOS lauffähig.
- **Hardware**: Optimiert für nRF5340 / Arduino mit RC522 RFID-Modul.

## Voraussetzungen

### Hardware
- Arduino
- MFRC522 RFID Reader/Writer
- MIFARE Classic Karten/Tags

### Software
- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO Extension](https://platformio.org/) (für die Firmware)
- [Qt 6.x SDK](https://www.qt.io/) & CMake (für die GUI)

## Installation & Build

### 1. Firmware (Arduino)
```bash
cd firmware
pio run --target upload