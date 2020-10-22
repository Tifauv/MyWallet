import QtQuick 2.12

AccountEditionForm {
	id: form
	
	property string accountWebsite: websiteTxt.text
	property string accountLogin: loginTxt.text
	property string accountNotes: notesTxt.text
	
	signal accepted()
	
	websiteTxt.onAccepted: accepted()
	loginTxt.onAccepted: accepted()
	
	function reset(account) {
		websiteTxt.text = account.website;
		loginTxt.text = account.login;
		notesTxt.text = account.notes;
		websiteTxt.focus = true;
	}
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
