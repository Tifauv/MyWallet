import QtQuick 2.4

Item {
	id: headerbar
	width: 440
	height: 32

	property alias title: title

	Rectangle {
		id: background
		color: "#eee8d5"
		anchors.fill: parent
	}

	Text {
		id: title
		color: "#657b83"
		text: qsTr("Title")
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 4
		anchors.top: parent.top
		anchors.topMargin: 4
		verticalAlignment: Text.AlignVCenter
		anchors.left: parent.left
		anchors.leftMargin: 8
		font.pixelSize: 14
	}
}
