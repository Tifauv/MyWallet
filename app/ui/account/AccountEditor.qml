import QtQuick 2.12

AccountEditorForm {
	
	property string name: "Account name"
	property string login: "Login"
	property string newPassword: ""
	
	nameTxt.text: name
	loginTxt.text: login
	newPasswordTxt.text: newPassword
}
