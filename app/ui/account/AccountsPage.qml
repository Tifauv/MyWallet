import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.4 as Kirigami

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Accounts")

	property alias model: list.model
	property variant createDlg
	readonly property alias selectedAccount: list.currentAccount
	readonly property alias selectedIndex: list.currentIndex

	mainAction: Kirigami.Action {
		text: qsTr("Create account")
		iconName: "list-add-user"
		shortcut: StandardKey.New
		onTriggered: {
			createDlg.open()
		}
	}

	mainItem: ListView {
		id: list

		clip: true

		property variant currentAccount: undefined

		delegate: Kirigami.AbstractListItem {
			id: delegate

			contentItem: AccountItem {
				id: accountItem
				name: model.name
				login: model.login
			}

			highlighted: ListView.isCurrentItem
			onHighlightedChanged: {
				list.currentAccount = model.account
			}
			onClicked: {
				list.currentIndex = model.index;
				list.currentAccount = model.account
			}
		}
	}
}
