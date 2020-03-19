import QtQuick 2.12

AccountItemForm {
	id: view

	property string name: "Account name"
	property string login: "Login"

	nameTxt.text: view.name
	loginTxt.text: view.login
}
