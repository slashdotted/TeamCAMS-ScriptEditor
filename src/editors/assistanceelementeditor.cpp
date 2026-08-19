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
#include "assistanceelementeditor.h"
#include "ui_assistanceelementeditor.h"

AssistanceElementEditor::AssistanceElementEditor(Element *e, QWidget *parent)
    : Editor(parent), m_element{e}, ui(new Ui::AssistanceElementEditor) {
  ui->setupUi(this);

  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));

  ui->type_comboBox->addItems(
      {"loa1", "loa2", "loa3", "loa4", "loa5", "loa6", "ask", "force"});

  if (m_element->parameters().contains("type")) {
    ui->type_comboBox->setCurrentText(
        m_element->parameters()["type"].toString());
  } else {
    m_element->parameters()["type"] = "loa1";
  }

  if (m_element->parameters().contains("notify")) {
    if (m_element->parameters()["notify"].toBool()) {
      ui->notify_checkBox->setChecked(true);
    }
  }

  connect(ui->type_comboBox, &QComboBox::currentTextChanged, this,
          &AssistanceElementEditor::onAssistanceTypeChanged);
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &AssistanceElementEditor::onStartTimeChanged);
  connect(ui->notify_checkBox, &QCheckBox::checkStateChanged, this,
          &AssistanceElementEditor::onNotifyChanged);
  emit dataChanged(m_element);
}

AssistanceElementEditor::~AssistanceElementEditor() { delete ui; }

void AssistanceElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void AssistanceElementEditor::onAssistanceTypeChanged(const QString &type) {
  m_element->parameters()["type"] = type;
  emit dataChanged(m_element);
}

void AssistanceElementEditor::onNotifyChanged() {
  if (ui->notify_checkBox->isChecked()) {
    m_element->parameters()["notify"] = true;
  } else {
    m_element->parameters().remove("notify");
  }
  emit dataChanged(m_element);
}
