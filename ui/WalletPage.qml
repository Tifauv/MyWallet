import QtQuick 2.4
import "widgets"

WalletPageForm {
	property var wallet: undefined

	title: adaptTitle(wallet !== undefined ? wallet.accounts.count : 0)
	accounts.model: wallet !== undefined ? wallet.accounts : []

	menuButton.onClicked: console.log("Menu for wallet '" + wallet.name + "' requested.")

	function adaptTitle(count) {
		switch (count) {
		    case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(count)
		}
	}
}
