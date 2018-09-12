import QtQuick 2.4
import "widgets"

SidebarForm {

	property var walletsModel: WalletsModel {}
	signal walletSelected(string name, int index)
	signal createWallet()
	signal showSettings()

	wallets.height: wallets.contentHeight
	wallets.model: walletsModel
	wallets.delegate: WalletButton {
		color: model.color
		name: model.name
		selected: model.selected
		anchors.left: parent.left
		anchors.right: parent.right
		onClicked: sidebar.walletSelected(name, model.index)
	}

	newWallet.onClicked: sidebar.createWallet()

	openSettings.onClicked: sidebar.showSettings()
}
