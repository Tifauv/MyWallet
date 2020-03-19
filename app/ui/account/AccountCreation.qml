import QtQuick 2.12

AccountCreationForm {
	id: form
	
	property string accountName: nameTxt.text
	property string accountWebsite: websiteTxt.text
	property string accountLogin: loginTxt.text
	property string accountPassword: passwordTxt.text
	property string accountNotes: notesTxt.text
	
	// An account can be created if its name is not empty
	readonly property bool isValid: nameTxt.text.length > 0
	
	signal accepted()
	
	nameTxt.onAccepted     : if (isValid()) accepted()
	loginTxt.onAccepted    : if (isValid()) accepted()
	passwordTxt.onAccepted : if (isValid()) accepted()
	
	function reset() {
		nameTxt.text = "";
		websiteTxt.text = "";
		loginTxt.text = "";
		passwordTxt.text = "";
		notesTxt.text = "";
		nameTxt.focus = true;
	}
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
