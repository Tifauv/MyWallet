import QtQuick 2.12

AccountItemForm {
	id: view

	property string name: "Account name"
	property string login: "Login"
	property string password: "********"
	property bool passwordVisible: false

	nameTxt.text: view.name
	loginTxt.text: view.login
	passwordTxt.text: view.password
	
	onPasswordVisibleChanged: view.state = passwordVisible ? "ShowPassword" : ""
}
