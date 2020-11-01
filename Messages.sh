#!/bin/sh
$XGETTEXT $(find core -name '*.cpp' -o -name '*.h') $(find app -name '*.cpp' -o -name '*.h' -o -name '*.qml' -o -name '*.js') -o $podir/wallets.pot
