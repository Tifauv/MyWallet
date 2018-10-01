import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Drawer {
	id: sidebar

	property alias model: folderList.model
	property variant createDlg
	
	contentItem: ListView {
		id: folderList

		anchors.fill: parent
		clip: true

		delegate: DrawerSwipeDelegate {
			id: delegate
			width: parent.width
			hoverEnabled: true

			contentItem: FolderItem {
				color: model.color
				text: model.name
			}

			highlighted: ListView.isCurrentItem
			onClicked: {
				loadFolder(model.index)
				folderList.currentIndex = model.index
			}

			swipe.right: Rectangle {
				width: parent.width
				height: parent.height

				clip: true
				color: SwipeDelegate.pressed ? "#555" : "#666"

				Label {
					text: delegate.swipe.complete ? "\u2714" : "\u2718"

					padding: 20
					anchors.fill: parent
					horizontalAlignment: Qt.AlignRight
					verticalAlignment: Qt.AlignVCenter

					opacity: 2 * -delegate.swipe.position

					color: Material.color(delegate.swipe.complete ? Material.Green : Material.Red, Material.Shade200)
					Behavior on color { ColorAnimation { } }
				}

				Label {
					text: qsTr("Removed")

					padding: 20
					anchors.fill: parent
					horizontalAlignment: Qt.AlignLeft
					verticalAlignment: Qt.AlignVCenter

					opacity: delegate.swipe.complete ? 1 : 0
					Behavior on opacity { NumberAnimation { } }
				}

				SwipeDelegate.onClicked: delegate.swipe.close()
				SwipeDelegate.onPressedChanged: undoTimer.stop()
			}

			Timer {
				id: undoTimer
				interval: 3600
				onTriggered: wallet.removeFolder(index)
			}

			swipe.onCompleted: undoTimer.start()
		}

		ScrollIndicator.vertical: ScrollIndicator { }
	}

	RoundButton {
		id: newFolderBtn
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 4
		anchors.horizontalCenter: parent.horizontalCenter

		hoverEnabled: true
		text: "+"

		onClicked: createDlg.open()
	}
}
