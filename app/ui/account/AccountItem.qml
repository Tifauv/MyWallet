/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12

AccountItemForm {
	id: view

	property string name: "Account name"
	property string login: "Login"

	nameTxt.text: view.name
	loginTxt.text: view.login
}
