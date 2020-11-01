/*
 *  SPDX-FileCopyrightText: 2020 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

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

        FieldItem {
            id: notes
            name: qsTr("Notes")
            showCopyAction: false
            Layout.fillWidth: true
        }
    }
}
