import QtQuick 2.4
import QtQuick.Controls 2.2

ToolBar {
	id: headerbar
	width: 440
	height: optionsBtn.implicitHeight
	background: Rectangle {
		color: "#eee8d5"
	}

	property alias title: titleTxt
	property alias button: optionsBtn

	Text {
		id: titleTxt
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

	ToolButton {
		id: optionsBtn
		anchors.right: parent.right
		text: "\u2630"
		anchors.verticalCenter: parent.verticalCenter
		font.pixelSize: Qt.application.font.pixelSize * 1.6
	}
}
