#include "v3test.h"

#include <gtest/gtest.h>

/*
# Für QT5-Entwicklung unter ubuntu muss mind. noch
#    qt5-base-dev bzw. qt5base-dev
# nachinstalliert werden
#
--------------

# Einstellung für das Extra-Terminal befinden sich im QtCreator
#  1) links auf "Projekte" -> "Ausführen" -> "In Terminal starten"
#  2) falls sich das Terminal nicht öffnet, dann
#     im Menü "Extras" -> "Einstellungen" -> "Umgebung" -> "System" -> "Terminal"
#     das korrekt Terminalprogramm auswählen (z. B. /bin/gnome-terminal)
#     Standard ist der Terminal-Emulator, der unter Ubuntu/Debian Probleme macht.

--------------

# Die benötigten Quelldateien werden in CMakeLists.txt festgelegt

set(PROJECT_SOURCES
        bohrung.h bohrung.cpp telement.h ikomponente.h ikomponente.cpp
        fraesung.h fraesung.cpp
        deList.h iterator.h deList_impl.h iterator_impl.h
        serializer.h serializer.cpp
        komponente.h komponente.cpp
        werkstueck.h werkstueck.cpp
)

Sollten Sie bestimmte cpp-Dateien für Ihre Implementierung nicht benötigen, dann können
Sie diese dort entfernen.
Beachten Sie hier auch die Groß-/Kleinschreibung der Dateinamen. (z. B. deList.h, ...)
--------------

Das googletest-Verzeichnis wird hier ebenfalls in CMakeLists.txt festgelegt (s. ~ Zeile 50)

set(GOOGLETEST_DIR "/usr/src/googletest")

Prüfen Sie zunächst, ob googletest in diesem Verzeichnis installiert wurde.
Alternativverzeichnisse sind "/usr/local/src/googletest" oder "/opt/googletest"

 */
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
