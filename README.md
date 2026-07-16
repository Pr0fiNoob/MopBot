# MopBot

## MopSlothOS – Python-Teil

MopSlothOS ist der Python-Teil des MopBots. Er soll später die übergeordnete
Steuerung und Navigation übernehmen und über eine serielle Schnittstelle mit
dem Arduino kommunizieren.

Aktuell ist nur die grundlegende Datei- und Ordnerstruktur angelegt. Die
einzelnen Module werden im weiteren Projektverlauf implementiert.

```text
mopsloth/
├── app.py
├── communication/
│   ├── protocol.py
│   └── serial_link.py
├── control/
│   ├── safety.py
│   └── state_machine.py
├── navigation/
│   ├── odometry.py
│   └── serpentine.py
└── robot/
    ├── drive_base.py
    └── sensors.py
```

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz. Siehe [LICENSE](LICENSE).
