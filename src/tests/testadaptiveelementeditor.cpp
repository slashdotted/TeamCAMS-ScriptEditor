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
#include "testadaptiveelementeditor.h"
#include "../editors/ui_adaptiveelementeditor.h"
#include "editors/adaptiveelementeditor.h"
#include <QTest>

TestAdaptiveElementEditor::TestAdaptiveElementEditor(QObject *parent)
    : QObject(parent) {}

void TestAdaptiveElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->command_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->pastPeriod_spinBox->value() == 0);
    QVERIFY(editor.ui->periodTo_spinBox->value() == 0);
    QVERIFY(editor.ui->periodFrom_spinBox->value() == 0);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::AdaptiveElementType, 13, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(editor.ui->timeEdit->time().second() == 13);
  }
  {
    QJsonObject parameters;
    parameters["onPast"] = 42;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(editor.ui->command_comboBox->currentText() == "onPast");
    QVERIFY(editor.ui->pastPeriod_spinBox->value() == 42);
    QVERIFY(editor.ui->pastPeriod_spinBox->isEnabled());
    QVERIFY(!editor.ui->samples_spinBox->isEnabled());
    QVERIFY(!editor.ui->periodFrom_spinBox->isEnabled());
    QVERIFY(!editor.ui->periodTo_spinBox->isEnabled());
    QVERIFY(e.parameters() == parameters);
  }
  {
    QJsonObject parameters;
    parameters["onPeriodFrom"] = 10;
    parameters["onPeriodTo"] = 20;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(editor.ui->command_comboBox->currentText() == "onPeriod");
    QVERIFY(editor.ui->periodFrom_spinBox->value() == 10);
    QVERIFY(editor.ui->periodTo_spinBox->value() == 20);
    QVERIFY(!editor.ui->pastPeriod_spinBox->isEnabled());
    QVERIFY(!editor.ui->samples_spinBox->isEnabled());
    QVERIFY(editor.ui->periodFrom_spinBox->isEnabled());
    QVERIFY(editor.ui->periodTo_spinBox->isEnabled());
    QVERIFY(e.parameters() == parameters);
  }
  {
    QJsonObject parameters;
    parameters["onSamples"] = 13;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(editor.ui->command_comboBox->currentText() == "onSamples");
    QVERIFY(editor.ui->samples_spinBox->value() == 13);
    QVERIFY(!editor.ui->pastPeriod_spinBox->isEnabled());
    QVERIFY(editor.ui->samples_spinBox->isEnabled());
    QVERIFY(!editor.ui->periodFrom_spinBox->isEnabled());
    QVERIFY(!editor.ui->periodTo_spinBox->isEnabled());
    QVERIFY(e.parameters() == parameters);
  }
}

void TestAdaptiveElementEditor::testChange() {
  {
    // Test change start time
    QJsonObject parameters;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(e.time() == 0);
    editor.ui->timeEdit->setTime(QTime{0, 0, 13});
    QVERIFY(e.time() == 13);
  }
  {
    // Test change adaptive type
    QJsonObject parameters;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(editor.ui->command_comboBox->currentText().isEmpty());
    editor.ui->command_comboBox->setCurrentText("onSamples");
    editor.ui->samples_spinBox->setValue(4);
    QVERIFY(e.parameters()["onSamples"].toInt() == 4);
  }
  {
    // Test change adaptive type
    QJsonObject parameters;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(editor.ui->command_comboBox->currentText().isEmpty());
    editor.ui->command_comboBox->setCurrentText("onPeriod");
    editor.ui->periodFrom_spinBox->setValue(5);
    editor.ui->periodTo_spinBox->setValue(10);
    QVERIFY(e.parameters()["onPeriodFrom"].toInt() == 5);
    QVERIFY(e.parameters()["onPeriodTo"].toInt() == 10);
  }
  {
    // Test change adaptive type
    QJsonObject parameters;
    Element e{ElementType::AdaptiveElementType, 0, parameters};
    AdaptiveElementEditor editor{&e};
    QVERIFY(editor.ui->command_comboBox->currentText().isEmpty());
    editor.ui->command_comboBox->setCurrentText("onPast");
    editor.ui->pastPeriod_spinBox->setValue(2);
    QVERIFY(e.parameters()["onPast"].toInt() == 2);
  }
}
