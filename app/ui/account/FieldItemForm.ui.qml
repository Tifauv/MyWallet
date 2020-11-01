/*
 *  SPDX-FileCopyrightText: 2020 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.8 as Kirigami
import ".."
import QtQuick.Layouts 1.3

Item {
    id: editor
    implicitHeight: mainLayout.implicitHeight

    property alias nameTxt: nameTxt
    property alias valueTxt: valueTxt
    property alias revealBtn: revealBtn
    property alias copyBtn: copyBtn

    RowLayout {
        id: mainLayout

        width: parent.width
        spacing: Kirigami.Units.largeSpacing

        ColumnLayout {
            id: nameValueLayout

            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            SecondaryLabel {
                id: nameTxt
                text: qsTr("Field name")
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom

                width: valueTxt.width
            }

            Loader {
                id: valueTxt
                Layout.fillWidth: true
            }
        }

        Button {
            id: revealBtn
            text: qsTr("Show the password")
            Layout.preferredWidth: height
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            visible: true
            display: AbstractButton.IconOnly
            icon.name: "password-show-on"
        }

        Button {
            id: copyBtn
            text: qsTr("Copy the password to the clipboard")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.preferredWidth: height
            display: AbstractButton.IconOnly
            icon.name: "edit-copy"
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
