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
#include "testcontrolelementeditor.h"
#include "../editors/ui_controlelementeditor.h"
#include "editors/controlelementeditor.h"
#include <QTest>

TestControlElementEditor::TestControlElementEditor(QObject *parent)
    : QObject(parent) {}

void TestControlElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::ControlElementType, 0, parameters};
    ControlElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->deviceCommand_comboBox->currentText().isEmpty());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::CodeElementType, 44, parameters};
    ControlElementEditor editor{&e};
    QVERIFY(editor.ui->timeEdit->time().second() == 44);
    QVERIFY(e.time() == 44);
  }
  {
    QJsonObject parameters;
    parameters["command"] = "stickstoff.vent.high";
    Element e{ElementType::ControlElementType, 0, parameters};
    ControlElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->deviceCommand_comboBox->currentText() ==
            "stickstoff.vent.high");
    QVERIFY(e.parameters()["command"] == "stickstoff.vent.high");
  }
}

void TestControlElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::CodeElementType, 0, parameters};
    ControlElementEditor editor{&e};
    editor.ui->timeEdit->setTime(QTime{0, 0, 44});
    QVERIFY(e.time() == 44);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ControlElementType, 0, parameters};
    ControlElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    editor.ui->deviceCommand_comboBox->setCurrentText("stickstoff.vent.high");
    QVERIFY(e.parameters()["command"] == "stickstoff.vent.high");
  }
}
