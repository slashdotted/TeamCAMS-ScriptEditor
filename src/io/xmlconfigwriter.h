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
#ifndef XMLCONFIGWRITER_H
#define XMLCONFIGWRITER_H
#include "models/elementlist.h"
#include <QList>
#include <QString>
#include <QXmlStreamWriter>

class XMLConfigWriter {
public:
  static void write(QXmlStreamWriter &sw, ElementList &elist);

private:
  static void writeScriptElement(Element *e, QXmlStreamWriter &sw);
  static void writeErrorElement(Element *e, QXmlStreamWriter &sw);
  static void writeInterfaceElement(Element *e, QXmlStreamWriter &sw);
  static void writeAdaptiveElement(Element *e, QXmlStreamWriter &sw);
  static void writeCodeElement(Element *e, QXmlStreamWriter &sw);
  static void writeDurationElement(Element *e, QXmlStreamWriter &sw);
  static void writeControlElement(Element *e, QXmlStreamWriter &sw);
  static void writeQuestionElement(Element *e, QXmlStreamWriter &sw);
  static void writeAssistanceElement(Element *e, QXmlStreamWriter &sw);
  static void writePopupElement(Element *e, QXmlStreamWriter &sw);
  static void writeAttribute(const QString &name, const QJsonValue &v,
                             QXmlStreamWriter &sw);
  static void writeFilterElement(Element *e, QXmlStreamWriter &sw);
  static void writeMessageElement(Element *e, QXmlStreamWriter &sw);
  static void writeAccessElement(Element *e, QXmlStreamWriter &sw);
};

#endif // XMLCONFIGWRITER_H
