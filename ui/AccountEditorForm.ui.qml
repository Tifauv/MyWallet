import QtQuick 2.4
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami

Item {
    id: editor
    implicitWidth: 400
    implicitHeight: 400

    property alias headingTxt: heading
    property alias loginTxt: login
    property alias passwordTxt: password
	
    Column {
        id: column
        anchors.fill: parent

        Kirigami.Heading {
            id: heading
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        Kirigami.FormLayout {
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            TextField {
                id: login
                Kirigami.FormData.label: qsTr("Login:")
            }
            TextField {
                id: password
                Kirigami.FormData.label: qsTr("Password:")
            }
            Kirigami.Separator {
                Kirigami.FormData.label: qsTr("Password generator")
                Kirigami.FormData.isSection: true
            }
        }
    }
}
