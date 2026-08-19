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
#include "testaccesselementeditor.h"
#include "../editors/ui_accesselementeditor.h"
#include "editors/accesselementeditor.h"
#include <QTest>

TestAccessElementEditor::TestAccessElementEditor(QObject *parent)
    : QObject(parent) {}

void TestAccessElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::AccessElementType, 0, parameters};
    AccessElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->accessTypeCombo->currentIndex() == 0);
  }
  {
    QJsonObject parameters;
    parameters["username"] = "foo";
    Element e{ElementType::AccessElementType, 0, parameters};
    AccessElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->usernameEdit->text() == "foo");
    QVERIFY(editor.ui->accessTypeCombo->currentIndex() == 0);
  }
  {
    QJsonObject parameters;
    parameters["username"] = "foo";
    parameters["type"] = 5;
    Element e{ElementType::AccessElementType, 0, parameters};
    AccessElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->usernameEdit->text() == "foo");
    QVERIFY(editor.ui->accessTypeCombo->currentIndex() == 5);
  }
}

void TestAccessElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::AccessElementType, 0, parameters};
    AccessElementEditor editor{&e};
    editor.ui->timeEdit->setTime(QTime{0, 0, 44});
    QVERIFY(e.time() == 44);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::AccessElementType, 0, parameters};
    AccessElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->accessTypeCombo->currentIndex() == 0);
    editor.ui->usernameEdit->setText("bar");
    QVERIFY(e.parameters()["username"] == "bar");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::AccessElementType, 0, parameters};
    AccessElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->accessTypeCombo->currentIndex() == 0);
    editor.ui->accessTypeCombo->setCurrentIndex(7);
    QVERIFY(e.parameters()["type"] == 7);
  }
}
