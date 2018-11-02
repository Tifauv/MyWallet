import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
	id: control
	
	property string text
	property double textOpacity
	property color  bgColor: Material.color(Material.Blue)
	property double progress: 1.0
	
	Rectangle {
		id: background
		anchors.fill: parent
		color: bgColor
	}
	
	Label {
		id: passwordLbl

		text: control.text
		
		padding: 20
		anchors.fill: parent
		horizontalAlignment: Qt.AlignCenter
		verticalAlignment: Qt.AlignVCenter

		opacity: textOpacity
	}

	Rectangle {
		color: passwordLbl.color

		anchors.right: parent.right
		anchors.bottom: parent.bottom
		height: 4
		width: parent.width * progress
	}
}
