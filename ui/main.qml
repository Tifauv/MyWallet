import QtQuick 2.9
import QtQuick.Window 2.2

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

	/**
	 *
	 */
	function loadWallet(index) {
		model.select(index);
		walletPage.wallet = model.get(index)
	}
}
