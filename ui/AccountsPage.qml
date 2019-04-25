import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami
import Wallets 1.0

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Accounts")

	property variant createDlg
	property alias model: list.model
	
	signal copyPassword(string p_accountName, string p_password)
	signal edit(int p_index)
	signal confirmDelete(int p_index, string p_accountName)

	mainAction: Kirigami.Action {
		text: "Create account"
		iconName: "document-new"
		onTriggered: {
			createDlg.open()
		}
	}

	mainItem: ListView {
		id: list

		clip: true

		delegate: Kirigami.SwipeListItem {
			id: delegate

			separatorVisible: false
			backgroundColor: Kirigami.Theme.backgroundColor

			actions: [
				Kirigami.Action {
					text: accountItem.passwordVisible ? qsTr("Hide password") : qsTr("Show password")
					iconName: accountItem.passwordVisible ? "password-show-off" : "password-show-on"
					onTriggered: accountItem.passwordVisible = !accountItem.passwordVisible
				},
				Kirigami.Action {
					text: qsTr("Copy the password to the clipboard")
					iconName: "edit-copy"
					onTriggered: page.copyPassword(model.name, model.password)
				},
				Kirigami.Action {
					text: qsTr("Edit this account")
					iconName: "document-edit"
					onTriggered: page.edit(model.index)
				},
				Kirigami.Action {
					text: qsTr("Delete this account")
					iconName: "edit-delete"
					onTriggered: page.confirmDelete(model.index, model.name)
				}
			]
			
			contentItem: AccountItem {
				id: accountItem
				name: model.name
				login: model.login
				password: model.password
			}
		}
	}
}
