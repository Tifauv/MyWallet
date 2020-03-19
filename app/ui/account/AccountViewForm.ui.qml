import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.8 as Kirigami
import QtQuick.Layouts 1.3

Item {
    id: editor
    implicitWidth: 400
    implicitHeight: 400

    property alias nameLbl: name
    property alias loginLbl: login
    property alias passwordLbl: password
    property alias websiteLbl: website
    property alias notesLbl: notes

    ColumnLayout {
        id: column

        spacing: Kirigami.Units.largeSpacing
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter

        FieldItem {
            id: name
            name: qsTr("Name")
            showCopyAction: false
            Layout.fillWidth: true
        }

        FieldItem {
            id: website
            name: qsTr("Website")
            Layout.fillWidth: true
        }

        FieldItem {
            id: login
            name: qsTr("Login")
            Layout.fillWidth: true
        }

        FieldItem {
            id: password
            name: qsTr("Password")
            showRevealAction: true
            Layout.fillWidth: true
        }

        Kirigami.FormLayout {
            Layout.fillWidth: true

            Kirigami.Separator {
                Kirigami.FormData.label: qsTr("Password History")
                Kirigami.FormData.isSection: true
            }

            Kirigami.Separator {
                Kirigami.FormData.label: qsTr("Notes")
                Kirigami.FormData.isSection: true
            }

            Label {
                id: notes
                text: "This is a test acccount designed to check the global behaviour of the viewer and editor."
            }
        }
    }
}
