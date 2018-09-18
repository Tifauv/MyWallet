import QtQuick 2.4
import QtQuick.Controls 2.2
import "widgets"

WalletPageForm {
	id: page
	property var wallet: undefined

	title: wallet !== undefined ? wallet.name : qsTr("Wallet name")
	countTxt.text: adaptCount(wallet !== undefined ? wallet.accounts.count : 0)
	accounts.model: wallet !== undefined ? wallet.accounts : []


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
