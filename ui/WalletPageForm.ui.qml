import QtQuick 2.4
import QtQuick.Controls 2.2
import "widgets"

Page {
	id: page
	width: 440
	height: 480
	title: qsTr("Wallet")

	property alias countTxt: accountCount

	footer: Rectangle {
		height: 24
		color: "#eee8d5"

		Label {
			id: accountCount
			text: qsTr("n accounts")
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 4
			anchors.top: parent.top
			anchors.topMargin: 4
			verticalAlignment: Text.AlignVCenter
			anchors.left: parent.left
			anchors.leftMargin: 8
		}
	}

	property alias accounts: list

	ListView {
		id: list
		clip: true
		anchors.fill: parent
		delegate: ItemDelegate {
			width: parent.width

			contentItem: AccountView {
				name: model.name
				login: model.login
			}
		}
	}
}
