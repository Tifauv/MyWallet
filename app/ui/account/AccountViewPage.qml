/*
 *  SPDX-FileCopyrightText: 2020 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.8 as Kirigami

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Account")
	
	property variant model
	property variant editDlg
	
	signal copyString(string p_string)
	signal copyPassword(string p_password)
	signal confirmDelete()
	
    mainAction: Kirigami.Action {
        text: qsTr("Edit")
        iconName: "document-edit"
		onTriggered: {
			editDlg.reset(model);
			editDlg.open();
		}
    }
	
	contextualActions: [
		Kirigami.Action {
			text: qsTr("Delete")
			iconName: "edit-delete"
			onTriggered: page.confirmDelete()
		}
    ]

	mainItem: AccountView {
		id: view
		
		name: model.name
		login: model.login
		password: model.password
		website: model.website
		notes: model.notes
		
		onCopyString: page.copyString(p_string)
		onCopyPassword: page.copyPassword(p_password)
	}
}
