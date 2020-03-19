import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.10 as Kirigami

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
	
	AccountCreation {
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
		folderModel.createAccount(form.accountName, form.accountLogin, form.website, form.notes, form.accountPassword);
		form.reset();
	}
}
