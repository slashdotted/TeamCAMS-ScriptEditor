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
#include "accesselementeditor.h"
#include "ui_accesselementeditor.h"

QString AccessElementEditor::accessTypeName(int type) const
{
    switch (type) {
    case 0:
        return tr("Full View (autostart)");
    case 1:
        return tr("Full View (autorestart)");
    case 2:
        return tr("Full View");
    case 3:
        return tr("System Overview");
    case 4:
        return tr("Command Panel");
    case 5:
        return tr("Assistance Screen");
    case 6:
        return tr("Assistance Selector");
    case 7:
        return tr("Assistance Panel");
    case 8:
        return tr("Full Command Panel");
    case 9:
        return tr("Graphs");
    case 10:
        return tr("Repair Panel");
    case 11:
        return tr("N2 Logging Panel");
    case 12:
        return tr("Transmission Panel");
    case 13:
        return tr("Disabled");
    }
    return {};
}

AccessElementEditor::AccessElementEditor(Element *e, QWidget *parent)
    : Editor(parent), ui(new Ui::AccessElementEditor), m_element{e} {
  ui->setupUi(this);
  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));
  QStringList names;
  for (auto i{0}; i < 14; ++i) {
      names.push_back(accessTypeName(i));
  }
  ui->accessTypeCombo->addItems(names);
  if (m_element->parameters().contains("type")) {
    ui->accessTypeCombo->setCurrentIndex(
        m_element->parameters()["type"].toInt());
  }
  if (m_element->parameters().contains("username")) {
    ui->usernameEdit->setText(m_element->parameters()["username"].toString());
  }
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &AccessElementEditor::onStartTimeChanged);
  connect(ui->usernameEdit, &QLineEdit::textChanged, this,
          &AccessElementEditor::onUsernameChanged);
  connect(ui->accessTypeCombo,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &AccessElementEditor::onAccessTypeChanged);

  m_element->parameters()["username"] =
      ui->usernameEdit->text().toHtmlEscaped();
  m_element->parameters()["type"] = ui->accessTypeCombo->currentIndex();
}

AccessElementEditor::~AccessElementEditor() { delete ui; }

void AccessElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void AccessElementEditor::onUsernameChanged() {
  m_element->parameters()["username"] =
      ui->usernameEdit->text().toHtmlEscaped();
  emit dataChanged(m_element);
}

void AccessElementEditor::onAccessTypeChanged() {
  m_element->parameters()["type"] = ui->accessTypeCombo->currentIndex();
  emit dataChanged(m_element);
}
