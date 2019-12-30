import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5 as Controls
import org.kde.kirigami 2.4 as Kirigami

Kirigami.OverlaySheet {
	id: sheet
	
	/* The parent's folder model. */
	property var folderModel: undefined

	header: Kirigami.Heading {
		id: heading
		text: qsTr("New Account")
	}
	
	footer: RowLayout {
		Controls.Button {
			id: submitBtn
			
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
			
			text: qsTr("Create")
			focus: true
			enabled: form.isValid
			
			onClicked: form.submit()
		}
	}
	
	AccountCreate {
		id: form
		Layout.preferredWidth: Kirigami.Units.gridUnit * 20
		focus: true
		
		onAccepted: form.submit()
		
		function submit() {
			sheet.createAccount();
			sheet.close()
		}
	}
	
	function createAccount() {
		folderModel.createAccount(form.accountName, form.accountLogin, form.accountPassword);
		form.reset();
	}
}
