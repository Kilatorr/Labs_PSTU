#include "mainwindow.h"
#include <QMessageBox>
#include <cmath>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QMenu>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QApplication>
#include <QDialogButtonBox>
#include <QSettings>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Финансовый помощник");
    setMinimumSize(1000, 650);
    resize(1100, 700);

    // Тёмная тема
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::PlaceholderText, QColor(128, 128, 128));
    darkPalette.setColor(QPalette::Button, QColor(55, 55, 55));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    QApplication::setPalette(darkPalette);

    setupUI();
    loadData();

    updateIncomeList();
    updateExpenseList();
    updateGoalsList();
    updateMainInfo();
}

MainWindow::~MainWindow()
{
    saveData();
}

void MainWindow::setupUI()
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(createTopBar());

    tabWidget = new QTabWidget(this);
    tabWidget->addTab(createMainTab(), "Главная");
    tabWidget->addTab(createIncomeTab(), "Доходы");
    tabWidget->addTab(createExpenseTab(), "Расходы");
    tabWidget->addTab(createGoalsTab(), "Цели");
    tabWidget->addTab(createCalendarTab(), "Календарь");
    tabWidget->addTab(createPurchaseTab(), "Покупки");

    mainLayout->addWidget(tabWidget, 1);
    setCentralWidget(central);
}

QWidget* MainWindow::createTopBar()
{
    QWidget* topBar = new QWidget(this);
    topBar->setObjectName("topBar");
    QHBoxLayout* layout = new QHBoxLayout(topBar);
    layout->setContentsMargins(15, 5, 15, 5);

    QLabel* logoLabel = new QLabel("💰 Финансовый контроль", topBar);
    logoLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: white;");
    layout->addWidget(logoLabel);

    layout->addStretch();

    return topBar;
}

QWidget* MainWindow::createMainTab()
{
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(20);

    QGroupBox* summaryBox = new QGroupBox("Финансовая сводка за месяц", widget);
    QVBoxLayout* boxLayout = new QVBoxLayout(summaryBox);
    boxLayout->setContentsMargins(20, 20, 20, 20);
    boxLayout->setSpacing(15);

    lblTotalIncome = new QLabel("Сумма доходов: 0 ₽", summaryBox);
    lblTotalExpense = new QLabel("Сумма расходов: 0 ₽", summaryBox);
    lblSavings = new QLabel("Вы откладываете: 0 ₽", summaryBox);

    QFont font = lblTotalIncome->font();
    font.setPointSize(12);
    lblTotalIncome->setFont(font);
    lblTotalExpense->setFont(font);

    font.setPointSize(14);
    font.setBold(true);
    lblSavings->setFont(font);

    boxLayout->addWidget(lblTotalIncome);
    boxLayout->addWidget(lblTotalExpense);
    boxLayout->addWidget(lblSavings);

    layout->addWidget(summaryBox);

    // Блок с целями на главной
    QGroupBox* goalsBox = new QGroupBox("🎯 Текущие цели накопления", widget);
    QVBoxLayout* goalsBoxLayout = new QVBoxLayout(goalsBox);
    goalsBoxLayout->setContentsMargins(15, 15, 15, 15);

    listGoalsMain = new QListWidget(goalsBox);
    listGoalsMain->setMaximumHeight(150);
    goalsBoxLayout->addWidget(listGoalsMain);

    layout->addWidget(goalsBox);
    layout->addStretch();

    return widget;
}

QWidget* MainWindow::createIncomeTab()
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(widget);

    listIncomes = new QListWidget(widget);
    listIncomes->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listIncomes, &QListWidget::customContextMenuRequested, this, &MainWindow::showIncomeContextMenu);
    mainLayout->addWidget(listIncomes, 2);

    QGroupBox* addGroup = new QGroupBox("Добавить доход", widget);
    QFormLayout* form = new QFormLayout(addGroup);

    lineIncomeName = new QLineEdit(addGroup);
    lineIncomeName->setPlaceholderText("Например: Зарплата");

    spinIncomeAmount = new QSpinBox(addGroup);
    spinIncomeAmount->setRange(0, 10000000);
    spinIncomeAmount->setSuffix(" ₽");

    dateIncomeDate = new QDateEdit(addGroup);
    dateIncomeDate->setDate(QDate::currentDate());
    dateIncomeDate->setCalendarPopup(true);

    chkIncomeRecurring = new QCheckBox("Повторять каждый месяц", addGroup);
    spinIncomeRecurringDay = new QSpinBox(addGroup);
    spinIncomeRecurringDay->setRange(1, 31);
    spinIncomeRecurringDay->setSuffix(" число");
    spinIncomeRecurringDay->setEnabled(false);
    connect(chkIncomeRecurring, &QCheckBox::toggled, spinIncomeRecurringDay, &QSpinBox::setEnabled);

    chkIncomeLimited = new QCheckBox("Ограничить по времени", addGroup);
    spinIncomeDuration = new QSpinBox(addGroup);
    spinIncomeDuration->setRange(1, 600);
    spinIncomeDuration->setSuffix(" мес.");
    spinIncomeDuration->setEnabled(false);
    connect(chkIncomeLimited, &QCheckBox::toggled, spinIncomeDuration, &QSpinBox::setEnabled);

    QPushButton* btnAddIncome = new QPushButton("Добавить запись", addGroup);
    QPushButton* btnRemoveIncome = new QPushButton("Удалить выбранное", addGroup);

    form->addRow("Название:", lineIncomeName);
    form->addRow("Сумма:", spinIncomeAmount);
    form->addRow("Дата начала:", dateIncomeDate);
    form->addRow(chkIncomeRecurring);
    form->addRow("День получения:", spinIncomeRecurringDay);
    form->addRow(chkIncomeLimited);
    form->addRow("Длительность:", spinIncomeDuration);
    form->addRow(btnAddIncome);
    form->addRow(btnRemoveIncome);

    mainLayout->addWidget(addGroup, 1);

    connect(btnAddIncome, &QPushButton::clicked, this, &MainWindow::onAddIncome);
    connect(btnRemoveIncome, &QPushButton::clicked, this, &MainWindow::onRemoveIncome);

    return widget;
}

QWidget* MainWindow::createExpenseTab()
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(widget);

    listExpenses = new QListWidget(widget);
    listExpenses->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listExpenses, &QListWidget::customContextMenuRequested, this, &MainWindow::showExpenseContextMenu);
    mainLayout->addWidget(listExpenses, 2);

    QGroupBox* addGroup = new QGroupBox("Добавить расход", widget);
    QFormLayout* form = new QFormLayout(addGroup);

    lineExpenseName = new QLineEdit(addGroup);
    lineExpenseName->setPlaceholderText("Например: Аренда");

    spinExpenseAmount = new QSpinBox(addGroup);
    spinExpenseAmount->setRange(0, 10000000);
    spinExpenseAmount->setSuffix(" ₽");

    dateExpenseDate = new QDateEdit(addGroup);
    dateExpenseDate->setDate(QDate::currentDate());
    dateExpenseDate->setCalendarPopup(true);

    comboExpenseType = new QComboBox(addGroup);
    comboExpenseType->addItems({"В месяц", "В день"});

    chkExpenseRecurring = new QCheckBox("Повторять каждый месяц", addGroup);
    spinExpenseRecurringDay = new QSpinBox(addGroup);
    spinExpenseRecurringDay->setRange(1, 31);
    spinExpenseRecurringDay->setSuffix(" число");
    spinExpenseRecurringDay->setEnabled(false);
    connect(chkExpenseRecurring, &QCheckBox::toggled, spinExpenseRecurringDay, &QSpinBox::setEnabled);

    chkExpenseLimited = new QCheckBox("Ограничить по времени", addGroup);
    spinExpenseDuration = new QSpinBox(addGroup);
    spinExpenseDuration->setRange(1, 600);
    spinExpenseDuration->setSuffix(" мес.");
    spinExpenseDuration->setEnabled(false);
    connect(chkExpenseLimited, &QCheckBox::toggled, spinExpenseDuration, &QSpinBox::setEnabled);

    QPushButton* btnAddExpense = new QPushButton("Добавить запись", addGroup);
    QPushButton* btnRemoveExpense = new QPushButton("Удалить выбранное", addGroup);

    form->addRow("Название:", lineExpenseName);
    form->addRow("Сумма:", spinExpenseAmount);
    form->addRow("Дата начала:", dateExpenseDate);
    form->addRow("Периодичность:", comboExpenseType);
    form->addRow(chkExpenseRecurring);
    form->addRow("День списания:", spinExpenseRecurringDay);
    form->addRow(chkExpenseLimited);
    form->addRow("Длительность:", spinExpenseDuration);
    form->addRow(btnAddExpense);
    form->addRow(btnRemoveExpense);

    mainLayout->addWidget(addGroup, 1);

    connect(btnAddExpense, &QPushButton::clicked, this, &MainWindow::onAddExpense);
    connect(btnRemoveExpense, &QPushButton::clicked, this, &MainWindow::onRemoveExpense);

    return widget;
}

QWidget* MainWindow::createGoalsTab()
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(widget);

    listGoals = new QListWidget(widget);
    listGoals->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listGoals, &QListWidget::customContextMenuRequested, this, &MainWindow::showGoalContextMenu);
    mainLayout->addWidget(listGoals, 2);

    QGroupBox* addGroup = new QGroupBox("Новая цель", widget);
    QFormLayout* form = new QFormLayout(addGroup);

    lineGoalName = new QLineEdit(addGroup);
    lineGoalName->setPlaceholderText("Например: Отпуск");

    spinGoalTarget = new QDoubleSpinBox(addGroup);
    spinGoalTarget->setRange(0, 100000000);
    spinGoalTarget->setSuffix(" ₽");
    spinGoalTarget->setDecimals(0);

    spinGoalCurrent = new QDoubleSpinBox(addGroup);
    spinGoalCurrent->setRange(0, 100000000);
    spinGoalCurrent->setSuffix(" ₽");
    spinGoalCurrent->setDecimals(0);

    dateGoalDate = new QDateEdit(addGroup);
    dateGoalDate->setDate(QDate::currentDate().addMonths(6));
    dateGoalDate->setCalendarPopup(true);

    QPushButton* btnAddGoal = new QPushButton("Создать цель", addGroup);
    QPushButton* btnRemoveGoal = new QPushButton("Удалить цель", addGroup);

    form->addRow("Название:", lineGoalName);
    form->addRow("Нужно собрать:", spinGoalTarget);
    form->addRow("Уже собрано:", spinGoalCurrent);
    form->addRow("Срок до:", dateGoalDate);
    form->addRow(btnAddGoal);
    form->addRow(btnRemoveGoal);

    mainLayout->addWidget(addGroup, 1);

    connect(btnAddGoal, &QPushButton::clicked, this, &MainWindow::onAddGoal);
    connect(btnRemoveGoal, &QPushButton::clicked, this, &MainWindow::onRemoveGoal);

    return widget;
}

QWidget* MainWindow::createCalendarTab()
{
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    calendar = new QCalendarWidget(widget);
    calendar->setGridVisible(true);
    connect(calendar, &QCalendarWidget::clicked, this, &MainWindow::onCalendarDayClicked);
    connect(calendar, &QCalendarWidget::currentPageChanged, this, &MainWindow::onCalendarMonthChanged);

    calendarInfo = new QTextBrowser(widget);
    calendarInfo->setMinimumHeight(100);

    layout->addWidget(calendar, 1);
    layout->addWidget(new QLabel("Финансовые операции на выбранный день:"));
    layout->addWidget(calendarInfo);

    return widget;
}

QWidget* MainWindow::createPurchaseTab()
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(widget);

    QGroupBox* inputGroup = new QGroupBox("Параметры планируемой покупки", widget);
    QFormLayout* form = new QFormLayout(inputGroup);

    comboPurchaseType = new QComboBox(inputGroup);
    comboPurchaseType->addItems({"Покупка сразу (накопление)", "Рассрочка", "Кредит"});

    lineItemName = new QLineEdit(inputGroup);
    lineItemName->setPlaceholderText("Например: Смартфон");

    spinItemPrice = new QDoubleSpinBox(inputGroup);
    spinItemPrice->setRange(0, 100000000);
    spinItemPrice->setSuffix(" ₽");
    spinItemPrice->setDecimals(0);

    spinMonths = new QSpinBox(inputGroup);
    spinMonths->setRange(1, 600);
    spinMonths->setSuffix(" мес.");
    spinMonths->setValue(12);

    spinDownPayment = new QDoubleSpinBox(inputGroup);
    spinDownPayment->setRange(0, 100000000);
    spinDownPayment->setSuffix(" ₽");
    spinDownPayment->setDecimals(0);

    doubleSpinInterest = new QDoubleSpinBox(inputGroup);
    doubleSpinInterest->setRange(0, 100);
    doubleSpinInterest->setSuffix(" %");
    doubleSpinInterest->setValue(15.0);

    btnCalculate = new QPushButton("Рассчитать нагрузку", inputGroup);
    btnAddPurchaseToExpenses = new QPushButton("Внести ежемесячный платёж в расходы", inputGroup);
    btnAddPurchaseToExpenses->setEnabled(false);

    form->addRow("Вариант сделки:", comboPurchaseType);
    form->addRow("Наименование товара:", lineItemName);
    form->addRow("Полная стоимость:", spinItemPrice);
    form->addRow("Срок выплат/сбора:", spinMonths);
    form->addRow("Первый взнос:", spinDownPayment);
    form->addRow("Годовой процент (кредит):", doubleSpinInterest);
    form->addRow(btnCalculate);
    form->addRow(btnAddPurchaseToExpenses);

    mainLayout->addWidget(inputGroup, 1);

    QGroupBox* resultGroup = new QGroupBox("Аналитический отчёт", widget);
    QVBoxLayout* resLayout = new QVBoxLayout(resultGroup);
    textResult = new QTextEdit(resultGroup);
    textResult->setReadOnly(true);
    resLayout->addWidget(textResult);

    mainLayout->addWidget(resultGroup, 1);

    connect(btnCalculate, &QPushButton::clicked, this, &MainWindow::onCalculate);
    connect(btnAddPurchaseToExpenses, &QPushButton::clicked, this, &MainWindow::onAddPurchaseToExpenses);

    return widget;
}

// ================= DIALOGS =================

bool MainWindow::editIncomeDialog(IncomeWithDate& income)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Редактирование дохода");
    QFormLayout form(&dialog);

    QLineEdit* nameEdit = new QLineEdit(income.name, &dialog);
    QSpinBox* amountEdit = new QSpinBox(&dialog);
    amountEdit->setRange(0, 10000000);
    amountEdit->setValue((int)income.amount);

    QDateEdit* dateEdit = new QDateEdit(income.date, &dialog);
    dateEdit->setCalendarPopup(true);

    QCheckBox* recCheck = new QCheckBox("Повторяющийся", &dialog);
    recCheck->setChecked(income.isRecurring);

    QSpinBox* dayEdit = new QSpinBox(&dialog);
    dayEdit->setRange(1, 31);
    dayEdit->setValue(income.recurringDay);
    dayEdit->setEnabled(income.isRecurring);

    connect(recCheck, &QCheckBox::toggled, dayEdit, &QSpinBox::setEnabled);

    form.addRow("Название:", nameEdit);
    form.addRow("Сумма (₽):", amountEdit);
    form.addRow("Дата:", dateEdit);
    form.addRow(recCheck);
    form.addRow("День получения:", dayEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form.addRow(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        income.name = nameEdit->text();
        income.amount = amountEdit->value();
        income.date = dateEdit->date();
        income.isRecurring = recCheck->isChecked();
        income.recurringDay = dayEdit->value();
        return true;
    }
    return false;
}

bool MainWindow::editExpenseDialog(ExpenseWithDate& expense)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Редактирование расхода");
    QFormLayout form(&dialog);

    QLineEdit* nameEdit = new QLineEdit(expense.name, &dialog);
    QSpinBox* amountEdit = new QSpinBox(&dialog);
    amountEdit->setRange(0, 10000000);
    amountEdit->setValue((int)expense.amount);

    QDateEdit* dateEdit = new QDateEdit(expense.date, &dialog);
    dateEdit->setCalendarPopup(true);

    QComboBox* typeCombo = new QComboBox(&dialog);
    typeCombo->addItems({"В месяц", "В день"});
    typeCombo->setCurrentIndex(expense.isMonthly ? 0 : 1);

    QCheckBox* recCheck = new QCheckBox("Повторяющийся", &dialog);
    recCheck->setChecked(expense.isRecurring);

    QSpinBox* dayEdit = new QSpinBox(&dialog);
    dayEdit->setRange(1, 31);
    dayEdit->setValue(expense.recurringDay);
    dayEdit->setEnabled(expense.isRecurring);

    connect(recCheck, &QCheckBox::toggled, dayEdit, &QSpinBox::setEnabled);

    form.addRow("Название:", nameEdit);
    form.addRow("Сумма (₽):", amountEdit);
    form.addRow("Дата:", dateEdit);
    form.addRow("Периодичность:", typeCombo);
    form.addRow(recCheck);
    form.addRow("День списания:", dayEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form.addRow(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        expense.name = nameEdit->text();
        expense.amount = amountEdit->value();
        expense.date = dateEdit->date();
        expense.isMonthly = (typeCombo->currentIndex() == 0);
        expense.isRecurring = recCheck->isChecked();
        expense.recurringDay = dayEdit->value();
        return true;
    }
    return false;
}

bool MainWindow::editGoalDialog(SavingsGoal& goal)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Редактирование цели");
    QFormLayout form(&dialog);

    QLineEdit* nameEdit = new QLineEdit(goal.name, &dialog);
    QDoubleSpinBox* targetEdit = new QDoubleSpinBox(&dialog);
    targetEdit->setRange(0, 100000000);
    targetEdit->setValue(goal.targetAmount);

    QDoubleSpinBox* currentEdit = new QDoubleSpinBox(&dialog);
    currentEdit->setRange(0, 100000000);
    currentEdit->setValue(goal.currentSaved);

    QDateEdit* dateEdit = new QDateEdit(goal.targetDate, &dialog);
    dateEdit->setCalendarPopup(true);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form.addRow("Название:", nameEdit);
    form.addRow("Цель (₽):", targetEdit);
    form.addRow("Собрано (₽):", currentEdit);
    form.addRow("Дата цели:", dateEdit);
    form.addRow(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        goal.name = nameEdit->text();
        goal.targetAmount = targetEdit->value();
        goal.currentSaved = currentEdit->value();
        goal.targetDate = dateEdit->date();
        return true;
    }
    return false;
}

// ================= ACTION SLOTS =================

void MainWindow::onAddIncome()
{
    QString name = lineIncomeName->text().trimmed();
    double amount = spinIncomeAmount->value();
    if (name.isEmpty() || amount <= 0) return;

    IncomeWithDate inc;
    inc.name = name;
    inc.amount = amount;
    inc.date = dateIncomeDate->date();
    inc.isRecurring = chkIncomeRecurring->isChecked();
    inc.recurringDay = spinIncomeRecurringDay->value();
    inc.durationMonths = chkIncomeLimited->isChecked() ? spinIncomeDuration->value() : 0;

    incomes.append(inc);
    updateIncomeList();
    updateMainInfo();
    saveData();

    lineIncomeName->clear();
    spinIncomeAmount->setValue(0);
    chkIncomeRecurring->setChecked(false);
    chkIncomeLimited->setChecked(false);
}

void MainWindow::onRemoveIncome()
{
    int row = listIncomes->currentRow();
    if (row >= 0 && row < incomes.size()) {
        incomes.remove(row);
        updateIncomeList();
        updateMainInfo();
        saveData();
    }
}

void MainWindow::onEditIncome()
{
    int row = listIncomes->currentRow();
    if (row < 0 || row >= incomes.size()) return;

    if (editIncomeDialog(incomes[row])) {
        updateIncomeList();
        updateMainInfo();
        saveData();
    }
}

void MainWindow::showIncomeContextMenu(const QPoint& pos)
{
    if (listIncomes->currentRow() < 0) return;
    QMenu menu;
    menu.addAction("Редактировать", this, &MainWindow::onEditIncome);
    menu.addAction("Удалить", this, &MainWindow::onRemoveIncome);
    menu.exec(listIncomes->viewport()->mapToGlobal(pos));
}

void MainWindow::updateIncomeList()
{
    listIncomes->clear();
    for (const auto& i : incomes) {
        QString recurring = i.isRecurring ? QString(" (каждое %1-е)").arg(i.recurringDay) : "";
        listIncomes->addItem(QString("%1: %2 ₽%3 (%4)").arg(i.name).arg(i.amount).arg(recurring).arg(i.date.toString("dd.MM.yyyy")));
    }
}

void MainWindow::onAddExpense()
{
    QString name = lineExpenseName->text().trimmed();
    double amount = spinExpenseAmount->value();
    if (name.isEmpty() || amount <= 0) return;

    ExpenseWithDate exp;
    exp.name = name;
    exp.amount = amount;
    exp.date = dateExpenseDate->date();
    exp.isMonthly = (comboExpenseType->currentIndex() == 0);
    exp.isRecurring = chkExpenseRecurring->isChecked();
    exp.recurringDay = spinExpenseRecurringDay->value();
    exp.durationMonths = chkExpenseLimited->isChecked() ? spinExpenseDuration->value() : 0;

    expenses.append(exp);
    updateExpenseList();
    updateMainInfo();
    saveData();

    lineExpenseName->clear();
    spinExpenseAmount->setValue(0);
    chkExpenseRecurring->setChecked(false);
    chkExpenseLimited->setChecked(false);
}

void MainWindow::onRemoveExpense()
{
    int row = listExpenses->currentRow();
    if (row >= 0 && row < expenses.size()) {
        expenses.remove(row);
        updateExpenseList();
        updateMainInfo();
        saveData();
    }
}

void MainWindow::onEditExpense()
{
    int row = listExpenses->currentRow();
    if (row < 0 || row >= expenses.size()) return;

    if (editExpenseDialog(expenses[row])) {
        updateExpenseList();
        updateMainInfo();
        saveData();
    }
}

void MainWindow::showExpenseContextMenu(const QPoint& pos)
{
    if (listExpenses->currentRow() < 0) return;
    QMenu menu;
    menu.addAction("Редактировать", this, &MainWindow::onEditExpense);
    menu.addAction("Удалить", this, &MainWindow::onRemoveExpense);
    menu.exec(listExpenses->viewport()->mapToGlobal(pos));
}

void MainWindow::updateExpenseList()
{
    listExpenses->clear();
    for (const auto& e : expenses) {
        QString typeStr = e.isMonthly ? "в месяц" : "в день";
        QString recurring = e.isRecurring ? QString(" (каждое %1-е)").arg(e.recurringDay) : "";
        listExpenses->addItem(QString("%1: %2 ₽%3 (%4) — %5").arg(e.name).arg(e.amount).arg(recurring).arg(typeStr).arg(e.date.toString("dd.MM.yyyy")));
    }
}

void MainWindow::onAddGoal()
{
    QString name = lineGoalName->text().trimmed();
    if (name.isEmpty() || spinGoalTarget->value() <= 0) return;

    SavingsGoal g;
    g.name = name;
    g.targetAmount = spinGoalTarget->value();
    g.currentSaved = spinGoalCurrent->value();
    g.targetDate = dateGoalDate->date();

    goals.append(g);
    updateGoalsList();
    saveData();

    lineGoalName->clear();
    spinGoalTarget->setValue(0);
    spinGoalCurrent->setValue(0);
}

void MainWindow::onRemoveGoal()
{
    int row = listGoals->currentRow();
    if (row >= 0 && row < goals.size()) {
        goals.remove(row);
        updateGoalsList();
        saveData();
    }
}

void MainWindow::onEditGoal()
{
    int row = listGoals->currentRow();
    if (row < 0 || row >= goals.size()) return;

    if (editGoalDialog(goals[row])) {
        updateGoalsList();
        saveData();
    }
}

void MainWindow::showGoalContextMenu(const QPoint& pos)
{
    if (listGoals->currentRow() < 0) return;
    QMenu menu;
    menu.addAction("Редактировать", this, &MainWindow::onEditGoal);
    menu.addAction("Удалить", this, &MainWindow::onRemoveGoal);
    menu.exec(listGoals->viewport()->mapToGlobal(pos));
}

void MainWindow::updateGoalsList()
{
    listGoals->clear();
    if (listGoalsMain) listGoalsMain->clear();

    for (const auto& g : goals) {
        double percent = (g.currentSaved / g.targetAmount) * 100;
        QString status = g.currentSaved >= g.targetAmount ? "✅ Достигнута!" :
                        QString("📊 %1%").arg(percent, 0, 'f', 1);
        QString itemText = QString("%1: %2 / %3 ₽ — %4 (до %5)")
                           .arg(g.name)
                           .arg(g.currentSaved)
                           .arg(g.targetAmount)
                           .arg(status)
                           .arg(g.targetDate.toString("dd.MM.yyyy"));
        listGoals->addItem(itemText);
        if (listGoalsMain) listGoalsMain->addItem(itemText);
    }
}

// ================= FINANCIAL CORE =================

double MainWindow::getMonthlySavings()
{
    double inc = 0;
    for (const auto& i : incomes) inc += i.amount;
    double exp = 0;
    for (const auto& e : expenses) {
        if (e.isMonthly) exp += e.amount;
        else exp += e.amount * 30;
    }
    return inc - exp;
}

double MainWindow::getTotalSaved()
{
    double s = 0;
    for (const auto& g : goals) s += g.currentSaved;
    return s;
}

void MainWindow::updateMainInfo()
{
    double inc = 0;
    for (const auto& i : incomes) inc += i.amount;
    double exp = 0;
    for (const auto& e : expenses) {
        if (e.isMonthly) exp += e.amount;
        else exp += e.amount * 30;
    }

    lblTotalIncome->setText(QString("Сумма доходов (в месяц): %1 ₽").arg(inc));
    lblTotalExpense->setText(QString("Сумма расходов (в месяц): %1 ₽").arg(exp));

    double rem = inc - exp;
    lblSavings->setText(QString("Свободный остаток: %1 ₽").arg(rem));
    if (rem >= 0) lblSavings->setStyleSheet("color: #2ecc71; font-weight: bold;");
    else lblSavings->setStyleSheet("color: #e74c3c; font-weight: bold;");

    updateGoalsList();
    updateCalendarColors();
}

void MainWindow::onCalculate()
{
    int idx = comboPurchaseType->currentIndex();
    if (idx == 0) calculateImmediatePurchase();
    else if (idx == 1) calculateInstallment();
    else if (idx == 2) calculateCredit();

    // Сохраняем рассчитанный ежемесячный платёж для кнопки
    calculatedMonthlyPayment = 0;
    if (idx == 1) {
        double rem = spinItemPrice->value() - spinDownPayment->value();
        if (rem > 0) {
            calculatedMonthlyPayment = rem / spinMonths->value();
        }
    } else if (idx == 2) {
        double loan = spinItemPrice->value() - spinDownPayment->value();
        int m = spinMonths->value();
        double r = doubleSpinInterest->value() / 100.0 / 12.0;
        if (r > 0) {
            calculatedMonthlyPayment = (loan * r * pow(1 + r, m)) / (pow(1 + r, m) - 1);
        } else {
            calculatedMonthlyPayment = loan / m;
        }
    }

    btnAddPurchaseToExpenses->setEnabled(spinItemPrice->value() > 0 && calculatedMonthlyPayment > 0);
}

void MainWindow::calculateImmediatePurchase()
{
    double price = spinItemPrice->value();
    int m = spinMonths->value();
    double target = price / m;
    double free = getMonthlySavings();

    QString res = QString("🛒 Вариант: Прямая покупка\nНеобходимые отчисления: %1 ₽ в месяц.\n").arg(target);
    if (free >= target) res += "✅ Ваш текущий профицит бюджета позволяет накопить в срок!";
    else res += "⚠️ Текущих свободных денег не хватает, нужно сократить расходы.";
    textResult->setPlainText(res);
}

void MainWindow::calculateInstallment()
{
    double rem = spinItemPrice->value() - spinDownPayment->value();
    if (rem <= 0) {
        textResult->setPlainText("Первоначальный взнос покрывает покупку полностью.");
        return;
    }
    double pay = rem / spinMonths->value();

    QString res = QString("🤝 Вариант: Рассрочка\nЕжемесячный платёж: %1 ₽\n").arg(pay);
    if (getMonthlySavings() >= pay) res += "✅ Одобрено: Бюджет справится.";
    else res += "❌ Риск: Платёж выше свободного остатка бюджета!";
    textResult->setPlainText(res);
}

void MainWindow::calculateCredit()
{
    double loan = spinItemPrice->value() - spinDownPayment->value();
    int m = spinMonths->value();
    double r = doubleSpinInterest->value() / 100.0 / 12.0;

    double pay = (r > 0) ? (loan * r * pow(1 + r, m)) / (pow(1 + r, m) - 1) : (loan / m);
    QString res = QString("💳 Вариант: Кредит\nПлатёж в месяц: %1 ₽\nПереплата по процентам: %2 ₽\n")
                  .arg(QString::number(pay, 'f', 0))
                  .arg(QString::number((pay * m) - loan, 'f', 0));
    textResult->setPlainText(res);
}

void MainWindow::onAddPurchaseToExpenses()
{
    if (calculatedMonthlyPayment <= 0) return;

    ExpenseWithDate exp;
    exp.name = lineItemName->text().isEmpty() ? "Крупная покупка" : lineItemName->text();
    exp.amount = calculatedMonthlyPayment;
    exp.date = QDate::currentDate();
    exp.isMonthly = true;
    exp.isRecurring = true;
    exp.recurringDay = QDate::currentDate().day();
    exp.durationMonths = spinMonths->value();

    expenses.append(exp);
    updateExpenseList();
    updateMainInfo();
    saveData();
    QMessageBox::information(this, "Успех", QString("Платёж %1 ₽ добавлен в расходы на %2 месяцев.")
                             .arg(calculatedMonthlyPayment, 0, 'f', 2)
                             .arg(spinMonths->value()));
}

// ================= CALENDAR =================

void MainWindow::onCalendarDayClicked(QDate date)
{
    QString info = QString("📅 День: %1\n").arg(date.toString("dd.MM.yyyy"));
    bool hasAny = false;

    // Доходы
    for (const auto& i : incomes) {
        if (i.date == date || (i.isRecurring && i.recurringDay == date.day())) {
            info += QString("   💰 [Доход] %1: +%2 ₽\n").arg(i.name).arg(i.amount);
            hasAny = true;
        }
    }

    // Расходы
    for (const auto& e : expenses) {
        // Ежедневные расходы — показываем каждый день!
        if (!e.isMonthly) {
            info += QString("   💸 [Расход] %1 (ежедневный): -%2 ₽\n").arg(e.name).arg(e.amount);
            hasAny = true;
        }
        // Обычные расходы по дате или повторяющиеся
        else if (e.date == date || (e.isRecurring && e.recurringDay == date.day())) {
            info += QString("   💸 [Расход] %1: -%2 ₽\n").arg(e.name).arg(e.amount);
            hasAny = true;
        }
    }

    if (!hasAny) {
        info += "✨ Нет запланированных операций";
    }

    calendarInfo->setPlainText(info);
}

void MainWindow::onCalendarMonthChanged(int year, int month)
{
    Q_UNUSED(year);
    Q_UNUSED(month);
    updateCalendarColors();
}

void MainWindow::updateCalendarColors()
{
    // Очищаем все подсветки
    QTextCharFormat defaultFormat;
    defaultFormat.setBackground(Qt::transparent);
    defaultFormat.setForeground(Qt::white);

    QDate currentDate(calendar->yearShown(), calendar->monthShown(), 1);
    while (currentDate.month() == calendar->monthShown()) {
        calendar->setDateTextFormat(currentDate, defaultFormat);
        currentDate = currentDate.addDays(1);
    }

    // Подсвечиваем доходы (зелёным)
    for (const auto& i : incomes) {
        if (i.isRecurring) {
            QDate date(calendar->yearShown(), calendar->monthShown(), i.recurringDay);
            if (date.isValid() && date.month() == calendar->monthShown()) {
                QTextCharFormat fmt;
                fmt.setBackground(QColor(46, 204, 113));
                fmt.setForeground(Qt::black);
                calendar->setDateTextFormat(date, fmt);
            }
        } else {
            if (i.date.year() == calendar->yearShown() && i.date.month() == calendar->monthShown()) {
                QTextCharFormat fmt;
                fmt.setBackground(QColor(46, 204, 113));
                fmt.setForeground(Qt::black);
                calendar->setDateTextFormat(i.date, fmt);
            }
        }
    }

    // Подсвечиваем расходы (красным) — ТОЛЬКО НЕ ЕЖЕДНЕВНЫЕ
    for (const auto& e : expenses) {
        // Ежедневные расходы НЕ подсвечиваем
        if (!e.isMonthly) {
            continue;  // пропускаем ежедневные расходы
        }
        else if (e.isRecurring) {
            QDate date(calendar->yearShown(), calendar->monthShown(), e.recurringDay);
            if (date.isValid() && date.month() == calendar->monthShown()) {
                QTextCharFormat fmt;
                fmt.setBackground(QColor(231, 76, 60));
                fmt.setForeground(Qt::white);
                calendar->setDateTextFormat(date, fmt);
            }
        } else {
            if (e.date.year() == calendar->yearShown() && e.date.month() == calendar->monthShown()) {
                QTextCharFormat fmt;
                fmt.setBackground(QColor(231, 76, 60));
                fmt.setForeground(Qt::white);
                calendar->setDateTextFormat(e.date, fmt);
            }
        }
    }
}

// ================= DATA STORAGE =================

void MainWindow::saveData()
{
    QJsonObject root;
    QJsonArray incArr;
    for (const auto& i : incomes) {
        QJsonObject obj;
        obj["name"] = i.name;
        obj["amount"] = i.amount;
        obj["date"] = i.date.toString(Qt::ISODate);
        obj["isRecurring"] = i.isRecurring;
        obj["recurringDay"] = i.recurringDay;
        obj["durationMonths"] = i.durationMonths;
        incArr.append(obj);
    }
    root["incomes"] = incArr;

    QJsonArray expArr;
    for (const auto& e : expenses) {
        QJsonObject obj;
        obj["name"] = e.name;
        obj["amount"] = e.amount;
        obj["date"] = e.date.toString(Qt::ISODate);
        obj["isMonthly"] = e.isMonthly;
        obj["isRecurring"] = e.isRecurring;
        obj["recurringDay"] = e.recurringDay;
        obj["durationMonths"] = e.durationMonths;
        expArr.append(obj);
    }
    root["expenses"] = expArr;

    QJsonArray goalArr;
    for (const auto& g : goals) {
        QJsonObject obj;
        obj["name"] = g.name;
        obj["targetAmount"] = g.targetAmount;
        obj["currentSaved"] = g.currentSaved;
        obj["targetDate"] = g.targetDate.toString(Qt::ISODate);
        goalArr.append(obj);
    }
    root["savingsGoals"] = goalArr;

    QFile file(QDir::homePath() + "/finance_data.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

void MainWindow::loadData()
{
    QFile file(QDir::homePath() + "/finance_data.json");
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonObject root = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    incomes.clear();
    for (auto v : root["incomes"].toArray()) {
        QJsonObject o = v.toObject();
        IncomeWithDate i;
        i.name = o["name"].toString();
        i.amount = o["amount"].toDouble();
        i.date = QDate::fromString(o["date"].toString(), Qt::ISODate);
        i.isRecurring = o["isRecurring"].toBool();
        i.recurringDay = o["recurringDay"].toInt();
        i.durationMonths = o["durationMonths"].toInt();
        incomes.append(i);
    }

    expenses.clear();
    for (auto v : root["expenses"].toArray()) {
        QJsonObject o = v.toObject();
        ExpenseWithDate e;
        e.name = o["name"].toString();
        e.amount = o["amount"].toDouble();
        e.date = QDate::fromString(o["date"].toString(), Qt::ISODate);
        e.isMonthly = o["isMonthly"].toBool();
        e.isRecurring = o["isRecurring"].toBool();
        e.recurringDay = o["recurringDay"].toInt();
        e.durationMonths = o["durationMonths"].toInt();
        expenses.append(e);
    }

    goals.clear();
    for (auto v : root["savingsGoals"].toArray()) {
        QJsonObject o = v.toObject();
        SavingsGoal g;
        g.name = o["name"].toString();
        g.targetAmount = o["targetAmount"].toDouble();
        g.currentSaved = o["currentSaved"].toDouble();
        g.targetDate = QDate::fromString(o["targetDate"].toString(), Qt::ISODate);
        goals.append(g);
    }
}
