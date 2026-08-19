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
#include "testassistanceelementeditor.h"
#include "../editors/ui_assistanceelementeditor.h"
#include "editors/assistanceelementeditor.h"
#include <QTest>

TestAssistanceElementEditor::TestAssistanceElementEditor(QObject *parent)
    : QObject(parent) {}

void TestAssistanceElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::AssistanceElementType, 0, parameters};
    AssistanceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->type_comboBox->currentText() == "loa1");
    QVERIFY(!editor.ui->notify_checkBox->isChecked());
  }
  {
    QJsonObject parameters;
    parameters["type"] = "loa2";
    Element e{ElementType::AssistanceElementType, 0, parameters};
    AssistanceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->type_comboBox->currentText() == "loa2");
    QVERIFY(!editor.ui->notify_checkBox->isChecked());
  }
  {
    QJsonObject parameters;
    parameters["type"] = "loa2";
    parameters["notify"] = true;
    Element e{ElementType::AssistanceElementType, 0, parameters};
    AssistanceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->type_comboBox->currentText() == "loa2");
    QVERIFY(editor.ui->notify_checkBox->isChecked());
  }
}

void TestAssistanceElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::AssistanceElementType, 0, parameters};
    AssistanceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->type_comboBox->currentText() == "loa1");
    QVERIFY(!editor.ui->notify_checkBox->isChecked());
    editor.ui->timeEdit->setTime(QTime{0, 0, 3});
    QVERIFY(e.time() == 3);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::AssistanceElementType, 0, parameters};
    AssistanceElementEditor editor{&e};
    editor.ui->type_comboBox->setCurrentText("loa4");
    QVERIFY(e.parameters()["type"] == "loa4");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::AssistanceElementType, 0, parameters};
    AssistanceElementEditor editor{&e};
    editor.ui->notify_checkBox->setChecked(true);
    QVERIFY(e.parameters()["notify"].toBool());
  }
}
