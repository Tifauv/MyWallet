import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
	id: page
	implicitWidth: 440
	implicitHeight: 480
	title: qsTr("Wallet")

	property alias countTxt: accountCount
	property alias accounts: list

	footer: Pane {
		height: accountCount.implicitHeight + topPadding + bottomPadding

		topPadding: 4
		bottomPadding: 4
		leftPadding: 8

		Label {
			id: accountCount
			text: qsTr("n accounts")
			verticalAlignment: Text.AlignVCenter
			anchors.left: parent.left
		}
	}

	ListView {
		id: list
		clip: true
		anchors.fill: parent
		delegate: ItemDelegate {
			id: accountDelegate
			width: parent.width

			contentItem: AccountView {
				name: model.name
				login: model.login
				hovered: accountDelegate.hovered
			}
		}
	}
}
