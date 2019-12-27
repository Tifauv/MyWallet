import QtQuick 2.4
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami

Item {
    id: editor
    implicitWidth: 400
    implicitHeight: 400

    property alias nameTxt: name
    property alias loginTxt: login

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
                Kirigami.FormData.label: qsTr("Password history")
                Kirigami.FormData.isSection: true
            }
        }
    }
}
