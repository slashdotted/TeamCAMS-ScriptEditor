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
#include "errorelementeditor.h"
#include "ui_errorelementeditor.h"
#include <QDebug>
#include <QDoubleSpinBox>
#include <QListWidgetItem>

ErrorElementEditor::ErrorElementEditor(Element *e,
                                       const QStringList &validQuestionIds,
                                       QWidget *parent)
    : Editor(parent), ui(new Ui::ErrorElementEditor), m_element{e} {
  ui->setupUi(this);
  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));

  ui->surveycorrect_list->addItems(validQuestionIds);
  ui->surveymissed_list->addItems(validQuestionIds);

  QStringList correct;
  for (QString q : m_element->parameters()["surveyOk"].toString().split(",")) {
    if (validQuestionIds.contains(q)) {
      correct.append(q);
    }
  }

  QStringList wrong;
  for (QString q : m_element->parameters()["survey"].toString().split(",")) {
    if (validQuestionIds.contains(q)) {
      wrong.append(q);
    }
  }

  QListWidgetItem *item;
  for (int i = 0; i < ui->surveycorrect_list->count(); i++) {
    item = ui->surveycorrect_list->item(i);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    if (correct.contains(item->text())) {
      item->setCheckState(Qt::Checked);
    } else {
      item->setCheckState(Qt::Unchecked);
    }
  }

  for (int i = 0; i < ui->surveymissed_list->count(); i++) {
    item = ui->surveymissed_list->item(i);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    if (wrong.contains(item->text())) {
      item->setCheckState(Qt::Checked);
    } else {
      item->setCheckState(Qt::Unchecked);
    }
  }

  ui->errortype_comboBox->addItems({"",
                                    "ox_valve_leak",
                                    "ox_valve_block",
                                    "ox_stuck_open",
                                    "ox_sensor_upper",
                                    "ox_sensor_lower",
                                    "ox_sensor",
                                    "ni_valve_leak",
                                    "ni_valve_block",
                                    "ni_stuck_open",
                                    "ni_sensor_upper",
                                    "ni_sensor_lower",
                                    "ni_sensor",
                                    "mixer_block",
                                    "dehum_sensor_lower",
                                    "dehum_sensor_upper",
                                    "cool_sensor_lower",
                                    "heat_sensor_lower",
                                    "cool_sensor_upper",
                                    "heat_sensor_upper",
                                    "scrub_sensor_lower",
                                    "scrub_sensor_upper",
                                    "vent_sensor_lower",
                                    "vent_sensor_upper",
                                    "dehum_ineff",
                                    "scrub_ineff",
                                    "vent_ineff",
                                    "cool_ineff",
                                    "heat_ineff",
                                    "dehum_stuck_on",
                                    "scrub_stuck_on",
                                    "cool_stuck_on",
                                    "heat_stuck_on",
                                    "vent_stuck_on",
                                    "dehum_sensor",
                                    "scrub_sensor",
                                    "cool_sensor",
                                    "heat_sensor",
                                    "vent_sensor"});

  if (m_element->parameters().contains("type")) {
    ui->errortype_comboBox->setCurrentText(
        // Fix typo found in some scripts
        m_element->parameters()["type"].toString().replace("leack", "leak"));
  } else {
    ui->errortype_comboBox->setCurrentIndex(0);
    m_element->parameters()["type"] = "ox_valve_leak";
    emit dataChanged(m_element);
  }

  if (m_element->parameters().contains("clear")) {
    ui->cleanAfter_spinBox->setValue(m_element->parameters()["clear"].toInt());
  }

  ui->diagnostic_comboBox->addItems({"",
                                     "true",
                                     "miss",
                                     "ox_valve_leak",
                                     "ox_valve_block",
                                     "ox_stuck_open",
                                     "ox_sensor_upper",
                                     "ox_sensor_lower",
                                     "ox_sensor",
                                     "ni_valve_leak",
                                     "ni_valve_block",
                                     "ni_stuck_open",
                                     "ni_sensor_upper",
                                     "ni_sensor_lower",
                                     "ni_sensor",
                                     "mixer_block",
                                     "dehum_sensor_lower",
                                     "dehum_sensor_upper",
                                     "cool_sensor_lower",
                                     "heat_sensor_lower",
                                     "cool_sensor_upper",
                                     "heat_sensor_upper",
                                     "scrub_sensor_lower",
                                     "scrub_sensor_upper",
                                     "vent_sensor_lower",
                                     "vent_sensor_upper",
                                     "dehum_ineff",
                                     "scrub_ineff",
                                     "vent_ineff",
                                     "cool_ineff",
                                     "heat_ineff",
                                     "dehum_stuck_on",
                                     "scrub_stuck_on",
                                     "cool_stuck_on",
                                     "heat_stuck_on",
                                     "vent_stuck_on",
                                     "dehum_sensor",
                                     "scrub_sensor",
                                     "cool_sensor",
                                     "heat_sensor",
                                     "vent_sensor"});
  if (m_element->parameters().contains("diagnostics")) {
    ui->diagnostic_comboBox->setCurrentText(
        m_element->parameters()["diagnostics"].toString().replace("false",
                                                                  "miss"));
  } else {
    ui->diagnostic_comboBox->setCurrentIndex(0);
    m_element->parameters()["diagnostics"] = "true";
    emit dataChanged(m_element);
  }

  ui->fakelevel_comboBox->addItems({"0 (not fake)", "1 (alarm, no assistance)",
                                    "2 (no alarm, assistance)",
                                    "3 (alarm, assistance)"});
  if (m_element->parameters().contains("fake")) {
    bool ok;
    int value{m_element->parameters()["fake"].toString().toInt(&ok)};
    ui->fakelevel_comboBox->setCurrentIndex(value);
  }

  if (m_element->parameters().contains("notify")) {
    int value{m_element->parameters()["notify"].toInt()};
    ui->notifyAfter_spinBox->setValue(value);
  }

  if (m_element->parameters().contains("efficiency")) {
    ui->efficiency_spinBox->setValue(
        m_element->parameters()["efficiency"].toDouble());
  }

  if (m_element->parameters().contains("surveyDelay")) {
    ui->surveydelay_spinBox->setValue(
        m_element->parameters()["surveyDelay"].toDouble());
  }

  if (m_element->parameters().contains("repeatNotify")) {
    ui->repeatNotification_checkBox->setChecked(
        m_element->parameters()["repeatNotify"].toBool());
  }

  if (m_element->parameters().contains("allowLateRepair")) {
    ui->allowLateRepair_checkBox->setChecked(
        m_element->parameters()["allowLateRepair"].toBool());
  }

  ui->loa_comboBox->addItems(
      {"", "loa1", "loa2", "loa3", "loa4", "loa5", "ask", "force"});
  if (m_element->parameters().contains("loa")) {
    ui->loa_comboBox->setCurrentText(m_element->parameters()["loa"].toString());
    ui->loadelay_spinBox->setEnabled(true);
  } else {
    ui->loadelay_spinBox->setEnabled(false);
  }

  if (m_element->parameters().contains("loadelay")) {
    ui->loadelay_spinBox->setValue(m_element->parameters()["loadelay"].toInt());
  }

  connect(ui->errortype_comboBox, &QComboBox::currentTextChanged, this,
          &ErrorElementEditor::onErrorTypeChanged);
  connect(ui->diagnostic_comboBox, &QComboBox::currentTextChanged, this,
          &ErrorElementEditor::onDiagnosticsChanged);
  connect(ui->surveycorrect_list, &QListWidget::itemChanged, this,
          &ErrorElementEditor::onSurveyItemChanged);
  connect(ui->surveymissed_list, &QListWidget::itemChanged, this,
          &ErrorElementEditor::onSurveyItemChanged);
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &ErrorElementEditor::onStartTimeChanged);
  connect(ui->fakelevel_comboBox, &QComboBox::currentTextChanged, this,
          &ErrorElementEditor::onFakeLevelChanged);
  connect(ui->efficiency_spinBox,
          static_cast<void (QDoubleSpinBox::*)(double)>(
              &QDoubleSpinBox::valueChanged),
          this, &ErrorElementEditor::onEfficiencyChanged);
  connect(ui->surveydelay_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ErrorElementEditor::onSurveyDelayChanged);
  connect(ui->repeatNotification_checkBox, &QCheckBox::checkStateChanged, this,
          &ErrorElementEditor::onRepeatNotifyChanged);
  connect(ui->cleanAfter_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ErrorElementEditor::onClearAfterChanged);
  connect(ui->notifyAfter_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ErrorElementEditor::onNotifyAfterChanged);
  connect(ui->allowLateRepair_checkBox, &QCheckBox::checkStateChanged, this,
          &ErrorElementEditor::onAllowLateRepairChanged);
  connect(ui->loa_comboBox, &QComboBox::currentTextChanged, this,
          &ErrorElementEditor::onLoaChanged);
  connect(ui->loadelay_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ErrorElementEditor::onLoaDelayChanged);

  onSurveyItemChanged(nullptr);
  onErrorTypeChanged(ui->errortype_comboBox->currentText());
  ui->fakelevel_comboBox->setEnabled(ui->diagnostic_comboBox->currentText() ==
                                     "true");
  ui->allowLateRepair_checkBox->setEnabled(ui->cleanAfter_spinBox->value() >=
                                           0);
  ui->repeatNotification_checkBox->setEnabled(
      ui->notifyAfter_spinBox->value() >= 0);
}

ErrorElementEditor::~ErrorElementEditor() { delete ui; }

void ErrorElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void ErrorElementEditor::onErrorTypeChanged(const QString &errortype) {
  m_element->parameters()["type"] = errortype;
  ui->efficiency_spinBox->setEnabled(errortype.contains("ineff"));
  emit dataChanged(m_element);
}

void ErrorElementEditor::onDiagnosticsChanged(const QString &diagnostics) {
  m_element->parameters()["diagnostics"] = diagnostics;
  if (diagnostics == "true") {
    ui->fakelevel_comboBox->setEnabled(true);
  } else {
    ui->fakelevel_comboBox->setCurrentIndex(0);
    ui->fakelevel_comboBox->setEnabled(false);
  }
  emit dataChanged(m_element);
}

void ErrorElementEditor::onSurveyItemChanged(QListWidgetItem *it) {
  Q_UNUSED(it)
  QString correctList;
  QListWidgetItem *item;
  for (int i = 0; i < ui->surveycorrect_list->count(); i++) {
    item = ui->surveycorrect_list->item(i);
    if (item->checkState()) {
      correctList += item->text();
      if (i < ui->surveycorrect_list->count() - 1) {
        correctList += ",";
      }
    }
  }
  if (correctList.isEmpty()) {
    m_element->parameters().remove("surveyOk");
  } else {
    m_element->parameters()["surveyOk"] = correctList;
  }

  QString wrongList;
  for (int i = 0; i < ui->surveymissed_list->count(); i++) {
    item = ui->surveymissed_list->item(i);
    if (item->checkState()) {
      wrongList += item->text();
      if (i < ui->surveymissed_list->count() - 1) {
        wrongList += ",";
      }
    }
  }
  if (wrongList.isEmpty()) {
    m_element->parameters().remove("survey");
  } else {
    m_element->parameters()["survey"] = wrongList;
  }
  ui->surveydelay_spinBox->setEnabled(!correctList.isEmpty() ||
                                      !wrongList.isEmpty());
  emit dataChanged(m_element);
}

void ErrorElementEditor::onFakeLevelChanged(const QString &fakelevel) {
  Q_UNUSED(fakelevel)
  int idx{ui->fakelevel_comboBox->currentIndex()};
  if (idx > 0) {
    m_element->parameters()["fake"] = idx;
  } else {
    m_element->parameters().remove("fake");
  }
  emit dataChanged(m_element);
}

void ErrorElementEditor::onClearAfterChanged(int value) {
  Q_UNUSED(value)
  m_element->parameters()["clear"] = ui->cleanAfter_spinBox->value();
  ui->allowLateRepair_checkBox->setEnabled(ui->cleanAfter_spinBox->value() >=
                                           0);
  emit dataChanged(m_element);
}

void ErrorElementEditor::onNotifyAfterChanged(int value) {
  Q_UNUSED(value)
  m_element->parameters()["notify"] = ui->notifyAfter_spinBox->value();
  ui->repeatNotification_checkBox->setEnabled(
      ui->notifyAfter_spinBox->value() >= 0);
  emit dataChanged(m_element);
}

void ErrorElementEditor::onEfficiencyChanged(double value) {
  Q_UNUSED(value)
  m_element->parameters()["efficiency"] = ui->efficiency_spinBox->value();
  emit dataChanged(m_element);
}

void ErrorElementEditor::onSurveyDelayChanged(int value) {
  Q_UNUSED(value)
  m_element->parameters()["surveyDelay"] = ui->surveydelay_spinBox->value();
  emit dataChanged(m_element);
}

void ErrorElementEditor::onRepeatNotifyChanged(int state) {
  Q_UNUSED(state)
  m_element->parameters()["repeatNotify"] =
      ui->repeatNotification_checkBox->isChecked();
  emit dataChanged(m_element);
}

void ErrorElementEditor::onAllowLateRepairChanged(int state) {
  Q_UNUSED(state)
  m_element->parameters()["allowLateRepair"] =
      ui->allowLateRepair_checkBox->isChecked();
  emit dataChanged(m_element);
}

void ErrorElementEditor::onLoaChanged(const QString &loa) {
  if (loa != "") {
    m_element->parameters()["loa"] = ui->loa_comboBox->currentText();
    ui->loadelay_spinBox->setEnabled(true);
  } else {
    m_element->parameters().remove("loa");
    m_element->parameters().remove("loadelay");
    ui->loadelay_spinBox->setEnabled(false);
  }
  emit dataChanged(m_element);
}

void ErrorElementEditor::onLoaDelayChanged(int value) {
  m_element->parameters()["loadelay"] = value;
  emit dataChanged(m_element);
}
