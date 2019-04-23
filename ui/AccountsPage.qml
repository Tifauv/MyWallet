import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami
import Wallets 1.0

Kirigami.ScrollablePage {
	id: page
	title: model !== undefined ? "Accounts of " + model.name : "Accounts"

	property variant createDlg
	property alias model: list.model
	
	property int hideTimeout: 10
	property int cancelDeleteTimeout: 8

	mainAction: Kirigami.Action {
		text: "Create account"
		iconName: "document-new"
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
				onTriggered: page.model.deleteAccount(index)
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
		
		Clipboard {
			id: clipboard
		}
	}
}
