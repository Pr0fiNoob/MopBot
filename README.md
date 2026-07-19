# MopBot

MopBot ist ein experimenteller Bodenreinigungsroboter. Die Python-Software **MopSlothOS** läuft auf einem Raspberry Pi und übernimmt Navigation sowie die übergeordnete Steuerung. Über eine serielle Schnittstelle kommuniziert sie mit einem Arduino, dessen Firmware die Hardware ansteuert.

> **Projektstatus:** Frühphase. Das Repository enthält derzeit nur erste Grundlagen; Software, Firmware und die Elektronik werden schrittweise ergänzt.

## Ziele

- Den Roboter mit einer klaren Zustandsmaschine steuern.
- Eine zuverlässige und dokumentierte serielle Kommunikation zwischen Raspberry Pi und Arduino entwickeln.
- Eine sichere Grundlage für Antrieb, Sensoren und Reinigungsfunktion schaffen.
- Eine einfache Flächennavigation entwickeln, zunächst mit einem Schlangenlinienmuster.

## Konzept

Der Raspberry Pi trifft die übergeordneten Entscheidungen, etwa zur Navigation und zum aktuellen Betriebszustand. Er übermittelt passende Befehle an den Arduino. Die Arduino-Firmware steuert anschliessend die angebundene Hardware wie Motoren, Sensoren oder weitere Aktoren.

## Geplante Repository-Struktur

Die folgende Struktur beschreibt den Zielaufbau des Repositories. Bis alle Teile umgesetzt sind, können einzelne Ordner oder Dateien noch fehlen.

```text
MopBot/
├── .gitignore
├── LICENSE
├── README.md
├── AGENTS.md
├── CONTRIBUTING.md
├── python/
│
├── PCBs/
│   ├── Motor_Shield_v1/
│   │   └── ... KiCad-Projektdateien
│   └── ... weitere KiCad-Projekte
└── arduino-firmware/
    └── MopBot-firmware/
        └── MopBot-firmware.ino
