import QtQuick 2.4
import "widgets"

Item {
	width: 440
	height: 480

	property alias walletName: headerbar.mainTitle
	property alias accountsCount: headerbar.secondaryText
	property alias accounts: list

	Rectangle {
		id: background
		anchors.fill: parent
		color: "#eee8d5"
		border.width: 0

		PageHeader {
			id: headerbar
			height: 48
			anchors.top: parent.top
			anchors.right: parent.right
			anchors.left: parent.left
		}

		ListView {
			id: list
			clip: true
			anchors.top: headerbar.bottom
			anchors.right: parent.right
			anchors.left: parent.left
			anchors.bottom: parent.bottom

			delegate: AccountView {
				anchors.left: parent.left
				anchors.right: parent.right

				name: model.name
				login: model.login
			}
		}
	}
}
