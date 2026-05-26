#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDate>
#include <QCalendarWidget>
#include <QTextBrowser>
#include <QListWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QDialog>
#include <QFormLayout>
#include <QTabWidget>

struct IncomeWithDate {
    QString name;
    double amount;
    QDate date;
    bool isRecurring;
    int recurringDay;
    int durationMonths = 0;
};

struct ExpenseWithDate {
    QString name;
    double amount;
    QDate date;
    bool isRecurring;
    int recurringDay;
    bool isMonthly;
    int durationMonths = 0;
};

struct SavingsGoal {
    QString name;
    double targetAmount;
    double currentSaved;
    QDate targetDate;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddIncome();
    void onRemoveIncome();
    void onEditIncome();
    void onAddExpense();
    void onRemoveExpense();
    void onEditExpense();
    void onAddGoal();
    void onRemoveGoal();
    void onEditGoal();
    void onCalculate();
    void onAddPurchaseToExpenses();
    void onCalendarDayClicked(QDate date);
    void onCalendarMonthChanged(int year, int month);
    void showIncomeContextMenu(const QPoint& pos);
    void showExpenseContextMenu(const QPoint& pos);
    void showGoalContextMenu(const QPoint& pos);

private:
    QVector<IncomeWithDate> incomes;
    QVector<ExpenseWithDate> expenses;
    QVector<SavingsGoal> goals;

    // Виджеты для доходов
    QListWidget* listIncomes;
    QLineEdit* lineIncomeName;
    QSpinBox* spinIncomeAmount;
    QDateEdit* dateIncomeDate;
    QCheckBox* chkIncomeRecurring;
    QSpinBox* spinIncomeRecurringDay;
    QCheckBox* chkIncomeLimited;
    QSpinBox* spinIncomeDuration;

    // Виджеты для расходов
    QListWidget* listExpenses;
    QLineEdit* lineExpenseName;
    QSpinBox* spinExpenseAmount;
    QDateEdit* dateExpenseDate;
    QCheckBox* chkExpenseRecurring;
    QSpinBox* spinExpenseRecurringDay;
    QComboBox* comboExpenseType;
    QCheckBox* chkExpenseLimited;
    QSpinBox* spinExpenseDuration;

    // Виджеты для целей
    QListWidget* listGoals;
    QListWidget* listGoalsMain;  // для отображения на главной вкладке
    QLineEdit* lineGoalName;
    QDoubleSpinBox* spinGoalTarget;
    QDoubleSpinBox* spinGoalCurrent;
    QDateEdit* dateGoalDate;

    // Главная информация
    QLabel* lblTotalIncome;
    QLabel* lblTotalExpense;
    QLabel* lblSavings;

    // Виджеты для покупок
    QLineEdit* lineItemName;
    QDoubleSpinBox* spinItemPrice;
    QSpinBox* spinMonths;
    QDoubleSpinBox* spinDownPayment;
    QDoubleSpinBox* doubleSpinInterest;
    QComboBox* comboPurchaseType;
    QPushButton* btnCalculate;
    QPushButton* btnAddPurchaseToExpenses;
    QTextEdit* textResult;
    double calculatedMonthlyPayment = 0;  // для хранения рассчитанного платежа

    // Календарь
    QCalendarWidget* calendar;
    QTextBrowser* calendarInfo;
    QTabWidget* tabWidget;

    // Методы
    void setupUI();
    void updateIncomeList();
    void updateExpenseList();
    void updateGoalsList();
    void updateMainInfo();
    void updateCalendarColors();
    double getMonthlySavings();
    double getTotalSaved();
    void saveData();
    void loadData();
    void calculateImmediatePurchase();
    void calculateInstallment();
    void calculateCredit();

    bool editIncomeDialog(IncomeWithDate& income);
    bool editExpenseDialog(ExpenseWithDate& expense);
    bool editGoalDialog(SavingsGoal& goal);

    QWidget* createMainTab();
    QWidget* createIncomeTab();
    QWidget* createExpenseTab();
    QWidget* createGoalsTab();
    QWidget* createCalendarTab();
    QWidget* createPurchaseTab();
    QWidget* createTopBar();
};

#endif // MAINWINDOW_H
