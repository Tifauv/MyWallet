import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Drawer {
	id: sidebar

	property alias model: folderList.model
	property variant createDlg
	
	ListView {
		id: folderList

		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: newFolderBtn.top

		clip: true

		delegate: DrawerSwipeDelegate {
			id: delegate
			width: parent.width
			hoverEnabled: true

			contentItem: FolderItem {
				color: model.color
				text: model.name
				secondText: adaptCount(model.accounts.count)
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
				onTriggered: wallet.deleteFolder(index)
			}

			swipe.onCompleted: undoTimer.start()
		}

		ScrollIndicator.vertical: ScrollIndicator { }
	}

	ToolButton {
		id: newFolderBtn
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		height: 32

		text: qsTr("New Folder...")
		flat: true
		hoverEnabled: true

		onClicked: createDlg.open()
	}

	/**
	 * Adapts the accounts count to the number of elements in the folder.
	 */
	function adaptCount(count) {
		switch (count) {
		    case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(count)
		}
	}
}
