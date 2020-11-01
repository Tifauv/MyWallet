
/*
 *  SPDX-FileCopyrightText: 2020 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */
import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.10 as Kirigami
import ".."

Item {
    implicitWidth: form.implicitWidth
    implicitHeight: form.implicitHeight

    property alias nameTxt: nameTxt
    property alias colorSelector: colorSelector

    Kirigami.FormLayout {
        id: form

        anchors.fill: parent

        Controls.TextField {
            id: nameTxt
            placeholderText: qsTr("Folder name")
            Kirigami.FormData.label: qsTr("Name")
            selectByMouse: true
            maximumLength: 36
            focus: true
        }

        ColorSelector {
            id: colorSelector
            Kirigami.FormData.label: qsTr("Color")
            model: SolarizedPalette {}
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

