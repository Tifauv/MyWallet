import QtQuick 2.9

AccountViewForm {
	id: view

	property string name: "Account name"
	property string login: "Login"
	property bool hovered: false
	signal deleted()

	nameTxt.text: view.name
	loginTxt.text: view.login

	deleteBtn.enabled: hovered
	deleteBtn.onClicked: deleted()
}
