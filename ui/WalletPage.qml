import QtQuick 2.4
import "widgets"

WalletPageForm {

	property var wallet: undefined

	walletName: wallet !== undefined ? wallet.name : "Sample wallet"
	accountsCount: qsTr("%1 accounts").arg(wallet !== undefined ? wallet.accounts.count : 0)
	accounts.model: wallet !== undefined ? wallet.accounts : []
}
