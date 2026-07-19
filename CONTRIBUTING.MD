# Zu MopBot beitragen

Danke für dein Interesse an MopBot. Das Projekt befindet sich noch in einer frühen Entwicklungsphase. Kleine, klar abgegrenzte Beiträge helfen deshalb besonders.

## Bevor du beginnst

Bei grösseren Funktionen, Änderungen am seriellen Protokoll oder Änderungen mit Auswirkung auf die physische Hardware solltest du zuerst ein Issue eröffnen oder die Idee besprechen. So bleiben Software, Firmware und Elektronik aufeinander abgestimmt.

Geplante Teamaufgaben und Hardwareentscheide gelten erst als verbindlich, wenn sie im Repository dokumentiert sind.

## Sprache

- **Code wird auf Englisch geschrieben.** Das gilt für Dateinamen, Bezeichner, Kommentare, Docstrings, Log-Meldungen und Protokollfelder.
- **Dokumentation wird auf Deutsch geschrieben.** Das gilt insbesondere für Markdown-Dateien wie `README.md`, Anleitungen und Änderungsbeschreibungen.

## Empfohlener Ablauf

1. Wähle ein bestehendes Issue oder eröffne ein neues.
2. Erstelle einen beschreibenden Branch, zum Beispiel `feature/serial-protocol` oder `fix/stop-on-timeout`.
3. Beschränke die Änderung auf ein klar umrissenes Problem.
4. Ergänze oder aktualisiere Tests, wo dies sinnvoll ist, und passe die Dokumentation an, wenn sich Verhalten oder Schnittstellen ändern.
5. Erstelle einen Pull Request mit einer kurzen Beschreibung des Problems, der Lösung und der ausgeführten Tests. Beachte dabei die Freigaberegeln in [AGENTS.md](AGENTS.md).

## Richtlinien für Code und Dateien

- Lege Raspberry-Pi-Code unter `python/` ab; allgemeine Hilfsfunktionen gehören nach `python/utils/`.
- Die Arduino-Firmware gehört nach `arduino-firmware/MopBot-firmware/`.
- KiCad-Projekte gehören nach `PCBs/`; jedes Board erhält einen eigenen, aussagekräftigen Ordner.
- Verwende für neue Python- und Firmware-Funktionen klar benannte, kleine Einheiten mit nachvollziehbarer Fehlerbehandlung.
- Prüfe Daten aus der seriellen Verbindung vollständig. Ungültige, unvollständige oder abgelaufene Nachrichten dürfen keine unkontrollierte Roboterbewegung auslösen.
- Ändere ein serielles Protokoll nur zusammen mit der passenden Gegenstelle oder kennzeichne die Änderung klar als nicht kompatibel.
- Füge keine Zugangsdaten, API-Schlüssel, persönlichen Daten, lokalen Pfade oder generierten Dateien ins Repository ein.
- Neue Abhängigkeiten müssen notwendig sein und in der deutschen Dokumentation erwähnt werden.

## Tests

Automatisierte Tests werden mit der Umsetzung der Module ergänzt. Bis dahin gilt mindestens:

- Führe die vorhandenen Prüfungen für jede geänderte Datei aus.
- Teste Protokollverarbeitung und Zustandslogik nach Möglichkeit ohne angeschlossene physische Hardware.
- Gib im Pull Request an, welche Prüfungen liefen und welche nicht möglich waren.

Tests an Motoren, Pumpen oder anderen Aktoren müssen bewusst geplant und überwacht werden. Eine reine Codeänderung erfordert keinen Test mit dem physischen Roboter.

## Pull Requests

Ein Pull Request sollte leicht überprüfbar sein und Folgendes enthalten:

- Eine kurze Beschreibung der Änderung.
- Relevante Annahmen zu Protokoll, Konfiguration oder Hardware.
- Testergebnisse oder eine Begründung, weshalb ein Test nicht ausgeführt werden konnte.
- Aktualisierte deutsche Dokumentation, wenn sie für Nutzende oder Mitwirkende relevant ist.

Mit einem Beitrag erklärst du dich damit einverstanden, dass er unter der [MIT-Lizenz](LICENSE) dieses Repositories veröffentlicht werden darf.