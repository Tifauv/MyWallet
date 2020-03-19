import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.8 as Kirigami

Item {
    id: editor
    implicitWidth: 400
    implicitHeight: 400

    property alias nameTxt: name
    property alias loginTxt: login
	property alias newPasswordTxt: newPassword

    Column {
        id: column
        anchors.fill: parent

        Kirigami.FormLayout {
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            TextField {
                id: name
                Kirigami.FormData.label: qsTr("Name")
            }
            TextField {
                id: login
                Kirigami.FormData.label: qsTr("Login")
            }
            Kirigami.Separator {
                //Kirigami.FormData.label: qsTr("New Password")
                Kirigami.FormData.isSection: true
            }
			Kirigami.PasswordField {
				id: newPassword
				placeholderText: qsTr("New password")
				Kirigami.FormData.label: qsTr("Password")
				selectByMouse: true
				maximumLength: 48
				focus: true
            }
			Kirigami.Separator {
                Kirigami.FormData.label: qsTr("Password History")
                Kirigami.FormData.isSection: true
            }
        }
    }
}
