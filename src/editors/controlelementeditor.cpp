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
#include "controlelementeditor.h"
#include "ui_controlelementeditor.h"

ControlElementEditor::ControlElementEditor(Element *e, QWidget *parent)
    : Editor(parent), ui(new Ui::ControlElementEditor), m_element{e} {
  ui->setupUi(this);

  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));

  ui->deviceCommand_comboBox->addItems({"",
                                        "sauerstoff.flow.high",
                                        "sauerstoff.flow.medium",
                                        "sauerstoff.flow.standard",
                                        "sauerstoff.general.auto on",
                                        "sauerstoff.general.flow on",
                                        "sauerstoff.general.flow off",
                                        "kohlendioxid.flow.high",
                                        "kohlendioxid.flow.medium",
                                        "kohlendioxid.flow.standard",
                                        "kohlendioxid.general.auto on",
                                        "kohlendioxid.general.scrub on",
                                        "kohlendioxid.general.scrub off",
                                        "feuchtigkeit.flow.high",
                                        "feuchtigkeit.flow.medium",
                                        "feuchtigkeit.flow.standard",
                                        "feuchtigkeit.general.auto on",
                                        "feuchtigkeit.general.dehumidify on",
                                        "feuchtigkeit.general.dehumidify off",
                                        "stickstoff.general.auto on",
                                        "stickstoff.general.flow on",
                                        "stickstoff.general.flow off",
                                        "stickstoff.flow.high",
                                        "stickstoff.flow.medium",
                                        "stickstoff.flow.standard",
                                        "stickstoff.vent.high",
                                        "stickstoff.vent.medium",
                                        "stickstoff.vent.standard",
                                        "stickstoff.flow.high",
                                        "stickstoff.flow.medium",
                                        "stickstoff.flow.standard",
                                        "temperature.general.auto on",
                                        "temperature.general.heat on",
                                        "temperature.general.off",
                                        "temperature.general.cool on",
                                        "temperature.heater.high",
                                        "temperature.heater.medium",
                                        "temperature.heater.standard",
                                        "temperature.cooler.high",
                                        "temperature.cooler.medium",
                                        "temperature.cooler.standard"});

  if (m_element->parameters().contains("command")) {
    ui->deviceCommand_comboBox->setCurrentText(
        m_element->parameters()["command"].toString());
  }

  connect(ui->deviceCommand_comboBox, &QComboBox::currentTextChanged, this,
          &ControlElementEditor::onDeviceCommandChanged);
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &ControlElementEditor::onStartTimeChanged);
  emit dataChanged(m_element);
}

ControlElementEditor::~ControlElementEditor() { delete ui; }

void ControlElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void ControlElementEditor::onDeviceCommandChanged(const QString &cmd) {
  m_element->parameters()["command"] = cmd;
  emit dataChanged(m_element);
}
