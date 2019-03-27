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
		
		z: 2
		
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
		
		MouseArea {
			id: iconMouseArea
			anchors.fill: parent
			hoverEnabled: true
		}
	}

	Label {
		id: label
		text: "Folder name"
		anchors.left: icon.right
		anchors.leftMargin: spacing
		anchors.top: parent.top
		anchors.right: parent.right
	}

	SecondaryLabel {
		id: accountCount
		text: "Empty"
		anchors.left: label.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
	}
	
	Rectangle {
		id: actionPanel
		
		z: 1
		color: Qt.darker(folder.color, 1.6)
		
		height: folder.height + 2*8
		clip: true
		width: folder.width + 2*16
		
		y: 0      -8
		x: -width -16
		
		Row {
			id: layout
			
			anchors.fill: parent
			anchors.leftMargin: 16+icon.width+4
			anchors.rightMargin: 4
			layoutDirection: Qt.RightToLeft
			
			
			Button {
				id: deleteBtn
		
				height: 32
				width: 32
		
				anchors.verticalCenter: parent.verticalCenter
		
				flat: true
		
				onClicked: removeClicked()
				
				PlasmaCore.IconItem {
					source: "edit-delete"
					
					width: 24
					height: width
	
					anchors.centerIn: parent
				}
			}
		}
	}
	
	states: [
		State {
			name: "ShowActions"
			when: iconMouseArea.containsMouse || (folder.state === "ShowActions"  && folder.hovered)
			
			PropertyChanges {
				target: actionPanel
				x: 0 -16
			}
		}
	]
}
