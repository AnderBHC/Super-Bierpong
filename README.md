# Super-Bierpong

DMX:
Für den DMX Modus den Schalter auf dem Deckel des gehäuses auf DMX Stellen.
Die Start Addresse wird im Quellcode gesetzt. DMXStart
Es werden 66 Kanäle Belegt. 3 Kanäle für jedes Becher feld und die Seitenstreifen in RGB.

Spielmodi:
Bierpong
Bierpong mit Regenbogen belechtung.
Kingscup: nur 1 Becher leuchtet auf. bis alle getroffen wurden.
Flipcup: nur die Seitenstreifen leuchten.

Beim Hochladen von neuer Software müssen die Pins RX und TX am arduino getrennt werden.
Es wird zusätzlich noch die Capacitive Sensor Bibliothek benötigt. https://github.com/PaulStoffregen/CapacitiveSensor
