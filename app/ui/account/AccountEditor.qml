import QtQuick 2.12

AccountEditorForm {
	
	property string name: "Account name"
	property string login: "Login"
	property string password: "********"
	
	nameTxt.text: name
	loginTxt.text: login
	//passwordTxt.text: password
}
