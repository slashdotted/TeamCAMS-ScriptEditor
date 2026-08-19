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
#include "elementlist.h"
#include "io/xmlconfighandler.h"
#include "io/xmlconfigwriter.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QMimeData>
#include <QPixmap>
#include <QTime>

ElementList::ElementList(QObject *parent) : QAbstractTableModel(parent) {}

QVariant ElementList::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return tr("Time (HH:MM:SS)");
    case 1:
      return tr("");
    case 2:
      return tr("Type");
    case 3:
      return tr("Data");
    default:
      return QVariant();
    }
  }
  return QVariant();
}

int ElementList::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_schedule.size();
}

int ElementList::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 4;
}

QVariant ElementList::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant{};
  Element *el = m_schedule.at(index.row());
  switch (role) {
  case Qt::DisplayRole:
    switch (index.column()) {
    case 0:
      if (el->time() >= 0) {
        return QTime(0, 0).addSecs(el->time()).toString("hh:mm:ss");
      } else {
        return "--:--:--";
      }
    case 2:
      switch (el->type()) {
      case ScriptElementType:
        return "<script>";
      case ErrorElementType:
        return "<error>";
      case InterfaceElementType:
        return "<interface>";
      case AdaptiveElementType:
        return "<adaptive>";
      case CodeElementType:
        return "<code>";
      case DurationElementType:
        return "<duration>";
      case ControlElementType:
        return "<control>";
      case QuestionElementType:
        return "<question>";
      case AssistanceElementType:
        return "<assistance>";
      case FilterElementType:
        return "<filter>";
      case AccessElementType:
        return "<access>";
      case MessageElementType:
        return "<message>";
      case PopupElementType:
        return "<popup>";
      }
    case 3:
        return el->asString().removeFirst().removeLast();
    default:
      return QVariant{};
    }
  case Qt::DecorationRole:
    if (index.column() == 1) {
      switch (el->type()) {
      case ScriptElementType:
        return QPixmap(":/images/File.png").scaled(16, 16);
      case ErrorElementType:
        return QPixmap(":/images/Bolt.png").scaled(16, 16);
      case InterfaceElementType:
        return QPixmap(":/images/Cursor.png").scaled(16, 16);
      case AdaptiveElementType:
        return QPixmap(":/images/Resize.png").scaled(16, 16);
      case CodeElementType:
        return QPixmap(":/images/Gear.png").scaled(16, 16);
      case DurationElementType:
        return QPixmap(":/images/Entrance.png").scaled(16, 16);
      case ControlElementType:
        return QPixmap(":/images/Triangle.png").scaled(16, 16);
      case QuestionElementType:
        return QPixmap(":/images/Star.png").scaled(16, 16);
      case AssistanceElementType:
        return QPixmap(":/images/Home.png").scaled(16, 16);
      case FilterElementType:
        return QPixmap(":/images/denied.png").scaled(16, 16);
      case MessageElementType:
        return QPixmap(":/images/mail.png").scaled(16, 16);
      case AccessElementType:
        return QPixmap(":/images/eye.png").scaled(16, 16);
      case PopupElementType:
        return QPixmap(":/images/popup.png").scaled(16, 16);
      }
    }
    break;
  default:
    break;
  }
  return QVariant();
}

bool ElementList::remove(int row) {
  beginRemoveRows(QModelIndex(), row, row);
  m_schedule.removeAt(row);
  endRemoveRows();
  return true;
}

bool ElementList::duplicate(int row) {
  beginInsertRows(QModelIndex(), row, row);
  auto e{m_schedule.at(row)};
  Element *element{new Element{e->type(), e->time() + 1, e->parameters()}};
  m_schedule.append(element);
  sortElements();
  endInsertRows();
  return true;
}

bool ElementList::open(QFile &source, bool validate) {
  beginResetModel();
  m_schedule.clear();
  endResetModel();
  XMLConfigHandler handler{validate};

  connect(&handler, &XMLConfigHandler::scriptElementRead, this,
          &ElementList::onScriptElement);
  connect(&handler, &XMLConfigHandler::questionElementRead, this,
          &ElementList::onQuestionElement);
  connect(&handler, &XMLConfigHandler::durationElementRead, this,
          &ElementList::onDurationElement);
  connect(&handler, &XMLConfigHandler::assistanceElementRead, this,
          &ElementList::onAssistanceElement);
  connect(&handler, &XMLConfigHandler::interfaceElementRead, this,
          &ElementList::onInterfaceElement);
  connect(&handler, &XMLConfigHandler::controlElementRead, this,
          &ElementList::onControlElement);
  connect(&handler, &XMLConfigHandler::adaptiveElementRead, this,
          &ElementList::onAdaptiveElement);
  connect(&handler, &XMLConfigHandler::errorElementRead, this,
          &ElementList::onErrorElement);
  connect(&handler, &XMLConfigHandler::codeElementRead, this,
          &ElementList::onCodeElement);
  connect(&handler, &XMLConfigHandler::filterElementRead, this,
          &ElementList::onFilterElement);
  connect(&handler, &XMLConfigHandler::messageElementRead, this,
          &ElementList::onMessageElement);
  connect(&handler, &XMLConfigHandler::accessElementRead, this,
          &ElementList::onAccessElement);
  connect(&handler, &XMLConfigHandler::popupElementRead, this,
          &ElementList::onPopupElement);

  source.open(QIODeviceBase::ReadOnly);
  try {
    QXmlStreamReader reader{&source};
    while (!reader.atEnd()) {
      auto el = reader.readNext();
      switch (el) {
      case QXmlStreamReader::StartElement: {
        auto name = reader.name();
        auto attr = reader.attributes();
        handler.startElement(name, attr);
      } break;
      case QXmlStreamReader::EndElement: {
        auto name = reader.name();
        handler.endElement(name);
      } break;
      case QXmlStreamReader::Characters: {
        auto text = reader.text();
        handler.characters(text);
      } break;
      default:
        break;
      }
    }
    if (reader.hasError()) {
      m_schedule.clear();
      QMessageBox::critical(QApplication::activeWindow(), tr("Error"),
                            tr("Error while reading data"), QMessageBox::Ok);
      return false;
    }
  } catch (const XMLConfigHandlerException &e) {
    if (!validate) {
      m_schedule.clear();
    }
    QMessageBox::critical(QApplication::activeWindow(), tr("Error"),
                          tr("Error while reading data: %1").arg(e.what()),
                          QMessageBox::Ok);
    return false;
  }

  sortElements();
  return true;
}

int ElementList::count(ElementType type) {
  int count{0};
  for (auto e : m_schedule) {
    if (e->type() == type) {
      ++count;
    }
  }
  return count;
}

int ElementList::count() { return m_schedule.size(); }

void ElementList::clear() {
  beginResetModel();
  for (Element *e : m_schedule) {
    delete e;
  }
  m_schedule.clear();
  endResetModel();
}

int ElementList::addElement(ElementType type) {
  int maxTime{-1};
  if (type != ScriptElementType && type != DurationElementType && type != QuestionElementType) {
      for (auto e : m_schedule) {
          if (e->time() > maxTime) {
              maxTime = e->time();
          }
      }
  } else {
      maxTime = -2;
  }
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  Element *element{new Element{type, maxTime + 1, QJsonObject{}}};
  m_schedule.append(element);
  endInsertRows();
  sortElements();
  return m_schedule.indexOf(element);
}

Element *ElementList::elementAt(int row) { return m_schedule.at(row); }

void ElementList::onScriptElement(QJsonObject parameters) {
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::ScriptElementType, -1, parameters});
  endInsertRows();
}

void ElementList::onQuestionElement(QString id, const QString &text) {
  QJsonObject parameters;
  parameters["id"] = id;
  parameters["text"] = text;
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::QuestionElementType, -1, parameters});
  endInsertRows();
}

void ElementList::onPopupElement(int startTime, QJsonObject parameters) {
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::PopupElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onDurationElement(int endTime) {
  QJsonObject parameters;
  parameters["seconds"] = endTime;
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::DurationElementType, -1, parameters});
  endInsertRows();
}

void ElementList::onAssistanceElement(int startTime, QJsonObject parameters) {
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::AssistanceElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onInterfaceElement(int startTime, const QString &display,
                                     const QString &modifier,
                                     const QString &value,
                                     const QString &users) {
  QJsonObject parameters;
  parameters["display"] = display;
  if (modifier == "visible") {
    parameters["visible"] = (value == "true");
  }
  if (modifier == "enabled") {
    parameters["enabled"] = (value == "true");
  }
  if (!users.isEmpty()) {
    parameters["users"] = users;
  }
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::InterfaceElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onControlElement(int startTime, const QString &cmd) {
  QJsonObject parameters;
  parameters["command"] = cmd;
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::ControlElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onAdaptiveElement(int startTime, QJsonObject parameters) {
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::AdaptiveElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onErrorElement(int startTime, const QString &errorType,
                                 QJsonObject parameters) {
  parameters["type"] = errorType;
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::ErrorElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onCodeElement(int startTime, const QString &code) {
  QJsonObject parameters;
  parameters["code"] = code;
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  m_schedule.append(
      new Element{ElementType::CodeElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onFilterElement(int startTime, bool enabled,
                                  const QString &type, const QString &key,
                                  const QString &user, bool feedback) {
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  QJsonObject parameters;
  parameters["type"] = type;
  parameters["enabled"] = enabled;
  parameters["key"] = key;
  parameters["user"] = user;
  parameters["feedback"] = feedback;
  m_schedule.append(
      new Element{ElementType::FilterElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onMessageElement(int startTime, const QString &sender,
                                   const QString &recipient,
                                   const QString &text) {
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  QJsonObject parameters;
  parameters["from"] = sender;
  parameters["to"] = recipient;
  parameters["text"] = text;
  m_schedule.append(
      new Element{ElementType::MessageElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::onAccessElement(int startTime, const QString &user,
                                  int accessType) {
  beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
  QJsonObject parameters;
  parameters["username"] = user;
  parameters["type"] = accessType;
  m_schedule.append(
      new Element{ElementType::AccessElementType, startTime, parameters});
  endInsertRows();
}

void ElementList::sortElements() {
  std::sort(m_schedule.begin(), m_schedule.end(),
            [&](const Element *lhs, const Element *rhs) {
              if (lhs->time() < rhs->time()) {
                return true;
              } else if (lhs->time() == rhs->time()) {
                return lhs->type() < rhs->type();
              } else {
                return false;
              }
            });
  emit dataChanged(createIndex(0, 0), createIndex(m_schedule.size(), 2));
}

int ElementList::indexOf(Element *e) { return m_schedule.indexOf(e); }

QList<Element *>::iterator ElementList::begin() { return m_schedule.begin(); }

QList<Element *>::iterator ElementList::end() { return m_schedule.end(); }

QStringList ElementList::mimeTypes() const {
  return {"text/xml", "text/plain"};
}

QMimeData *ElementList::mimeData(const QModelIndexList &indexes) const {
  if (indexes.isEmpty()) {
    return nullptr;
  }
  QMimeData *data{new QMimeData()};
  XMLConfigWriter cw;
  QString output;
  QXmlStreamWriter sw{&output};
  ElementList dragList;
  for (const auto &e : indexes) {
    if (!dragList.m_schedule.contains(m_schedule.at(e.row()))) {
      dragList.m_schedule.append(m_schedule.at(e.row()));
    }
  }
  cw.write(sw, dragList);
  dragList.m_schedule.clear();
  data->setData("text/xml", output.toUtf8());
  data->setText(output);
  return data;
}

Qt::ItemFlags ElementList::flags(const QModelIndex &index) const {
  if (index.isValid()) {
    return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled;
  } else {
    return Qt::NoItemFlags;
  }
}

QList<Element *> ElementList::snapshot() {
  QList<Element *> copy;
  for (Element *e : m_schedule) {
    copy.append(new Element{*e});
  }
  return copy;
}

void ElementList::restore(const QList<Element *> &sn) {
  clear();
  for (Element *e : sn) {
    beginInsertRows(QModelIndex{}, m_schedule.size(), m_schedule.size());
    m_schedule.append(new Element{*e});
    endInsertRows();
  }
  sortElements();
}

void ElementList::update(Element *e) {
  emit dataChanged(createIndex(0, 0), createIndex(m_schedule.indexOf(e), 3));
}
