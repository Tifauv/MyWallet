import QtQuick 2.12

AccountCreateForm {
	id: form
	
	property string accountName: nameTxt.text
	property string accountLogin: loginTxt.text
	property string accountPassword: passwordTxt.text
	
	// An account can be created if its name is not empty
	readonly property bool isValid: nameTxt.text.length > 0
	
	signal accepted()
	
	nameTxt.onAccepted     : if (isValid()) accepted()
	loginTxt.onAccepted    : if (isValid()) accepted()
	passwordTxt.onAccepted : if (isValid()) accepted()
	
	function reset() {
		nameTxt.text = "";
		loginTxt.text = "";
		passwordTxt.text = "";
		nameTxt.focus = true;
	}
}
