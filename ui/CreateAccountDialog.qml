import QtQuick 2.9
import QtQuick.Controls 2.2

Dialog {
	id: dialog

	implicitWidth: 220
	implicitHeight: nameTxt.height + loginTxt.height + passwordTxt.height + (2 * padding)

	standardButtons: Dialog.Save | Dialog.Cancel
	closePolicy: Dialog.CloseOnEscape | Dialog.CloseOnPressOutside

	property alias name: nameTxt.text
	property alias login: loginTxt.text
	property alias password: passwordTxt.text

	Column {
		id: layout

		anchors.fill: parent

		TextField {
			id: nameTxt
			width: parent.width

			placeholderText: qsTr("Account name")
			focus: true
		}

		TextField {
			id: loginTxt
			width: parent.width

			placeholderText: qsTr("Login")
		}

		TextField {
			id: passwordTxt
			width: parent.width

			placeholderText: qsTr("Password")
			echoMode: "Password"
		}
	}

	function reset() {
		name = "";
		login = "";
		password = "";
		nameTxt.focus = true;
	}
}
