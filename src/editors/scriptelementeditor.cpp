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
#include "scriptelementeditor.h"
#include "ui_scriptelementeditor.h"

ScriptElementEditor::ScriptElementEditor(Element *e, QWidget *parent)
    : Editor(parent), ui(new Ui::ScriptElementEditor), m_element{e} {
  ui->setupUi(this);
  if (m_element->parameters().contains("adaptive")) {
    ui->adaptiveControlEnabled->setChecked(
        m_element->parameters()["adaptive"].toBool());
  }
  connect(ui->adaptiveControlEnabled, &QCheckBox::checkStateChanged, this,
          &ScriptElementEditor::onAdaptiveControlEnabledChanged);
  connect(ui->adaptiveControlType, &QComboBox::currentTextChanged, this,
          &ScriptElementEditor::onAdaptiveControlTypeChanged);
  connect(ui->maxLOAChange,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onMaxLOAChangeChanged);
  connect(ui->txBaseline,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onTxBaselineChanged);
  connect(ui->txBaselineFault,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onTxBaselineFaultChanged);

  connect(ui->txA,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onTxAChanged);
  connect(ui->txB,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onTxBChanged);
  connect(ui->txC,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onTxCChanged);
  connect(ui->txD,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onTxDChanged);
  connect(ui->txE,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onTxEChanged);

  connect(ui->logBaseline,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onLogBaselineChanged);
  connect(ui->logBaselineFault,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onLogBaselineFaultChanged);

  connect(ui->logA,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onLogAChanged);
  connect(ui->logB,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onLogBChanged);
  connect(ui->logC,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onLogCChanged);
  connect(ui->logD,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onLogDChanged);
  connect(ui->logE,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &ScriptElementEditor::onLogEChanged);

  if (m_element->parameters().contains("adaptiveControl")) {
    ui->adaptiveControlType->setCurrentText(
        m_element->parameters()["adaptiveControl"].toString());
  }
  if (m_element->parameters().contains("adaptiveControlMaxChange")) {
    ui->maxLOAChange->setValue(
        m_element->parameters()["adaptiveControlMaxChange"].toInt());
  }
  if (m_element->parameters().contains("reactionbaselinetransmission")) {
    ui->txBaseline->setValue(
        m_element->parameters()["reactionbaselinetransmission"].toInt());
  }
  if (m_element->parameters().contains(
          "reactionbaselinetransmissionDuringFault")) {
    ui->txBaselineFault->setValue(
        m_element->parameters()["reactionbaselinetransmissionDuringFault"]
            .toInt());
  }
  if (m_element->parameters().contains("reactionbaselinelogging")) {
    ui->logBaseline->setValue(
        m_element->parameters()["reactionbaselinelogging"].toInt());
  }
  if (m_element->parameters().contains("reactionbaselineloggingduringfault")) {
    ui->logBaselineFault->setValue(
        m_element->parameters()["reactionbaselineloggingduringfault"].toInt());
  }

  if (m_element->parameters().contains(
          "reactiontimeloggingpredefinedintervals_a")) {
    ui->logA->setValue(
        m_element->parameters()["reactiontimeloggingpredefinedintervals_a"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimeloggingpredefinedintervals_b")) {
    ui->logB->setValue(
        m_element->parameters()["reactiontimeloggingpredefinedintervals_b"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimeloggingpredefinedintervals_c")) {
    ui->logC->setValue(
        m_element->parameters()["reactiontimeloggingpredefinedintervals_c"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimeloggingpredefinedintervals_d")) {
    ui->logD->setValue(
        m_element->parameters()["reactiontimeloggingpredefinedintervals_d"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimeloggingpredefinedintervals_e")) {
    ui->logE->setValue(
        m_element->parameters()["reactiontimeloggingpredefinedintervals_e"]
            .toInt());
  }

  if (m_element->parameters().contains(
          "reactiontimetransmissionpredefinedintervals_a")) {
    ui->txA->setValue(
        m_element->parameters()["reactiontimetransmissionpredefinedintervals_a"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimetransmissionpredefinedintervals_b")) {
    ui->txB->setValue(
        m_element->parameters()["reactiontimetransmissionpredefinedintervals_b"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimetransmissionpredefinedintervals_c")) {
    ui->txC->setValue(
        m_element->parameters()["reactiontimetransmissionpredefinedintervals_c"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimetransmissionpredefinedintervals_d")) {
    ui->txD->setValue(
        m_element->parameters()["reactiontimetransmissionpredefinedintervals_d"]
            .toInt());
  }
  if (m_element->parameters().contains(
          "reactiontimetransmissionpredefinedintervals_e")) {
    ui->txE->setValue(
        m_element->parameters()["reactiontimetransmissionpredefinedintervals_e"]
            .toInt());
  }

  onAdaptiveControlEnabledChanged();
}

ScriptElementEditor::~ScriptElementEditor() { delete ui; }

void ScriptElementEditor::onAdaptiveControlEnabledChanged() {
  m_element->parameters()["adaptive"] = ui->adaptiveControlEnabled->isChecked();
  ui->adaptiveControlType->setEnabled(ui->adaptiveControlEnabled->isChecked());
  onAdaptiveControlTypeChanged();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onAdaptiveControlTypeChanged() {
  m_element->parameters()["adaptiveControl"] =
      ui->adaptiveControlType->currentText();
  ui->logA->setEnabled(m_element->parameters()["adaptiveControl"] ==
                       "predefinedlogging");
  ui->logB->setEnabled(m_element->parameters()["adaptiveControl"] ==
                       "predefinedlogging");
  ui->logC->setEnabled(m_element->parameters()["adaptiveControl"] ==
                       "predefinedlogging");
  ui->logD->setEnabled(m_element->parameters()["adaptiveControl"] ==
                       "predefinedlogging");
  ui->logE->setEnabled(m_element->parameters()["adaptiveControl"] ==
                       "predefinedlogging");
  ui->txA->setEnabled(m_element->parameters()["adaptiveControl"] ==
                      "predefinedtransmission");
  ui->txB->setEnabled(m_element->parameters()["adaptiveControl"] ==
                      "predefinedtransmission");
  ui->txC->setEnabled(m_element->parameters()["adaptiveControl"] ==
                      "predefinedtransmission");
  ui->txD->setEnabled(m_element->parameters()["adaptiveControl"] ==
                      "predefinedtransmission");
  ui->txE->setEnabled(m_element->parameters()["adaptiveControl"] ==
                      "predefinedtransmission");

  auto baselineBased =
      m_element->parameters()["adaptiveControl"] == "logging" ||
      m_element->parameters()["adaptiveControl"] == "transmission" ||
      m_element->parameters()["adaptiveControl"] == "combined";
  ui->txBaselineFault->setEnabled(
      m_element->parameters()["adaptiveControl"] == "transmission" ||
      m_element->parameters()["adaptiveControl"] == "combined");
  ui->txBaseline->setEnabled(
      m_element->parameters()["adaptiveControl"] == "transmission" ||
      m_element->parameters()["adaptiveControl"] == "combined");
  ui->logBaseline->setEnabled(
      m_element->parameters()["adaptiveControl"] == "logging" ||
      m_element->parameters()["adaptiveControl"] == "combined");
  ui->logBaselineFault->setEnabled(
      m_element->parameters()["adaptiveControl"] == "logging" ||
      m_element->parameters()["adaptiveControl"] == "combined");
  ui->maxLOAChange->setEnabled(
      !baselineBased && m_element->parameters()["adaptiveControl"] != "none");
  emit dataChanged(m_element);
}

void ScriptElementEditor::onMaxLOAChangeChanged() {
  m_element->parameters()["adaptiveControlMaxChange"] =
      ui->maxLOAChange->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onTxBaselineChanged() {
  m_element->parameters()["reactionbaselinetransmission"] =
      ui->txBaseline->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onTxBaselineFaultChanged() {
  m_element->parameters()["reactionbaselinetransmissionDuringFault"] =
      ui->txBaselineFault->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onLogBaselineChanged() {
  m_element->parameters()["reactionbaselinelogging"] = ui->logBaseline->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onLogBaselineFaultChanged() {
  m_element->parameters()["reactionbaselineloggingduringfault"] =
      ui->logBaselineFault->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onTxAChanged() {
  m_element->parameters()["reactiontimetransmissionpredefinedintervals_a"] =
      ui->txA->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onTxBChanged() {
  m_element->parameters()["reactiontimetransmissionpredefinedintervals_b"] =
      ui->txB->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onTxCChanged() {
  m_element->parameters()["reactiontimetransmissionpredefinedintervals_c"] =
      ui->txC->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onTxDChanged() {
  m_element->parameters()["reactiontimetransmissionpredefinedintervals_d"] =
      ui->txD->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onTxEChanged() {
  m_element->parameters()["reactiontimetransmissionpredefinedintervals_e"] =
      ui->txE->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onLogAChanged() {
  m_element->parameters()["reactiontimeloggingpredefinedintervals_a"] =
      ui->logA->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onLogBChanged() {
  m_element->parameters()["reactiontimeloggingpredefinedintervals_b"] =
      ui->logB->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onLogCChanged() {
  m_element->parameters()["reactiontimeloggingpredefinedintervals_c"] =
      ui->logC->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onLogDChanged() {
  m_element->parameters()["reactiontimeloggingpredefinedintervals_d"] =
      ui->logD->value();
  emit dataChanged(m_element);
}

void ScriptElementEditor::onLogEChanged() {
  m_element->parameters()["reactiontimeloggingpredefinedintervals_e"] =
      ui->logE->value();
  emit dataChanged(m_element);
}
