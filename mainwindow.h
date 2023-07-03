// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>

QT_BEGIN_NAMESPACE
class QTextBrowser;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void setFontSize(int size);
    void setMonth(int month);
    void setYear(QDate date);
    void DifferenceDate_window();

private:
    void SelectDate_Window(QWidget *parent);
    void updateDayCombo(QComboBox *dayCombo, QComboBox *monthCombo, QDateTimeEdit *yearChoose);
    void insertCalendar();

    int fontSize;
    QDate selectedDate;
    QTextBrowser *editor;
    QComboBox *monthCombo = new QComboBox;
    QComboBox *dayCombo = new QComboBox;
    QDateTimeEdit *yearChoose = new QDateTimeEdit;
};
//! [0]

#endif // MAINWINDOW_H
