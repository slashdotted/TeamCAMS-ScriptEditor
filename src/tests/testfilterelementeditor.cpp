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
#include "testfilterelementeditor.h"
#include "../editors/ui_filterelementeditor.h"
#include "editors/filterelementeditor.h"
#include <QTest>

TestFilterElementEditor::TestFilterElementEditor(QObject *parent)
    : QObject(parent) {}

void TestFilterElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->messageTypeCombo->currentText() == "server_update");
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->keyPatternEdit->text().isEmpty());
    QVERIFY(!editor.ui->blockCheck->isChecked());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::FilterElementType, 33, parameters};
    FilterElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 33);
    QVERIFY(editor.ui->messageTypeCombo->currentText() == "server_update");
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->keyPatternEdit->text().isEmpty());
    QVERIFY(!editor.ui->blockCheck->isChecked());
  }
  {
    QJsonObject parameters;
    parameters["type"] = "client_update";
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->messageTypeCombo->currentText() == "client_update");
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->keyPatternEdit->text().isEmpty());
    QVERIFY(!editor.ui->blockCheck->isChecked());
  }
  {
    QJsonObject parameters;
    parameters["enabled"] = true;
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->messageTypeCombo->currentText() == "server_update");
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->keyPatternEdit->text().isEmpty());
    QVERIFY(editor.ui->blockCheck->isChecked());
  }
  {
    QJsonObject parameters;
    parameters["user"] = "someguy";
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->messageTypeCombo->currentText() == "server_update");
    QVERIFY(editor.ui->usernameEdit->text() == "someguy");
    QVERIFY(editor.ui->keyPatternEdit->text().isEmpty());
    QVERIFY(!editor.ui->blockCheck->isChecked());
  }
  {
    QJsonObject parameters;
    parameters["key"] = "somepattern";
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->messageTypeCombo->currentText() == "server_update");
    QVERIFY(editor.ui->usernameEdit->text().isEmpty());
    QVERIFY(editor.ui->keyPatternEdit->text() == "somepattern");
    QVERIFY(!editor.ui->blockCheck->isChecked());
  }
}

void TestFilterElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    editor.ui->timeEdit->setTime(QTime{0, 0, 36});
    QVERIFY(e.time() == 36);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    editor.ui->messageTypeCombo->setCurrentText("client_update");
    QVERIFY(e.parameters()["type"] == "client_update");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    editor.ui->keyPatternEdit->setText("somekey");
    QVERIFY(e.parameters()["key"] == "somekey");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    editor.ui->usernameEdit->setText("someuser");
    QVERIFY(e.parameters()["user"] == "someuser");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::FilterElementType, 0, parameters};
    FilterElementEditor editor{&e};
    editor.ui->blockCheck->setChecked(true);
    QVERIFY(e.parameters()["enabled"].toBool());
  }
}
