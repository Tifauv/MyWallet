import QtQuick 2.9
import QtQuick.Window 2.2
import "../models"

Window {
	id: window
	visible: true
	width: 640
	height: 480
	title: qsTr("Hello World")

	WalletsModel {
		id: model
	}

	Sidebar {
		id: sidebar
		width: 180
		anchors.bottom: parent.bottom
		anchors.left: parent.left
		anchors.top: parent.top

		walletsModel: model
		onWalletSelected: loadWallet(index)

		onCreateWallet: console.log("Wallet creation requested.")
		onShowSettings: console.log("Settings page opening requested.")
	}

	WalletPage {
		id: walletPage
		anchors.left: sidebar.right
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom
	}

	// Autoselect the first wallet
	Component.onCompleted: loadWallet(0)


	/**
	 * Selects the wallet at the given index in the model.
	 * If the model is empty, or the index is outside [0, model.count[, nothing is done.
	 *
	 * @param index  the index of the wallet to select
	 */
	function loadWallet(index) {
		if (model.count > 0 && index >= 0 && index < model.count) {
			model.select(index);
			walletPage.wallet = model.get(index)
		}
	}
}
