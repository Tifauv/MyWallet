import QtQuick 2.9
import QtQuick.Controls 2.2
import Wallets 1.0

Page {
	id: page

	implicitWidth: 440
	implicitHeight: 480

	property var wallet: undefined

	title: wallet !== undefined ? wallet.name : qsTr("Wallet name")

	Clipboard {
		id: clipboard
	}

	footer: Pane {
		height: accountCount.implicitHeight + topPadding + bottomPadding

		topPadding: 4
		bottomPadding: 4
		leftPadding: 8

		Label {
			id: accountCount
			verticalAlignment: Text.AlignVCenter
			anchors.left: parent.left

			text: adaptCount(wallet !== undefined ? wallet.accounts.count : 0)
		}
	}

	ListView {
		id: list
		clip: true
		anchors.fill: parent

		model: wallet !== undefined ? wallet.accounts : []

		delegate: ItemDelegate {
			id: accountDelegate
			width: parent.width
			hoverEnabled: true

			contentItem: AccountView {
				name: model.name
				login: model.login
				hovered: accountDelegate.hovered

				onDeleted: console.log("Asked to delete account '" + model.name + "' from wallet '" + wallet.name + "'")
			}

			onDoubleClicked: clipboard.setTextWithTimer(model.password, 10)
		}
	}

	/**
	 * Adapts the accounts count to the number of elements in the wallet.
	 */
	function adaptCount(count) {
		switch (count) {
		    case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(count)
		}
	}
}
