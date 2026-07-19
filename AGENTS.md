## Geltungsbereich und Zweck

Diese Anweisungen gelten für das gesamte MopBot-Repository. MopSlothOS ist die Python-Software auf dem Raspberry Pi; sie kommuniziert über eine serielle Schnittstelle mit der Arduino-Firmware und übernimmt die übergeordnete Steuerung des Roboters.

Das Repository befindet sich in einer frühen Umsetzungsphase. Die geplante Ordnerstruktur ist ein Zielbild und keine bereits vollständige Schnittstelle.

## Freigabe für Repository-Änderungen

- Zeige vor jedem Commit oder Pull Request alle vorgeschlagenen Änderungen vollständig und hole eine ausdrückliche Freigabe der nutzenden Person ein.
- Führe ohne diese Freigabe weder `git add`, `git commit` noch `git push` aus und erstelle keinen Pull Request.
- Niemals Force-Pushes ausführen, Historie umschreiben, Branches löschen oder bestehende Änderungen verwerfen, ausser die nutzende Person verlangt genau diese Handlung ausdrücklich.

## Sprache

- Python-Code, Arduino-Code, Bezeichner, Kommentare, Docstrings, Log-Meldungen und Protokollfelder werden auf Englisch geschrieben.
- Repository-Dokumentation, insbesondere Markdown-Dateien, Anleitungen und Änderungsbeschreibungen, wird auf Deutsch geschrieben.

## Zielstruktur und Verantwortlichkeiten

- `python/MopSlothOS.py` ist der Einstiegspunkt für die Software auf dem Raspberry Pi.
- `python/utils/` enthält kleine, allgemein verwendbare Python-Hilfsfunktionen.
- `arduino-firmware/MopBot-firmware/MopBot-firmware.ino` enthält die Arduino-Firmware.
- `PCBs/` enthält die KiCad-Projekte; jedes Board hat einen eigenen Unterordner, zum Beispiel `PCBs/Motor_Shield_v1/`.

Halte Raspberry-Pi-Code, Arduino-Firmware und PCB-Dateien getrennt. Änderungen am seriellen Protokoll müssen auf beiden Softwareseiten abgestimmt und in der deutschen Dokumentation festgehalten werden.

## Arbeitsweise

1. Lies vor einer Änderung den relevanten Code und die passende Dokumentation.
2. Benenne jede Annahme, die Hardware-Verhalten, das serielle Protokoll oder eine öffentliche Schnittstelle beeinflusst.
3. Implementiere die kleinste zusammenhängende Änderung, welche die Anforderung erfüllt.
4. Führe die relevanten Prüfungen aus und berichte genau, was ausgeführt wurde, was bestanden hat und was nicht möglich war.
5. Aktualisiere die deutsche Dokumentation, wenn sich Verhalten, Konfiguration, Befehle oder Schnittstellen ändern.

## Code und Architektur

- Verwende explizite Imports; füge keine Wildcard-Imports hinzu.
- Bevorzuge für neuen Code Typannotationen, kleine Funktionen und verständliche Fehlerbehandlung.
- Neue Drittanbieter-Abhängigkeiten benötigen einen klaren Zweck und müssen dokumentiert werden.
- Halte Befehlsnamen, Einheiten, Zeitlimits und Protokollfelder explizit und nachvollziehbar.
- Bewahre bestehende Nutzeränderungen. Revertiere, formatiere oder benenne keine unabhängigen Dateien ohne Anlass um.

## Sicherheitsrelevantes Verhalten

- Der sichere Standardzustand ist ein gestoppter Roboter. Bei Start, Beenden, fehlerhaften Befehlen, Kommunikationsverlust oder unbehandelten Fehlern müssen Antriebs- und Aktorbefehle in einen sicheren Zustand übergehen.
- Validiere jede serielle Nachricht, bevor sie den Roboterzustand oder Hardware beeinflussen kann.
- Implementiere keine automatische Wiederaufnahme von Bewegung oder Reinigung nach einem Fehler ohne einen ausdrücklichen Befehl.
- Führe keine Hardwaretests aus und behaupte keine solchen Tests, sofern sie nicht ausdrücklich verlangt wurden und die Testbedingungen sowie eine Möglichkeit zum sicheren Anhalten bekannt sind.
- Halte Simulationen sowie Unit- und Protokolltests nach Möglichkeit unabhängig von physischer Hardware.

## Geheimnisse und Repository-Hygiene

- Niemals API-Schlüssel, Passwörter, Tokens, private Netzwerkadressen, Seriennummern oder personenbezogene Daten in versionierte Dateien schreiben.
- Beachte `.gitignore`; füge keine Caches, virtuellen Umgebungen, Logs, Backups oder grossen Binärdateien hinzu, ausser dies wurde ausdrücklich verlangt.

## Validierung

- Verwende vorhandene, im Repository dokumentierte Werkzeuge und Konfigurationen.
- Für Python- und Arduino-Code sind die jeweils verfügbaren Tests, Linter, Typprüfungen, Syntax- oder Kompilationsprüfungen auszuführen.
- Für KiCad-Projekte verwende die vorhandenen Prüfungen, wenn sie eingerichtet sind.
- Gibt es keine automatisierte Prüfung, führe die engste sichere Prüfung aus und nenne die Einschränkung klar, statt einen nicht erfolgten Test zu behaupten.