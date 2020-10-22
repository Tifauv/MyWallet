import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.10 as Kirigami

Item {
    implicitWidth: form.implicitWidth
    implicitHeight: form.implicitHeight

    property alias websiteTxt: websiteTxt
    property alias loginTxt: loginTxt
    property alias notesTxt: notesTxt

    Kirigami.FormLayout {
        id: form

        anchors.fill: parent

        Controls.TextField {
            id: websiteTxt
            placeholderText: qsTr("https://example.org")
            Kirigami.FormData.label: qsTr("Website")
            selectByMouse: true
            maximumLength: 128
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
        Controls.TextArea {
            id: notesTxt
            placeholderText: qsTr("Notes about this account...\n\n\n")
            Kirigami.FormData.label: qsTr("Notes")
            selectByMouse: true
            Layout.fillWidth: parent
            focus: true
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
