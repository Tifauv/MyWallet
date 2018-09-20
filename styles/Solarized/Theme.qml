import QtQuick 2.9

pragma Singleton

QtObject {
	id: theme

	// Base colors
	property color base03: "#002b36"
	property color base02: "#073642"
	property color base01: "#586e75"
	property color base00: "#657b83"
	property color base0 : "#839496"
	property color base1 : "#93a1a1"
	property color base2 : "#eee8d5"
	property color base3 : "#fdf6e3"
	// Accent colors
	property color yellow : "#b58900"
	property color orange : "#cb4b16"
	property color red    : "#dc322f"
	property color magenta: "#d33682"
	property color violet : "#6c71c4"
	property color blue   : "#268bd2"
	property color cyan   : "#2aa198"
	property color green  : "#859900"

	// Dark variant
	property color darkBackgroundColor: base03
	property color darkBackgroundAccentColor: base02
	property color darkContentSecondaryColor: base01
	property color darkContentPrimaryColor: base0
	property color darkContentEmphasizedColor: base1

	// Light variant
	property color lightBackgroundColor: base3
	property color lightBackgroundAccentColor: base2
	property color lightContentSecondaryColor: base1
	property color lightContentPrimaryColor: base00
	property color lightContentEmphasizedColor: base01
}
