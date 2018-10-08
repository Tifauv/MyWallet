import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
	id: control
	
	property double textOpacity
	
	Rectangle {
		id: background
		
		anchors.fill: parent
		color: Material.color(Material.DeepOrange)
	}
	
	Label {
		text: "\u25b6"

		padding: 20
		anchors.fill: parent
		horizontalAlignment: Qt.AlignRight
		verticalAlignment: Qt.AlignVCenter

		opacity: textOpacity
	}

	Label {
		text: qsTr("Removed")

		padding: 20
		anchors.fill: parent
		horizontalAlignment: Qt.AlignLeft
		verticalAlignment: Qt.AlignVCenter

		opacity: textOpacity
	}
}
