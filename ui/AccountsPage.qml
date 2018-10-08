import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Wallets 1.0

Page {
	id: page

	implicitWidth: 440
	implicitHeight: 480

	property variant folder: undefined

	title: folder !== undefined ? folder.name : qsTr("Folder name")

	Clipboard {
		id: clipboard
	}

	footer: Pane {
		id: pane
		height: Math.max(accountCount.height, createBtn.height)
		padding: 8
		bottomPadding: 0
		topPadding: 0


		Label {
			id: accountCount
			verticalAlignment: Text.AlignVCenter
			anchors.left: parent.left

			text: adaptCount(folder !== undefined ? folder.count : 0)
			anchors.verticalCenter: parent.verticalCenter
		}

		ToolButton {
			id: createBtn
			height: 32
			anchors.verticalCenter: parent.verticalCenter
			anchors.right: parent.right

			text: qsTr("New Account...")
			flat: true

			visible: folder !== undefined

			onClicked: createAccountDlg.open()
		}
	}

	ListView {
		id: list

		anchors.fill: parent
		clip: true

		model: folder !== undefined ? folder : []

		delegate: SwipeDelegate {
			id: delegate
			width: parent.width
			hoverEnabled: true

			contentItem: AccountView {
				name: model.name
				login: model.login
			}

			highlighted: ListView.isCurrentItem
			onClicked: list.currentIndex = model.index

			onDoubleClicked: {
				console.log("Double click: copying password to clipboard")
				clipboard.setTextWithTimer(model.password, 10)
			}

			swipe.left: PasswordSwipeItem {
				width: parent.width
				height: parent.height

				clip: true
				bgColor: SwipeDelegate.pressed ? Material.color(Material.BlueGrey) : Material.color(Material.Blue)
				text: model.password
				textOpacity: 2 * delegate.swipe.position
				
				SwipeDelegate.onClicked: delegate.swipe.close()
			}

			swipe.right: RemovedSwipeItem {
				width: parent.width
				height: parent.height

				clip: true
				textOpacity: 2 * -delegate.swipe.position

				SwipeDelegate.onClicked: delegate.swipe.close()
				SwipeDelegate.onPressedChanged: undoTimer.stop()
			}

			Timer {
				id: hideTimer
				interval: 10000 // ms
				onTriggered: swipe.close()
			}

			Timer {
				id: undoTimer
				interval: 6000 // ms
				onTriggered: folder.deleteAccount(index)
			}

			swipe.onCompleted: {
				// Swipe to reveal password
				if (swipe.position == 1.0)
					hideTimer.start()

				// Swipe to delete
				if (swipe.position == -1.0)
					undoTimer.start()
			}
		}

		ScrollIndicator.vertical: ScrollIndicator {}
	}

	CreateAccountDialog {
		id: createAccountDlg

		modal: true
		focus: true

		width: 220
		height: 200

		x: (parent.width - width) / 2
		y: (parent.height - height) / 2

		onAccepted: {
			folder.createAccount(name, login, password);
			reset();
		}
		onRejected: reset()
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
