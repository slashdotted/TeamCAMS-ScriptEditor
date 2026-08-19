// TeamCAMS - reborn Cabin Air Management System
// Copyright (C) 2015-2026  Amos Brocco,
//                          Cognitive Ergonomics and Work Psychology Team,
//                          Psychology Department of Fribourg University,
//                          Switzerland / Department of Innovative Technologies
//                          University of Applied Sciences and Arts of Southern
//                          Switzerland, Contact: amos.brocco@supsi.ch
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
#include "testpopupelementeditor.h"
#include "../editors/ui_popupelementeditor.h"
#include "editors/popupelementeditor.h"
#include <QTest>

TestPopupElementEditor::TestPopupElementEditor(QObject *parent)
    : QObject(parent) {}

void TestPopupElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::PopupElementType, 0, parameters};
    PopupElementEditor editor{&e, {}};
    QVERIFY(editor.ui->urlEdit->text().isEmpty());
  }
  {
    QJsonObject parameters;
    parameters["url"] = "www.syscall.org";
    Element e{ElementType::PopupElementType, 0, parameters};
    PopupElementEditor editor{&e};
    QVERIFY(editor.ui->urlEdit->text() == "www.syscall.org");
  }
}

void TestPopupElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::PopupElementType, 0, parameters};
    PopupElementEditor editor{&e};
    editor.ui->urlEdit->setText("www.fuzzbug.com");
    QVERIFY(e.parameters()["url"].toString() == "www.fuzzbug.com");
  }
}
