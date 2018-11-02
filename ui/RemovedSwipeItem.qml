import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import org.kde.plasma.core 2.1 as PlasmaCore

Item {
	id: control
	
	property double textOpacity
	property double progress: 1.0

	Rectangle {
		id: background
		
		anchors.fill: parent
		color: Material.color(Material.DeepOrange)
	}


	PlasmaCore.IconItem {
		id: icon
		source: "dialog-cancel"

		anchors.left: parent.left
		anchors.leftMargin: 20
		anchors.top: parent.top
		anchors.bottom: parent.bottom

		opacity: textOpacity
	}

	Label {
		id: messageLbl

		text: qsTr("Cancel deletion")

		padding: 6
		anchors.left: icon.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.right: parent.right

		horizontalAlignment: Qt.AlignLeft
		verticalAlignment: Qt.AlignVCenter

		opacity: textOpacity
	}

	Rectangle {
		color: messageLbl.color

		anchors.left: parent.left
		anchors.bottom: parent.bottom
		height: 4
		width: parent.width * (1 - progress)
	}
}
