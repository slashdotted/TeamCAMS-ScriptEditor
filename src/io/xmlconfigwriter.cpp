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
#include "xmlconfigwriter.h"
#include <QDebug>
#include <QFile>

void XMLConfigWriter::write(QXmlStreamWriter &sw, ElementList &elist) {
  sw.setAutoFormatting(true);
  sw.writeStartDocument();
  sw.writeStartElement("script");
  // Find script element
  for (auto e : elist) {
    if (e->type() == ScriptElementType) {
      writeScriptElement(e, sw);
    }
  }
  // Write all other elements
  for (auto e : elist) {
    switch (e->type()) {
    case ErrorElementType:
      writeErrorElement(e, sw);
      break;
    case InterfaceElementType:
      writeInterfaceElement(e, sw);
      break;
    case AdaptiveElementType:
      writeAdaptiveElement(e, sw);
      break;
    case CodeElementType:
      writeCodeElement(e, sw);
      break;
    case DurationElementType:
      writeDurationElement(e, sw);
      break;
    case ControlElementType:
      writeControlElement(e, sw);
      break;
    case QuestionElementType:
      writeQuestionElement(e, sw);
      break;
    case AssistanceElementType:
      writeAssistanceElement(e, sw);
      break;
    case ScriptElementType:
      // Already processed
      break;
    case FilterElementType:
      writeFilterElement(e, sw);
      break;
    case MessageElementType:
      writeMessageElement(e, sw);
      break;
    case AccessElementType:
      writeAccessElement(e, sw);
      break;
    case PopupElementType:
      writePopupElement(e, sw);
      break;
    }
  }

  // Close element script
  sw.writeEndElement();
  sw.writeEndDocument();
}

void XMLConfigWriter::writeScriptElement(Element *e, QXmlStreamWriter &sw) {
  // Script element already open
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    const QJsonValue &el{e->parameters()[p]};
    writeAttribute(p, el, sw);
  }
}

void XMLConfigWriter::writeErrorElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("error");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    const QJsonValue &el{e->parameters()[p]};
    writeAttribute(p, el, sw);
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeInterfaceElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("interface");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    const QJsonValue &el{e->parameters()[p]};
    writeAttribute(p, el, sw);
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeAdaptiveElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("adaptive");
  sw.writeAttribute("start", QString::number(e->time()));
  if (e->parameters().contains("onSamples")) {
    writeAttribute(
        "command",
        QString{"onSamples %1;"}.arg(e->parameters()["onSamples"].toInt()), sw);
  } else if (e->parameters().contains("onPast")) {
    writeAttribute("command",
                   QString{"onPast %1;"}.arg(e->parameters()["onPast"].toInt()),
                   sw);
  } else if (e->parameters().contains("onPeriodFrom") &&
             e->parameters().contains("onPeriodTo")) {
    writeAttribute("command",
                   QString{"onPeriod %1 %2;"}
                       .arg(e->parameters()["onPeriodFrom"].toInt())
                       .arg(e->parameters()["onPeriodTo"].toInt()),
                   sw);
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeCodeElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("code");
  sw.writeAttribute("start", QString::number(e->time()));
  if (e->parameters().contains("code")) {
    sw.writeCharacters(e->parameters()["code"].toString());
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeDurationElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("duration");
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    const QJsonValue &el{e->parameters()[p]};
    writeAttribute(p, el, sw);
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeControlElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("control");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    sw.writeAttribute(p, e->parameters()[p].toString());
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeQuestionElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("question");
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    sw.writeAttribute(p, e->parameters()[p].toString());
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writePopupElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("popup");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
        continue;
    sw.writeAttribute(p, e->parameters()[p].toString());
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeAssistanceElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("assistance");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    writeAttribute(p, e->parameters()[p], sw);
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeAttribute(const QString &name, const QJsonValue &v,
                                     QXmlStreamWriter &sw) {
  if (v.isDouble()) {
    sw.writeAttribute(name, QString::number(v.toDouble()));
  } else if (v.isString()) {
    sw.writeAttribute(name, v.toString());
  } else if (v.isBool()) {
    sw.writeAttribute(name, v.toBool() ? "true" : "false");
  }
}

void XMLConfigWriter::writeFilterElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("filter");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    if (e->parameters()[p].isString()) {
      sw.writeAttribute(p, e->parameters()[p].toString());
    } else if (e->parameters()[p].isBool()) {
      sw.writeAttribute(p, e->parameters()[p].toBool() ? "true" : "false");
    }
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeMessageElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("message");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    const QJsonValue &el{e->parameters()[p]};
    writeAttribute(p, el, sw);
  }
  sw.writeEndElement();
}

void XMLConfigWriter::writeAccessElement(Element *e, QXmlStreamWriter &sw) {
  sw.writeStartElement("access");
  sw.writeAttribute("start", QString::number(e->time()));
  for (auto p : e->parameters().keys()) {
    if (p == "start")
      continue;
    if (p == "type") {
      sw.writeAttribute("type", QString::number(e->parameters()[p].toDouble()));
    } else {
      const QJsonValue &el{e->parameters()[p]};
      writeAttribute(p, el, sw);
    }
  }
  sw.writeEndElement();
}
