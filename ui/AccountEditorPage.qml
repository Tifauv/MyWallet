import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami

Kirigami.Page {
	id: page
	title: qsTr("Account editor")
	
	property variant model
	
	AccountEditor {
		id: editor
		
		name: model.name
		login: model.login
		//password: model.password
	}
}
