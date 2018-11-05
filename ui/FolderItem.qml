import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.plasma.core 2.1 as PlasmaCore

Item {
	id: folder
	implicitWidth: 200
	implicitHeight: label.height + accountCount.height
	
	property alias color: icon.color
	property alias text: label.text
	property alias secondText: accountCount.text
	property int spacing: 8
	property bool hovered: false
	signal removeClicked

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
		anchors.left: icon.right
		anchors.leftMargin: spacing
		anchors.top: parent.top
		anchors.right: deleteBtn.left
	}

	SecondaryLabel {
		id: accountCount
		text: "Empty"
		anchors.left: label.left
		anchors.right: deleteBtn.left
		anchors.bottom: parent.bottom
	}
	
	Button {
		id: deleteBtn

		height: 32
		width: 32

		anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter

		flat: true
		visible: folder.hovered

		onClicked: removeClicked()
		
		PlasmaCore.IconItem {
			source: "edit-delete"
			
			width: 24
			height: width


			anchors.centerIn: parent
		}
	}
}
