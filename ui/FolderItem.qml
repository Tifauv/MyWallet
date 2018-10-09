import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
	implicitWidth: 200
	implicitHeight: label.height
	property alias color: icon.color
	property alias text: label.text
	property alias secondText: accountCount.text
	property int padding: 4
	property int spacing: 10

	Rectangle {
		id: icon
		width: height
		radius: 4
		anchors.bottom: label.bottom
		anchors.top: label.top
		border.width: 0
		anchors.left: parent.left
		anchors.leftMargin: padding
	}

	Label {
		id: label
		text: "Folder name"
		verticalAlignment: Text.AlignVCenter
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: icon.right
		anchors.leftMargin: spacing
	}

	SecondaryLabel {
		id: accountCount
		text: "Empty"
		horizontalAlignment: Text.AlignRight
		verticalAlignment: Text.AlignVCenter
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: label.right
		anchors.right: parent.right
		anchors.rightMargin: padding
	}
}
