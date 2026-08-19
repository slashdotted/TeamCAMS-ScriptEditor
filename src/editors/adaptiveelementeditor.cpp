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
#include "adaptiveelementeditor.h"
#include "ui_adaptiveelementeditor.h"

AdaptiveElementEditor::AdaptiveElementEditor(Element *e, QWidget *parent)
    : Editor(parent), ui(new Ui::AdaptiveElementEditor), m_element{e} {
  ui->setupUi(this);
  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));

  ui->command_comboBox->addItems({"", "onPeriod", "onSamples", "onPast"});

  if (m_element->parameters().contains("onSamples")) {
    ui->command_comboBox->setCurrentText("onSamples");
    ui->samples_spinBox->setValue(m_element->parameters()["onSamples"].toInt());
  } else if (m_element->parameters().contains("onPast")) {
    ui->command_comboBox->setCurrentText("onPast");
    ui->pastPeriod_spinBox->setValue(m_element->parameters()["onPast"].toInt());
  } else if (m_element->parameters().contains("onPeriodFrom") &&
             m_element->parameters().contains("onPeriodTo")) {
    ui->command_comboBox->setCurrentText("onPeriod");
    ui->periodFrom_spinBox->setValue(
        m_element->parameters()["onPeriodFrom"].toInt());
    ui->periodTo_spinBox->setValue(
        m_element->parameters()["onPeriodTo"].toInt());
  }
  ui->pastPeriod_spinBox->setEnabled(false);
  ui->samples_spinBox->setEnabled(false);

  connect(ui->periodFrom_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &AdaptiveElementEditor::onDataChanged);
  connect(ui->periodTo_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &AdaptiveElementEditor::onDataChanged);
  connect(ui->samples_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &AdaptiveElementEditor::onDataChanged);
  connect(ui->pastPeriod_spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &AdaptiveElementEditor::onDataChanged);
  connect(ui->command_comboBox, &QComboBox::currentTextChanged, this,
          &AdaptiveElementEditor::onCommandChanged);
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &AdaptiveElementEditor::onStartTimeChanged);

  onCommandChanged(ui->command_comboBox->currentText());
}

AdaptiveElementEditor::~AdaptiveElementEditor() { delete ui; }

void AdaptiveElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void AdaptiveElementEditor::onCommandChanged(const QString &command) {
  ui->pastPeriod_spinBox->setEnabled(command == "onPast");
  ui->samples_spinBox->setEnabled(command == "onSamples");
  ui->periodFrom_spinBox->setEnabled(command == "onPeriod");
  ui->periodTo_spinBox->setEnabled(command == "onPeriod");
  m_element->parameters() = {};
  if (command == "onPast") {
    m_element->parameters()["onPast"] = ui->pastPeriod_spinBox->value();
  } else if (command == "onSamples") {
    m_element->parameters()["onSamples"] = ui->samples_spinBox->value();
  } else if (command == "onPeriod") {
    m_element->parameters()["onPeriodFrom"] = ui->periodFrom_spinBox->value();
    m_element->parameters()["onPeriodTo"] = ui->periodTo_spinBox->value();
  }
  emit dataChanged(m_element);
}

void AdaptiveElementEditor::onDataChanged() {
  onCommandChanged(ui->command_comboBox->currentText());
}
