#!/bin/sh
$XGETTEXT $(find core -name '*.cpp' -o -name '*.h') $(find ui -name '*.qml' -o -name '*.js') $(ls . | grep -E '\.(cpp|h)$') -o $podir/wallets.pot
