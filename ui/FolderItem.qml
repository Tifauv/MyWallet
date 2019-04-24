import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.plasma.core 2.1 as PlasmaCore
import org.kde.kirigami 2.4 as Kirigami

Item {
	id: folder
	implicitWidth: 200
	implicitHeight: label.height + accountCount.height
	
	property alias color: icon.color
	property alias text: label.text
	property alias secondText: accountCount.text
	property int spacing: 8

	Rectangle {
		id: icon
		width: Kirigami.Units.iconSizes.medium
		height: width
		radius: width / 2
		anchors.verticalCenter: parent.verticalCenter
		border.width: 0
		anchors.left: parent.left
		
		Label {
			id: initial
			
			text: label.text.charAt(0).toUpperCase() + label.text.charAt(1).toLowerCase()
			color: Qt.lighter(icon.color, 1.6)
			
			font.pointSize: 12
			font.bold: true
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			anchors.fill: parent
		}
	}

	Label {
		id: label
		text: qsTr("Folder name")
		anchors.left: icon.right
		anchors.leftMargin: spacing
		anchors.top: parent.top
		anchors.right: parent.right
	}

	SecondaryLabel {
		id: accountCount
		text: qsTr("Empty")
		anchors.left: label.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
	}
}
