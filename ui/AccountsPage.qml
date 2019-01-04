import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Wallets 1.0
import "dialogs"

Page {
	id: page

	implicitWidth: 440
	implicitHeight: 480

	property variant folder: undefined
	property int hideTimeout: 10
	property int cancelDeleteTimeout: 8

	title: folder !== undefined ? folder.name : qsTr("Folder name")

	Clipboard {
		id: clipboard
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
				hovered: delegate.hovered

				onRevealClicked: delegate.swipe.open(-1.0)
				onRemoveClicked: delegate.swipe.open(1.0)
			}

			onDoubleClicked: {
				console.log("Double click: copying password to clipboard")
				clipboard.setTextWithTimer(model.password, 10)
			}

			swipe.right: PasswordSwipeItem {
				width: parent.width
				height: parent.height

				clip: true
				bgColor: SwipeDelegate.pressed ? Material.color(Material.BlueGrey) : Material.color(Material.Blue)
				text: model.password
				textOpacity: 2 * -delegate.swipe.position
				progress: hideTimer.remaining / hideTimer.interval
				
				SwipeDelegate.onClicked: delegate.swipe.close()
				SwipeDelegate.onPressedChanged: hideTimer.stop()
			}

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
				id: hideTimer
				interval: hideTimeout * 1000 // ms
				onTriggered: swipe.close()
			}

			TickingTimer {
				id: undoTimer
				interval: cancelDeleteTimeout * 1000 // ms
				onTriggered: folder.deleteAccount(index)
			}

			swipe.onCompleted: {
				// Swipe to reveal password
				if (swipe.position == -1.0)
					hideTimer.start()

				// Swipe to delete
				if (swipe.position == 1.0)
					undoTimer.start()
			}
		}

		ScrollIndicator.vertical: ScrollIndicator {}
	}

	RoundButton {
		id: createBtn
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 4
		anchors.right: parent.right
		anchors.rightMargin: 4

		hoverEnabled: true
		text: "+"

		visible: folder != undefined

		onClicked: createAccountDlg.open()
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
}
