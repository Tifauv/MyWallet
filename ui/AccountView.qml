import QtQuick 2.9

AccountViewForm {
	id: view

	property string name: "Account name"
	property string login: "Login"

	nameTxt.text: view.name
	loginTxt.text: view.login
}
