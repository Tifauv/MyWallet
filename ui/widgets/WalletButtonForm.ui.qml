import QtQuick 2.4

Item {
	id: button
	width: 200
	height: 32

	property alias background: background
	property alias icon: colorIcon
	property alias label: textLabel
	property alias button: mouseArea

	Rectangle {
		id: background
		color: "transparent"
		anchors.fill: parent
	}

	Rectangle {
		id: colorIcon
		width: 16
		height: 16
		radius: 4
		border.width: 0
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 8
		anchors.top: parent.top
		anchors.topMargin: 8
		anchors.left: parent.left
		anchors.leftMargin: 8
	}

	Text {
		id: textLabel
		color: "#839496"
		text: "Wallet name"
		styleColor: "#839496"
		font.pointSize: 10
		verticalAlignment: Text.AlignVCenter
		anchors.left: colorIcon.right
		anchors.leftMargin: 10
		anchors.right: parent.right
		anchors.rightMargin: 8
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 8
		anchors.top: parent.top
		anchors.topMargin: 8
	}

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true
	}
}
