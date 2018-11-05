import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
	id: item1
	implicitWidth: 200
	implicitHeight: label.height + accountCount.height
	property alias color: icon.color
	property alias text: label.text
	property alias secondText: accountCount.text
	property int spacing: 8

	Rectangle {
		id: icon
		width: height
		radius: height / 2
		anchors.top: label.top
		anchors.bottom: accountCount.bottom
		border.width: 0
		anchors.left: parent.left
		
		Label {
			id: initial
			
			text: label.text.charAt(0)
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
		text: "Folder name"
		anchors.bottom: accountCount.top
		anchors.bottomMargin: 0
		anchors.left: icon.right
		anchors.leftMargin: spacing
		anchors.top: parent.top
		anchors.right: parent.right
	}

	SecondaryLabel {
		id: accountCount
		text: "Empty"
		anchors.left: label.left
		//anchors.leftMargin: 12
		anchors.right: parent.right
		anchors.bottom: parent.bottom
	}
}
