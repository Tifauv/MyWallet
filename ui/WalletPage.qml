import QtQuick 2.4
import QtQuick.Controls 2.2
import "widgets"

WalletPageForm {
	id: page
	property var wallet: undefined

	title: adaptTitle(wallet !== undefined ? wallet.accounts.count : 0)
	accounts.model: wallet !== undefined ? wallet.accounts : []

	menuButton.onClicked: {
		console.log("Menu for wallet '" + wallet.name + "' requested.");
		pageDrawer.open()
	}

	Drawer {
		id: pageDrawer
		height: accounts.height
		width: page.width * 0.33
		edge: Qt.RightEdge
		y: header.height
	}

	/**
	 * Adapts the page title to the number of elements in the wallet.
	 */
	function adaptTitle(count) {
		switch (count) {
		    case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(count)
		}
	}
}
