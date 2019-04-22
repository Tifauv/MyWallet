import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami
import Wallets 1.0

Kirigami.ScrollablePage {
	title: "Folders"

	property alias model: list.model
	property variant createDlg
	property variant selectedFolder: wallet.get(list.currentIndex)

	mainAction: Kirigami.Action {
		text: "Create folder"
		iconName: "edit"
		onTriggered: {
			createDlg.open()
		}
	}

	mainItem: ListView {
		id: list

		clip: true

		delegate: SwipeDelegate {
			id: delegate
			width: parent.width
			hoverEnabled: true

			contentItem: FolderItem {
				color: model.color
				text: model.name
				secondText: adaptCount(model.accounts.count)
				hovered: delegate.hovered
				
				onRemoveClicked: delegate.swipe.open(1.0)
			}

			highlighted: ListView.isCurrentItem
			onClicked: list.currentIndex = model.index

			swipe.left: RemovedSwipeItem {
				width: parent.width
				height: parent.height

				clip: true
				textOpacity: 2 * delegate.swipe.position
				progress: undoTimer.remaining / undoTimer.interval

				SwipeDelegate.onClicked: delegate.swipe.close()
				SwipeDelegate.onPressedChanged: undoTimer.stop()
			}

			TickingTimer {
				id: undoTimer
				interval: 8 * 1000 // ms
				onTriggered: wallet.deleteFolder(index)
			}

			swipe.onCompleted: undoTimer.start()
		}
	}


	/**
	 * Adapts the accounts count to the number of elements in the folder.
	 */
	function adaptCount(p_count) {
		switch (p_count) {
			case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(p_count)
		}
	}
}
