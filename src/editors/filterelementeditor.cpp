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
#include "filterelementeditor.h"
#include "ui_filterelementeditor.h"

FilterElementEditor::FilterElementEditor(Element *e, QWidget *parent)
    : Editor{parent}, ui(new Ui::FilterElementEditor), m_element{e} {
  ui->setupUi(this);
  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));
  ui->messageTypeCombo->addItems(
      {"server_update", "client_update", "client_trigger", "server_notify"});
  if (m_element->parameters().contains("type")) {
    ui->messageTypeCombo->setCurrentText(
        m_element->parameters()["type"].toString());
  }
  if (m_element->parameters().contains("user")) {
    ui->usernameEdit->setText(m_element->parameters()["user"].toString());
  }
  if (m_element->parameters().contains("key")) {
    ui->keyPatternEdit->setText(m_element->parameters()["key"].toString());
  }
  if (m_element->parameters().contains("enabled")) {
    ui->blockCheck->setChecked(m_element->parameters()["enabled"].toBool());
  }
  if (m_element->parameters().contains("feedback")) {
    ui->feedbackCheckbox->setChecked(
        m_element->parameters()["feedback"].toBool());
  }

  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &FilterElementEditor::onStartTimeChanged);
  connect(ui->blockCheck, &QCheckBox::checkStateChanged, this,
          &FilterElementEditor::onEnabledChanged);
  connect(ui->feedbackCheckbox, &QCheckBox::checkStateChanged, this,
          &FilterElementEditor::onFeedbackChanged);
  connect(ui->messageTypeCombo, &QComboBox::currentTextChanged, this,
          &FilterElementEditor::onTypeChanged);
  connect(ui->usernameEdit, &QLineEdit::textChanged, this,
          &FilterElementEditor::onUserChanged);
  connect(ui->keyPatternEdit, &QLineEdit::textChanged, this,
          &FilterElementEditor::onKeyChanged);

  onTypeChanged(ui->messageTypeCombo->currentText());
  onUserChanged(ui->usernameEdit->text());
  onKeyChanged(ui->keyPatternEdit->text());
  onFeedbackChanged();
  onEnabledChanged();
}

void FilterElementEditor::onTypeChanged(const QString &type) {
  m_element->parameters()["type"] = type;
  if (type != "client_update") {
    ui->feedbackCheckbox->setChecked(false);
    ui->feedbackCheckbox->setEnabled(false);
  } else {
    ui->feedbackCheckbox->setEnabled(true);
  }
  emit dataChanged(m_element);
}

void FilterElementEditor::onKeyChanged(const QString &key) {
  m_element->parameters()["key"] = key;
  emit dataChanged(m_element);
}

void FilterElementEditor::onUserChanged(const QString &user) {
  m_element->parameters()["user"] = user;
  emit dataChanged(m_element);
}

void FilterElementEditor::onFeedbackChanged() {
  if (ui->feedbackCheckbox->isEnabled()) {
    m_element->parameters()["feedback"] = ui->feedbackCheckbox->isChecked();
  } else {
    m_element->parameters().remove("feedback");
  }
  emit dataChanged(m_element);
}

void FilterElementEditor::onEnabledChanged() {
  m_element->parameters()["enabled"] = ui->blockCheck->isChecked();
  emit dataChanged(m_element);
}

FilterElementEditor::~FilterElementEditor() { delete ui; }

void FilterElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}
