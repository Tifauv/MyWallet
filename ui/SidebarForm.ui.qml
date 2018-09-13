import QtQuick 2.4
import QtQuick.Controls 2.2
import "widgets"

Item {
	id: sidebar
	width: 200
	height: 480

	property alias wallets: walletsList
	property alias newWallet: newWalletButton
	property alias openSettings: settingsButton

	Rectangle {
		id: background
		color: "#002b36"
		border.width: 0
		anchors.fill: parent
	}

	Text {
		id: title
		x: 8
		color: "#a57706"
		text: qsTr("Wallets")
		anchors.top: parent.top
		anchors.topMargin: 6
		font.letterSpacing: 2
		font.weight: Font.Thin
		anchors.right: parent.right
		anchors.rightMargin: 8
		anchors.left: parent.left
		anchors.leftMargin: 8
		font.pixelSize: 22
	}

	ListView {
		id: walletsList
		x: 8
		anchors.bottom: actions.top
		anchors.top: title.bottom
		spacing: 2
		anchors.right: parent.right
		anchors.left: parent.left
		clip: true
		model: WalletsModel {
		}
		delegate: WalletButton {
			color: model.color
			name: model.name
			selected: model.selected
			anchors.left: parent.left
			anchors.right: parent.right
		}
	}

	Row {
		id: actions
		height: 40
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.bottom: parent.bottom

		Button {
			id: newWalletButton
			width: parent.width / 2
			text: qsTr("New wallet")
			anchors.bottom: parent.bottom
			anchors.top: parent.top
		}

		Button {
			id: settingsButton
			width: parent.width / 2
			text: qsTr("Settings")
			anchors.top: parent.top
			anchors.bottom: parent.bottom
		}
	}
}
