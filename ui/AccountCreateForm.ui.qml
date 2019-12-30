import QtQuick 2.12
import QtQuick.Controls 2.5 as Controls
import org.kde.kirigami 2.8 as Kirigami

Item {
    implicitWidth: 300
    implicitHeight: 400

    property alias nameTxt: nameTxt
    property alias loginTxt: loginTxt
    property alias passwordTxt: passwordTxt

    Kirigami.FormLayout {
        clip: true
        anchors.fill: parent

        Controls.TextField {
            id: nameTxt
            placeholderText: qsTr("Account name")
            Kirigami.FormData.label: qsTr("Name")
            selectByMouse: true
            maximumLength: 36
            focus: true
        }
        Controls.TextField {
            id: loginTxt
            placeholderText: qsTr("Account login")
            Kirigami.FormData.label: qsTr("Login")
            selectByMouse: true
            maximumLength: 128
            focus: true
        }
        Kirigami.PasswordField {
            id: passwordTxt
            placeholderText: qsTr("Account password")
            Kirigami.FormData.label: qsTr("Password")
            selectByMouse: true
            maximumLength: 48
            focus: true
        }
    }
}
