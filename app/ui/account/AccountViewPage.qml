import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.8 as Kirigami

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Account")
	
	property variant model
	
	signal copyString(string p_string)
	signal copyPassword(string p_password)
    signal edit()
	signal confirmDelete()
	
    mainAction: Kirigami.Action {
        text: qsTr("Edit")
        iconName: "document-edit"
        onTriggered: page.edit()
    }
	
	contextualActions: [
		Kirigami.Action {
			text: qsTr("Delete")
			iconName: "edit-delete"
			onTriggered: page.confirmDelete()
		}
    ]

	mainItem: AccountView {
		id: view
		
		name: model.name
		login: model.login
		password: model.password
		website: model.website
		notes: model.notes
		
		onCopyString: page.copyString(p_string)
		onCopyPassword: page.copyPassword(p_password)
	}
}
