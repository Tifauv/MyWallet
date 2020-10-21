import QtQuick 2.12

AccountViewForm {
	id: view
	
	property string name: "Account name"
	property string login: "Login"
	property string password: ""
	property string website: "https://www.example.org"
	property string notes: "This is a test account."
	
	signal copyString(string p_string)
	signal copyPassword(string p_password)
	
	nameLbl.value: name
	loginLbl.value: login
	passwordLbl.value: password
	websiteLbl.value: website
	notesLbl.value: notes
	
	websiteLbl.onCopyValue: view.copyString(p_value)
	loginLbl.onCopyValue: view.copyString(p_value)
	passwordLbl.onCopyValue: view.copyPassword(p_value)
}
