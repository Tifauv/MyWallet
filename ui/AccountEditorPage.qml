import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami

Kirigami.Page {
	id: page
	title: qsTr("Account editor")
	
	property variant model

    signal saveAccount()
    signal closePage()
	
    mainAction: Kirigami.Action {
        text: qsTr("Save")
        iconName: "document-save"
        onTriggered: saveAccount()
    }
    contextualActions: [
        Kirigami.Action {
            text: qsTr("Close")
            iconName: "tab-close"
            onTriggered: closePage()
        }
    ]

	AccountEditor {
		id: editor
		
		name: model.name
		login: model.login
		//password: model.password
	}
}
