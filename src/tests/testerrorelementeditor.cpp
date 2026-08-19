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
#include "testerrorelementeditor.h"
#include "../editors/ui_errorelementeditor.h"
#include "editors/errorelementeditor.h"
#include <QTest>

TestErrorElementEditor::TestErrorElementEditor(QObject *parent)
    : QObject(parent) {}

void TestErrorElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText().isEmpty());
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 45, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 45);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText().isEmpty());
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
  }
  {
    // Set error type
    QJsonObject parameters;
    parameters["type"] = "ni_sensor";
    Element e{ElementType::ErrorElementType, 45, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 45);
    QVERIFY(editor.ui->errortype_comboBox->currentText() == "ni_sensor");
    QVERIFY(editor.ui->diagnostic_comboBox->currentText().isEmpty());
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["type"] == "ni_sensor");
  }
  {
    // Set diagnostics
    QJsonObject parameters;
    parameters["diagnostics"] = "miss";
    Element e{ElementType::ErrorElementType, 45, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 45);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText() == "miss");
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["diagnostics"] == "miss");
  }
  {
    // Set allow late repair
    QJsonObject parameters;
    parameters["allowLateRepair"] = true;
    Element e{ElementType::ErrorElementType, 45, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 45);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["allowLateRepair"].toBool());
  }
  {
    QJsonObject parameters;
    parameters["clear"] = 30;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText().isEmpty());
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == 30);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["clear"] == 30);
  }
  {
    QJsonObject parameters;
    parameters["notify"] = 30;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText().isEmpty());
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == 30);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["notify"] == 30);
  }
  {
    QJsonObject parameters;
    parameters["repeatNotify"] = true;
    parameters["diagnostics"] = "true";
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText() == "true");
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["repeatNotify"].toBool());
  }
  {
    QJsonObject parameters;
    parameters["efficiency"] = 0.31;
    parameters["diagnostics"] = "true";
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText() == "true");
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 0.31);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["efficiency"] == 0.31);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {"alpha", "beta", "gamma"}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText().isEmpty());
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 3);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 3);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["surveyDelay"] = 55;
    parameters["diagnostics"] = "true";
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText() == "true");
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 55);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["surveyDelay"] == 55);
  }
  {
    QJsonObject parameters;
    parameters["loa"] = "loa3";
    parameters["diagnostics"] = "true";
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText() == "true");
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText() == "loa3");
    QVERIFY(editor.ui->loadelay_spinBox->value() == 0);
    QVERIFY(e.parameters()["loa"] == "loa3");
  }
  {
    QJsonObject parameters;
    parameters["loadelay"] = 32;
    parameters["diagnostics"] = "true";
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->errortype_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->diagnostic_comboBox->currentText() == "true");
    QVERIFY(!editor.ui->allowLateRepair_checkBox->isChecked());
    QVERIFY(editor.ui->fakelevel_comboBox->currentIndex() == 0);
    QVERIFY(editor.ui->cleanAfter_spinBox->value() == -1);
    QVERIFY(editor.ui->notifyAfter_spinBox->value() == -1);
    QVERIFY(!editor.ui->repeatNotification_checkBox->isChecked());
    QVERIFY(editor.ui->efficiency_spinBox->value() == 1.0);
    QVERIFY(editor.ui->surveycorrect_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveymissed_list->model()->rowCount() == 0);
    QVERIFY(editor.ui->surveydelay_spinBox->value() == 0);
    QVERIFY(editor.ui->loa_comboBox->currentText().isEmpty());
    QVERIFY(editor.ui->loadelay_spinBox->value() == 32);
    QVERIFY(e.parameters()["loadelay"] == 32);
  }
}

void TestErrorElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->timeEdit->setTime(QTime{0, 0, 21});
    QVERIFY(e.time() == 21);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->errortype_comboBox->setCurrentText("ni_sensor");
    QVERIFY(e.parameters()["type"] == "ni_sensor");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->diagnostic_comboBox->setCurrentText("miss");
    QVERIFY(e.parameters()["diagnostics"] == "miss");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->allowLateRepair_checkBox->setChecked(true);
    QVERIFY(e.parameters()["allowLateRepair"].toBool());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->fakelevel_comboBox->setCurrentIndex(2);
    QVERIFY(e.parameters()["fake"].toInt() == 2);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->cleanAfter_spinBox->setValue(23);
    QVERIFY(e.parameters()["clear"].toInt() == 23);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->notifyAfter_spinBox->setValue(23);
    QVERIFY(e.parameters()["notify"].toInt() == 23);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->repeatNotification_checkBox->setChecked(true);
    QVERIFY(e.parameters()["repeatNotify"].toBool());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->efficiency_spinBox->setValue(0.67);
    QVERIFY(e.parameters()["efficiency"].toDouble() == 0.67);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->loa_comboBox->setCurrentText("loa2");
    QVERIFY(e.parameters()["loa"] == "loa2");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ErrorElementType, 0, parameters};
    ErrorElementEditor editor{&e, {}};
    editor.ui->loadelay_spinBox->setValue(33);
    QVERIFY(e.parameters()["loadelay"].toInt() == 33);
  }
}
