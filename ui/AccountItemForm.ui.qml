import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.4 as Kirigami

Item {
    id: account
    implicitWidth: 440
    implicitHeight: 53

    property alias nameTxt: accountName
    property alias loginTxt: accountLogin
    property alias passwordTxt: accountPassword

    Label {
        id: accountName
        text: qsTr("Account name")
        font.pixelSize: 16

        verticalAlignment: Text.AlignVCenter

        anchors.top: parent.top
        anchors.topMargin: Kirigami.Units.smallSpacing
        anchors.left: parent.left
        anchors.leftMargin: Kirigami.Units.largeSpacing
        anchors.right: parent.right
        anchors.rightMargin: Kirigami.Units.largeSpacing
    }

    Row {
        id: loginLayout

        height: Kirigami.Units.gridUnit
        width: childrenRect.width
        spacing: Kirigami.Units.smallSpacing

        anchors.top: accountName.bottom
        anchors.topMargin: Kirigami.Units.smallSpacing
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Kirigami.Units.smallSpacing
        anchors.left: accountName.left
        anchors.leftMargin: Kirigami.Units.largeSpacing * 2

        Kirigami.Icon {
            id: loginIcon

            source: "user"

            width: Kirigami.Units.iconSizes.small
            height: width
        }

        SecondaryLabel {
            id: accountLogin
            text: qsTr("Login")

            verticalAlignment: Text.AlignVCenter
        }
    }

    Row {
        id: passwordLayout

        visible: false

        height: Kirigami.Units.gridUnit
        spacing: Kirigami.Units.smallSpacing

        anchors.top: accountName.bottom
        anchors.topMargin: Kirigami.Units.smallSpacing
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Kirigami.Units.smallSpacing
        anchors.left: loginLayout.right
        anchors.leftMargin: Kirigami.Units.largeSpacing * 2
        anchors.right: parent.right
        anchors.rightMargin: Kirigami.Units.largeSpacing

        Kirigami.Icon {
            id: passwordIcon

            source: "lock"

            width: Kirigami.Units.iconSizes.small
            height: width
        }

        SecondaryLabel {
            id: accountPassword
            text: qsTr("********")

            verticalAlignment: Text.AlignVCenter
        }
    }
    states: [
        State {
            name: "ShowPassword"

            PropertyChanges {
                target: passwordLayout
                visible: true
            }
        }
    ]
}
