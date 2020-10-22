import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.10 as Kirigami

Kirigami.OverlaySheet {
	id: sheet
	
	property string accountName
	signal modifyAccount(string login, string website, string notes)

	header: Kirigami.Heading {
		id: heading
		text: qsTr("Edit Account %1").arg(accountName)
	}
	
	footer: RowLayout {
		Controls.Button {
			id: submitBtn
			
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
			
			text: qsTr("Modify")
			focus: true
			enabled: form.isValid
			
			onClicked: form.submit()
		}
	}
	
	AccountEdition {
		id: form
		Layout.preferredWidth: Kirigami.Units.gridUnit * 20
		focus: true
		
		onAccepted: form.submit()
		
		function submit() {
			sheet.modifyAccount(form.accountLogin, form.accountWebsite, form.accountNotes);
			sheet.close()
		}
	}
	
	function reset(account) {
		sheet.accountName = account.name;
		form.reset(account);
	}
}
