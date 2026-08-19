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
#include "interfaceelementeditor.h"
#include "ui_interfaceelementeditor.h"
#include <QDebug>
#include <QMap>
#include <QSpinBox>

InterfaceElementEditor::InterfaceElementEditor(Element *e, QWidget *parent)
    : Editor(parent), m_element{e}, ui(new Ui::InterfaceElementEditor) {
  ui->setupUi(this);
  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));

  ui->interfaceElement->addItems({"oxygenscope",
                                  "pressurescope",
                                  "carbonscope",
                                  "tempscope",
                                  "humidityscope",
                                  "systemmonitor",
                                  "oxtankdisplay",
                                  "oxseconddisplay",
                                  "nitankdisplay",
                                  "niseconddisplay",
                                  "mixerdisplay",
                                  "cofilterlabel",
                                  "coolingmachinelabel",
                                  "heatingmachinelabel",
                                  "dehumidlabel",
                                  "ventlabel",
                                  "oxygenpanel",
                                  "carbonpanel",
                                  "humiditypanel",
                                  "pressurepanel",
                                  "temppanel",
                                  "masteralarm",
                                  "assistanceselector",
                                  "repairbutton",
                                  "oxygenpanelgeneral",
                                  "oxygenpanelflow",
                                  "carbonpanelgeneral",
                                  "carbonpanelscrubber",
                                  "humiditypanelgeneral",
                                  "humiditypanellevel",
                                  "pressurepanelgeneral",
                                  "pressurepanelflow",
                                  "temppanelgeneral",
                                  "temppanelheater",
                                  "temppanelcooler",
                                  "loa_1.button",
                                  "loa_2.button",
                                  "loa_3.button",
                                  "loa_4.button",
                                  "loa_5.button",
                                  "loa_6.button",
                                  "assistancepanel",
                                  "chatbox",
                                  "alternatemessaging",
                                  "controldivider",
                                  "strengthtitle",
                                  "systemoverview",
                                  "repairtask",
                                  "transmissioncontrol",
                                  "n2loggingtask",
                                  "devicecontrol",
                                  "assistancebox",
                                  "survey",
                                  "automationnotification",
                                  "tempcontrolaligncenter",
                                  "keepcontrolsvisible",
                                  "transmissionchecksound",
                                  "buttonsound",
                                  "togglesound",
                                  "alarmsound",
                                  "loggingsound",
                                  "messagesound",
                                  "messaginginfront",
                                  "fullscreen"});

  if (m_element->parameters().contains("display")) {
    ui->interfaceElement->setCurrentText(
        m_element->parameters()["display"].toString());
  }

  if (m_element->parameters().contains("users")) {
    ui->users->setText(m_element->parameters()["users"].toString());
  }

  if (m_element->parameters().contains("enabled")) {
    ui->enabledCheck->setChecked(m_element->parameters()["enabled"].toBool());
  }

  if (m_element->parameters().contains("visible")) {
    ui->visibleCheck->setChecked(m_element->parameters()["visible"].toBool());
  }

  connect(ui->enabledCheck, &QCheckBox::checkStateChanged, this,
          &InterfaceElementEditor::onEnabledChanged);
  connect(ui->visibleCheck, &QCheckBox::checkStateChanged, this,
          &InterfaceElementEditor::onVisibleChanged);
  connect(ui->interfaceElement, &QComboBox::currentTextChanged, this,
          &InterfaceElementEditor::onInterfaceElementChanged);
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &InterfaceElementEditor::onStartTimeChanged);
  connect(ui->users, &QLineEdit::textChanged, this,
          &InterfaceElementEditor::onUsersChanged);
  updateCheckedAttributes();
}

InterfaceElementEditor::~InterfaceElementEditor() { delete ui; }

void InterfaceElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void InterfaceElementEditor::onInterfaceElementChanged(const QString &element) {
  Q_UNUSED(element)
  updateCheckedAttributes();
}

void InterfaceElementEditor::onEnabledChanged(int state) {
  Q_UNUSED(state)
  updateCheckedAttributes();
}

void InterfaceElementEditor::onVisibleChanged(int state) {
  Q_UNUSED(state)
  updateCheckedAttributes();
}

void InterfaceElementEditor::onUsersChanged(const QString &value) {
  Q_UNUSED(value)
  updateCheckedAttributes();
}

void InterfaceElementEditor::updateCheckedAttributes() {
  m_element->parameters()["display"] = ui->interfaceElement->currentText();
  m_element->parameters()["enabled"] = ui->enabledCheck->isChecked();
  m_element->parameters()["visible"] = ui->visibleCheck->isChecked();
  static QMap<QString, bool> visibility{{"oxygenscope", true},
                                        {"pressurescope", true},
                                        {"carbonscope", true},
                                        {"tempscope", true},
                                        {"humidityscope", true},
                                        {"systemmonitor", true},
                                        {"oxtankdisplay", true},
                                        {"oxseconddisplay", true},
                                        {"nitankdisplay", true},
                                        {"niseconddisplay", true},
                                        {"mixerdisplay", true},
                                        {"cofilterlabel", true},
                                        {"coolingmachinelabel", true},
                                        {"heatingmachinelabel", true},
                                        {"dehumidlabel", true},
                                        {"ventlabel", true},
                                        {"oxygenpanel", false},
                                        {"carbonpanel", false},
                                        {"humiditypanel", false},
                                        {"pressurepanel", false},
                                        {"temppanel", false},
                                        {"masteralarm", true},
                                        {"assistanceselector", true},
                                        {"repairbutton", true},
                                        {"oxygenpanelgeneral", false},
                                        {"oxygenpanelflow", false},
                                        {"carbonpanelgeneral", false},
                                        {"carbonpanelscrubber", false},
                                        {"humiditypanelgeneral", false},
                                        {"humiditypanellevel", false},
                                        {"pressurepanelgeneral", false},
                                        {"pressurepanelflow", false},
                                        {"temppanelgeneral", false},
                                        {"temppanelheater", false},
                                        {"temppanelcooler", false},
                                        {"loa_1.button", false},
                                        {"loa_2.button", false},
                                        {"loa_3.button", false},
                                        {"loa_4.button", false},
                                        {"loa_5.button", false},
                                        {"loa_6.button", false},
                                        {"assistancepanel", true},
                                        {"chatbox", true},
                                        {"alternatemessaging", true},
                                        {"controldivider", true},
                                        {"strengthtitle", true},
                                        {"systemoverview", true},
                                        {"repairtask", true},
                                        {"transmissioncontrol", true},
                                        {"n2loggingtask", true},
                                        {"devicecontrol", true},
                                        {"assistancebox", true},
                                        {"survey", true},
                                        {"automationnotification", true},
                                        {"tempcontrolaligncenter", true},
                                        {"keepcontrolsvisible", true},
                                        {"transmissionchecksound", false},
                                        {"buttonsound", false},
                                        {"togglesound", false},
                                        {"alarmsound", false},
                                        {"loggingsound", false},
                                        {"messagesound", false},
                                        {"messaginginfront", false},
                                        {"fullscreen", false}};

  static QMap<QString, bool> enabled{{"oxygenscope", false},
                                     {"pressurescope", false},
                                     {"carbonscope", false},
                                     {"tempscope", false},
                                     {"humidityscope", false},
                                     {"systemmonitor", false},
                                     {"oxtankdisplay", false},
                                     {"oxseconddisplay", false},
                                     {"nitankdisplay", false},
                                     {"niseconddisplay", false},
                                     {"mixerdisplay", false},
                                     {"cofilterlabel", false},
                                     {"coolingmachinelabel", false},
                                     {"heatingmachinelabel", false},
                                     {"dehumidlabel", false},
                                     {"ventlabel", false},
                                     {"oxygenpanel", true},
                                     {"carbonpanel", true},
                                     {"humiditypanel", true},
                                     {"pressurepanel", true},
                                     {"temppanel", true},
                                     {"masteralarm", false},
                                     {"assistanceselector", false},
                                     {"repairbutton", false},
                                     {"oxygenpanelgeneral", true},
                                     {"oxygenpanelflow", true},
                                     {"carbonpanelgeneral", true},
                                     {"carbonpanelscrubber", true},
                                     {"humiditypanelgeneral", true},
                                     {"humiditypanellevel", true},
                                     {"pressurepanelgeneral", true},
                                     {"pressurepanelflow", true},
                                     {"temppanelgeneral", true},
                                     {"temppanelheater", true},
                                     {"temppanelcooler", true},
                                     {"loa_1.button", true},
                                     {"loa_2.button", true},
                                     {"loa_3.button", true},
                                     {"loa_4.button", true},
                                     {"loa_5.button", true},
                                     {"loa_6.button", true},
                                     {"assistancepanel", false},
                                     {"chatbox", false},
                                     {"alternatemessaging", false},
                                     {"controldivider", false},
                                     {"strengthtitle", false},
                                     {"systemoverview", false},
                                     {"repairtask", false},
                                     {"transmissioncontrol", false},
                                     {"n2loggingtask", false},
                                     {"devicecontrol", false},
                                     {"assistancebox", false},
                                     {"survey", false},
                                     {"automationnotification", false},
                                     {"tempcontrolaligncenter", false},
                                     {"keepcontrolsvisible", false},
                                     {"transmissionchecksound", true},
                                     {"buttonsound", true},
                                     {"togglesound", true},
                                     {"alarmsound", true},
                                     {"loggingsound", true},
                                     {"messagesound", true},
                                     {"messaginginfront", true},
                                     {"fullscreen", true}};

  ui->enabledCheck->setEnabled(enabled[ui->interfaceElement->currentText()]);
  ui->visibleCheck->setEnabled(visibility[ui->interfaceElement->currentText()]);

  if (!ui->enabledCheck->isEnabled()) {
    ui->enabledCheck->setChecked(false);
    m_element->parameters().remove("enabled");
  }

  if (!ui->visibleCheck->isEnabled()) {
    ui->visibleCheck->setChecked(false);
    m_element->parameters().remove("visible");
  }

  if (ui->users->text().isEmpty()) {
    m_element->parameters().remove("users");
  } else {
    m_element->parameters()["users"] = ui->users->text();
  }

  emit dataChanged(m_element);
}
