import QtQuick 2.4

AccountViewForm {
	id: view

	property string name: "Account name"
	property string login: "Login"

	nameTxt.text: view.name
	loginTxt.text: view.login
}
