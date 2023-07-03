// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwindow.h"

#include <QtWidgets>

//! [0]
MainWindow::MainWindow()
{
    selectedDate = QDate::currentDate();
    fontSize = 10;

    QWidget *centralWidget = new QWidget;
    centralWidget->setWindowTitle("Calendar");
//! [0]
//! [0.1]

    QPushButton *dateDifference = new QPushButton(tr("Difference Date"));
    QPushButton *CurrentDate = new QPushButton(tr("Current Date"));

//! [0.1]

//! [1]
    QLabel *dateLabel = new QLabel(tr("Date:"));
    QComboBox *monthCombo = new QComboBox;

    for (int month = 1; month <= 12; ++month)
        monthCombo->addItem(QLocale::system().monthName(month));

    QDateTimeEdit *yearEdit = new QDateTimeEdit;
    yearEdit->setDisplayFormat("yyyy");
    yearEdit->setDateRange(QDate(1753, 1, 1), QDate(8000, 1, 1));
//! [1]

    monthCombo->setCurrentIndex(selectedDate.month() - 1);
    yearEdit->setDate(selectedDate);

//! [2]
    QLabel *fontSizeLabel = new QLabel(tr("Font size:"));
    QSpinBox *fontSizeSpinBox = new QSpinBox;
    fontSizeSpinBox->setRange(1, 64);

    editor = new QTextBrowser;
    insertCalendar();
//! [2]

//! [3]
    //-----------------------------------------------------

    connect(CurrentDate, &QPushButton::clicked, this, [=]() {
        monthCombo->setCurrentIndex(QDate::currentDate().month()-1);
        yearEdit->setDate(QDate::currentDate());
        setMonth(QDate::currentDate().month() - 1);
        setYear(QDate::currentDate());
    });
    //-----------------------------------------------------
    connect(monthCombo, &QComboBox::activated,
            this, &MainWindow::setMonth);
    connect(yearEdit, &QDateTimeEdit::dateChanged,
            this, &MainWindow::setYear);
    connect(fontSizeSpinBox, &QSpinBox::valueChanged,
            this, &MainWindow::setFontSize);
    connect(dateDifference, &QPushButton::clicked,
            this, &MainWindow::DifferenceDate_window);
//! [3]

    fontSizeSpinBox->setValue(10);

//! [4]
    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(dateLabel);
    controlsLayout->addWidget(monthCombo);
    controlsLayout->addWidget(yearEdit);
    controlsLayout->addStretch(5);
    controlsLayout->addWidget(CurrentDate);
    controlsLayout->addStretch(20);
    controlsLayout->addWidget(dateDifference);
    controlsLayout->addStretch(100);
    controlsLayout->addWidget(fontSizeLabel);
    controlsLayout->addWidget(fontSizeSpinBox);
    controlsLayout->addStretch(1);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlsLayout);
    centralLayout->addWidget(editor, 1);
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);
//! [4]
}

//-----------------------------------------------------------------------
//! [0.2]

void MainWindow::DifferenceDate_window()
{
    // Create window
    QWidget *Difference = new QWidget;
    Difference->show();
    Difference->resize(500, 250);

    // Create label and other
    //-----------------------------------------------------------------
    QLabel *SetMonthLabel = new QLabel(tr("Введіть першу дату зверху, і другу знизу"));
    QPushButton *CurrentDate = new QPushButton(tr("Current Date"));

    QComboBox *monthCombo1 = new QComboBox;
    for (int month = 1; month <= 12; ++month)
        monthCombo1->addItem(QLocale::system().monthName(month));

    QDateTimeEdit *yearChoose1 = new QDateTimeEdit;
    yearChoose1->setDisplayFormat("yyyy");
    yearChoose1->setDateRange(QDate(1753, 1, 1), QDate(8000, 1, 1));
    //-----------------------------------------------------------------
    QComboBox *dayCombo1 = new QComboBox;

    // Update the day combo box based on the selected month and year
    updateDayCombo(dayCombo1, monthCombo1, yearChoose1);

    connect(monthCombo1, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        updateDayCombo(dayCombo1, monthCombo1, yearChoose1);
    });

    connect(yearChoose1, &QDateTimeEdit::dateChanged, [=](const QDate &date) {
        updateDayCombo(dayCombo1, monthCombo1, yearChoose1);
    });
    //---------------------------------------------------------------------------------

    // Update the day combo box based on the selected month and year

    QComboBox *monthCombo2 = new QComboBox;
    for (int month = 1; month <= 12; ++month)
        monthCombo2->addItem(QLocale::system().monthName(month));

    QDateTimeEdit *yearChoose2 = new QDateTimeEdit;
    yearChoose2->setDisplayFormat("yyyy");
    yearChoose2->setDateRange(QDate(1753, 1, 1), QDate(8000, 1, 1));

    QComboBox *dayCombo2 = new QComboBox;

    updateDayCombo(dayCombo2, monthCombo2, yearChoose2);

    connect(monthCombo2, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        updateDayCombo(dayCombo2, monthCombo2, yearChoose2);
    });

    connect(yearChoose2, &QDateTimeEdit::dateChanged, [=](const QDate &date) {
        updateDayCombo(dayCombo2, monthCombo2, yearChoose2);
    });

    //------------------------------------------------------------------
    // Create label to display the difference between selected dates
    QLabel *differenceLabel = new QLabel;

    connect(dayCombo1, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        QDate selectedDate1(yearChoose1->date().year(), monthCombo1->currentIndex() + 1, dayCombo1->currentIndex() + 1);
        QDate selectedDate2(yearChoose2->date().year(), monthCombo2->currentIndex() + 1, dayCombo2->currentIndex() + 1);
        int difference = selectedDate1.daysTo(selectedDate2);
        differenceLabel->setText(QString("Різниця між датами: %1").arg(abs(difference)));
    });
    connect(dayCombo2, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        QDate selectedDate1(yearChoose1->date().year(), monthCombo1->currentIndex() + 1, dayCombo1->currentIndex() + 1);
        QDate selectedDate2(yearChoose2->date().year(), monthCombo2->currentIndex() + 1, dayCombo2->currentIndex() + 1);
        int difference = selectedDate1.daysTo(selectedDate2);
        differenceLabel->setText(QString("Різниця між датами: %1").arg(abs(difference)));
    });
    //-------------------------------------

    QDate currentDate = QDate::currentDate();

    int currentYear = currentDate.year();
    int currentMonth = currentDate.month();
    int currentDay = currentDate.day();
    //-------------------------------------
    connect(CurrentDate, &QPushButton::clicked, this, [=]() {
        QDate currentDate = QDate::currentDate();
        yearChoose1->setDate(QDate(currentYear, currentMonth, currentDay));
        monthCombo1->setCurrentIndex(currentMonth - 1);
        dayCombo1->setCurrentIndex(currentDay - 1);
        QDate selectedDate(yearChoose2->date().year(), monthCombo2->currentIndex() + 1, dayCombo2->currentIndex() + 1);
        int difference = selectedDate.daysTo(currentDate);
        differenceLabel->setText(QString("Різниця між датами: %1").arg(abs(difference)));
    });

    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    Difference->setStyleSheet("background-color: #C8ABDB;");
    mainLayout->addWidget(SetMonthLabel);
    SetMonthLabel->setStyleSheet("font-size: 20px;");

    mainLayout->addWidget(CurrentDate);
    CurrentDate->setMinimumSize(15, 30);
    CurrentDate->setStyleSheet("background-color: #8E99E8;");

    mainLayout->addWidget(monthCombo1);
    monthCombo1->setFixedWidth(200);
    monthCombo1->setStyleSheet("background-color: #8E99E8;");

    mainLayout->addWidget(yearChoose1);
    yearChoose1->setFixedWidth(180);
    yearChoose1->setStyleSheet("background-color: #8E99E8;");

    mainLayout->addWidget(dayCombo1);
    dayCombo1->setFixedWidth(160);
    dayCombo1->setStyleSheet("background-color: #8E99E8;");

    mainLayout->addWidget(differenceLabel);
    differenceLabel->setStyleSheet("font-size: 20px;");

    mainLayout->addWidget(monthCombo2);
    monthCombo2->setFixedWidth(160);
    monthCombo2->setStyleSheet("background-color: #8E99E8;");

    mainLayout->addWidget(yearChoose2);
    yearChoose2->setFixedWidth(180);
    yearChoose2->setStyleSheet("background-color: #8E99E8;");

    mainLayout->addWidget(dayCombo2);
    dayCombo2->setFixedWidth(200);
    dayCombo2->setStyleSheet("background-color: #8E99E8;");

    Difference->setLayout(mainLayout);
}

void MainWindow::updateDayCombo(QComboBox *dayCombo, QComboBox *monthCombo, QDateTimeEdit *yearChoose)
{
    int selectedMonth = monthCombo->currentIndex() + 1;
    int selectedYear = yearChoose->date().year();

    QDate selectedDate(selectedYear, selectedMonth, 1);
    int daysInMonth = selectedDate.daysInMonth();

    dayCombo->clear();

    for (int day = 1; day <= daysInMonth; ++day) {
        dayCombo->addItem(QString::number(day));
    }
}

//! [0.3]
//-----------------------------------------------------------------------

//! [5]
void MainWindow::insertCalendar()
{
    editor->clear();
    QTextCursor cursor = editor->textCursor();
    cursor.beginEditBlock();

    QDate date(selectedDate.year(), selectedDate.month(), 1);
//! [5]

//! [6]
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignHCenter);
    tableFormat.setBackground(QColor("#C8ABDB"));
    tableFormat.setCellPadding(2);
    tableFormat.setCellSpacing(4);
//! [6] //! [7]
    QList<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 15)
                << QTextLength(QTextLength::PercentageLength, 15)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14);
    tableFormat.setColumnWidthConstraints(constraints);
//! [7]

//! [8]
    QTextTable *table = cursor.insertTable(1, 7, tableFormat);
//! [8]

//! [9]
    QTextFrame *frame = cursor.currentFrame();
    QTextFrameFormat frameFormat = frame->frameFormat();
    frame->setFrameFormat(frameFormat);
//! [9]

//! [10]
    QTextCharFormat format = cursor.charFormat();
    format.setFontPointSize(fontSize);

    QTextCharFormat boldFormat = format;
    boldFormat.setFontWeight(QFont::Bold);

    QTextCharFormat highlightedFormat = boldFormat;
    highlightedFormat.setBackground(Qt::yellow);
//! [10]

//! [11]
    for (int weekDay = 1; weekDay <= 7; ++weekDay) {
        QTextTableCell cell = table->cellAt(0, weekDay-1);
//! [11] //! [12]
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(QLocale::system().dayName(weekDay), boldFormat);
    }
//! [12]

//! [13]
    table->insertRows(table->rows(), 1);
//! [13]

    while (date.month() == selectedDate.month()) {
        int weekDay = date.dayOfWeek();
        QTextTableCell cell = table->cellAt(table->rows()-1, weekDay-1);
        QTextCursor cellCursor = cell.firstCursorPosition();

        if (date == QDate::currentDate())
            cellCursor.insertText(QString("%1").arg(date.day()), highlightedFormat);
        else
            cellCursor.insertText(QString("%1").arg(date.day()), format);

        date = date.addDays(1);
        if (weekDay == 7 && date.month() == selectedDate.month())
            table->insertRows(table->rows(), 1);
    }

    cursor.endEditBlock();
//! [14]
    setWindowTitle(tr("Calendar for %1 %2"
        ).arg(QLocale::system().monthName(selectedDate.month())
        ).arg(selectedDate.year()));
}
//! [14]

//! [15]
void MainWindow::setFontSize(int size)
{
    fontSize = size;
    insertCalendar();
}
//! [15]

//! [16]
void MainWindow::setMonth(int month)
{
    selectedDate = QDate(selectedDate.year(), month + 1, selectedDate.day());
    insertCalendar();
}
//! [16]

//! [17]
void MainWindow::setYear(QDate date)
{
    selectedDate = QDate(date.year(), selectedDate.month(), selectedDate.day());
    insertCalendar();
}
//! [17]
