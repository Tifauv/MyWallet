import QtQuick 2.4

Item {
	id: headerbar
	width: 440
	height: 48

	property alias title: title
	property alias secondary: secondary

	Rectangle {
		id: background
		color: "#fdf6e3"
		anchors.fill: parent
	}

	Text {
		id: title
		color: "#93a1a1"
		text: qsTr("Wallet name")
		anchors.top: parent.top
		anchors.topMargin: 4
		verticalAlignment: Text.AlignVCenter
		anchors.left: parent.left
		anchors.leftMargin: 8
		font.pixelSize: 18
	}

	Text {
		id: secondary
		color: "#839496"
		text: qsTr("n accounts")
		font.italic: true
		anchors.top: title.bottom
		anchors.topMargin: 0
		anchors.left: parent.left
		anchors.leftMargin: 12
		font.pixelSize: 10
	}
}
