import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
	id: control
	
	property string text
	property double textOpacity
	property color  bgColor: Material.color(Material.Blue)
	
	Rectangle {
		id: background
		anchors.fill: parent
		color: bgColor
	}
	
	Label {
		text: control.text
		
		padding: 20
		anchors.fill: parent
		horizontalAlignment: Qt.AlignLeft
		verticalAlignment: Qt.AlignVCenter

		opacity: textOpacity
	}
}
