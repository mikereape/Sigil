/************************************************************************
**
**  Copyright (C) 2021      Kevin B. Hendricks, Stratford Ontario Canada 
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <QChar>
#include <QString>
#include <QWidget>
#include <QStyledItemDelegate>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QSize>
#include "Dialogs/StyledTextDelegate.h"

static const int COL_BEFORE = 2;
static const int COL_AFTER = 3;


StyledTextDelegate::StyledTextDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

StyledTextDelegate::~StyledTextDelegate()
{
}

void StyledTextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // use only in desginated columns
    if ((index.column() != COL_BEFORE) && (index.column() != COL_AFTER )) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    painter->save();
    painter->setClipRect(QRectF(option.rect));
    painter->translate(option.rect.topLeft());
    QTextDocument doc;
    doc.setPlainText(index.data(Qt::DisplayRole).toString());
    int astart = index.data(Qt::UserRole+1).toInt();
    int aend = index.data(Qt::UserRole+2).toInt();
    QTextCursor cursor = QTextCursor(&doc);
    cursor.clearSelection();
    cursor.setPosition(astart);
    cursor.setPosition(aend, QTextCursor::KeepAnchor);
    QTextCharFormat format;
    format.setForeground(Qt::red);
    cursor.setCharFormat(format);
    doc.drawContents(painter);
    painter->restore();
}

QSize StyledTextDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if ((index.column() != COL_BEFORE) && (index.column() != COL_AFTER )) {
        return QStyledItemDelegate::sizeHint(option, index);
    }
    QTextDocument doc;
    doc.setPlainText(index.data(Qt::DisplayRole).toString());
    QSize res = doc.size().toSize();
    if (res.width() > 160) res.setWidth(160);
    res.setHeight(res.height()+10);
    return res;
}
