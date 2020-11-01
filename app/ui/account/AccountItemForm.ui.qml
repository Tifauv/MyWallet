

/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.8 as Kirigami
import ".."

Item {
    id: account
    implicitWidth: 200
    implicitHeight: childrenRect.height + rootLayout.anchors.topMargin
                    + rootLayout.anchors.bottomMargin

    property alias nameTxt: accountName
    property alias loginTxt: accountLogin

    Column {
        id: rootLayout

        Layout.fillWidth: true
        height: accountName.height + spacing + loginLayout.height
        spacing: Kirigami.Units.smallSpacing

        anchors {
            leftMargin: Kirigami.Units.largeSpacing
            rightMargin: Kirigami.Units.largeSpacing
            topMargin: Kirigami.Units.smallSpacing
            bottomMargin: Kirigami.Units.smallSpacing
        }

        Label {
            id: accountName
            text: qsTr("Account name")
            Layout.fillWidth: true

            verticalAlignment: Text.AlignVCenter
        }

        Row {
            id: loginLayout

            height: Kirigami.Units.gridUnit
            spacing: Kirigami.Units.smallSpacing
            leftPadding: Kirigami.Units.largeSpacing

            Kirigami.Icon {
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
    }
}
