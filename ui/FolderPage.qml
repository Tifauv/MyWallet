import QtQuick 2.9
import QtQuick.Controls 2.2
import Wallets 1.0

Page {
	id: page

	implicitWidth: 440
	implicitHeight: 480

	property variant folder: undefined

	title: folder !== undefined ? folder.name : qsTr("Folder name")

	Clipboard {
		id: clipboard
	}

	footer: Pane {
		height: accountCount.implicitHeight + topPadding + bottomPadding

		topPadding: 4
		bottomPadding: 4
		leftPadding: 8

		Label {
			id: accountCount
			verticalAlignment: Text.AlignVCenter
			anchors.left: parent.left

			text: adaptCount(folder !== undefined ? folder.count : 0)
		}
	}

	ListView {
		id: list
		anchors.fill: parent
		clip: true

		model: folder !== undefined ? folder : []

		delegate: ItemDelegate {
			id: accountDelegate
			width: parent.width
			hoverEnabled: true

			contentItem: AccountView {
				name: model.name
				login: model.login
				hovered: accountDelegate.hovered

				onDeleted: console.log("Asked to delete account '" + model.name + "' from folder '" + folder.name + "'")
			}

			highlighted: ListView.isCurrentItem
			onClicked: list.currentIndex = model.index

			onDoubleClicked: {
				console.log("Double click: copying password to clipboard")
				clipboard.setTextWithTimer(model.password, 10)
				/*console.log("Right click: copying login to clipboard")
				clipboard.setText(model.login)*/
			}
		}

		ScrollIndicator.vertical: ScrollIndicator {}
	}

	/**
	 * Adapts the accounts count to the number of elements in the folder.
	 */
	function adaptCount(count) {
		switch (count) {
		    case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(count)
		}
	}
}
