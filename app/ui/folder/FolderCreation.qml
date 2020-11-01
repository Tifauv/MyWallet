/*
 *  SPDX-FileCopyrightText: 2020 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12

FolderCreationForm {
	id: form

	property string folderName: nameTxt.text
	property string folderTagColor: colorSelector.selectedColor
	
	// A folder can be created if its name is not empty
	readonly property bool isValid: nameTxt.text.length > 0

	signal accepted()
	
	nameTxt.onAccepted     : if (isValid()) accepted()
	
	function reset() {
		nameTxt.text = "";
		colorSelector.currentIndex = 0;
		nameTxt.focus = true;
	}
}
