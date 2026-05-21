#include "UsersPage.h"

UsersPage::UsersPage(QWidget *parent) : QWidget(parent){
    currentUserId = -1;
    kcalEaten = 0;
    proteinEaten = 0;
    fatEaten = 0;
    carbsEaten = 0;

    goToStatistics = new QPushButton("Перейти до статистики", this);

    kcalSeries = new QPieSeries();
    totalKcal = core.getDelta();
    if (totalKcal <= 0) totalKcal = 1;
    kcalEaten = 0;

    kcalSeries->append("Калорії", kcalEaten)->setColor(Qt::blue);
    int kcalRemaining = totalKcal - kcalEaten;
    if(kcalRemaining < 0) kcalRemaining = 0;
    kcalSeries->append("Залишок", kcalRemaining)->setColor(QColor("#ecf0f1"));

    kcalChart = new QChart();
    kcalChart->addSeries(kcalSeries);
    kcalChart->setTitle("Калорії");
    kcalChart->legend()->hide();
    kcalChart->setTitle(QString("Калорії: %1 / %2").arg(totalKcal - 1).arg(kcalEaten));
    kcalChart->setMargins(QMargins(0, 0, 0, 0));

    kcalView = new QChartView(kcalChart);
    kcalView->setRenderHint(QPainter::Antialiasing);
    kcalView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    kcalView->setMinimumSize(150, 150);
    kcalView->setMaximumHeight(300);

    proteinSeries = new QPieSeries();
    totalProtein = core.getProtein();
    if (totalProtein <= 0) totalProtein = 1;
    proteinEaten = 0;

    proteinSeries->append("Білки", proteinEaten)->setColor(Qt::green);
    int proteinRemaining = totalProtein - proteinEaten;
    if(proteinRemaining < 0) proteinRemaining = 0;
    proteinSeries->append("Залишок", proteinRemaining)->setColor(QColor("#ecf0f1"));

    proteinChart = new QChart();
    proteinChart->addSeries(proteinSeries);
    proteinChart->setTitle("Білки");
    proteinChart->legend()->hide();
    proteinChart->setTitle(QString("Білки: %1 / %2").arg(totalProtein - 1).arg(proteinEaten));
    proteinChart->setMargins(QMargins(0, 0, 0, 0));

    proteinView = new QChartView(proteinChart);
    proteinView->setRenderHint(QPainter::Antialiasing);
    proteinView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    proteinView->setMinimumSize(150, 150);
    proteinView->setMaximumHeight(300);

    fatSeries = new QPieSeries();
    totalFat = core.getFat();
    if (totalFat <= 0) totalFat = 1;
    fatEaten = 0;

    fatSeries->append("Жири", fatEaten)->setColor(Qt::yellow);
    int fatRemaining = totalFat - fatEaten;
    if(fatRemaining < 0) fatRemaining = 0;
    fatSeries->append("Залишок", fatRemaining)->setColor(QColor("#ecf0f1"));

    fatChart = new QChart();
    fatChart->addSeries(fatSeries);
    fatChart->setTitle("Жири");
    fatChart->legend()->hide();
    fatChart->setTitle(QString("Жири: %1 / %2").arg(totalFat - 1).arg(fatEaten));
    fatChart->setMargins(QMargins(0, 0, 0, 0));

    fatView = new QChartView(fatChart);
    fatView->setRenderHint(QPainter::Antialiasing);
    fatView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fatView->setMinimumSize(150, 150);
    fatView->setMaximumHeight(300);

    carbsSeries = new QPieSeries();
    totalCarbs = core.getCarbs();
    if (totalCarbs <= 0) totalCarbs = 1;
    carbsEaten = 0;

    carbsSeries->append("Вуглеводи", carbsEaten)->setColor(QColor("orange"));
    int carbsRemaining = totalCarbs - carbsEaten;
    if(carbsRemaining < 0) carbsRemaining = 0;
    carbsSeries->append("Залишок", carbsRemaining)->setColor(QColor("#ecf0f1"));

    carbsChart = new QChart();
    carbsChart->addSeries(carbsSeries);
    carbsChart->setTitle("Вуглеводи");
    carbsChart->legend()->hide();
    carbsChart->setTitle(QString("Вуглеводи: %1 / %2").arg(totalCarbs - 1).arg(carbsEaten));
    carbsChart->setMargins(QMargins(0, 0, 0, 0));

    carbsView = new QChartView(carbsChart);
    carbsView->setRenderHint(QPainter::Antialiasing);
    carbsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    carbsView->setMinimumSize(150, 150);
    carbsView->setMaximumHeight(300);

    diagramLayout = new QHBoxLayout();
    diagramLayout->addWidget(kcalView);
    diagramLayout->addWidget(proteinView);
    diagramLayout->addWidget(fatView);
    diagramLayout->addWidget(carbsView);

    addMeal = new QPushButton("Додати прийом їжі", this);
    updateWeight = new QPushButton("Оновити вагу", this);
    backButton = new QPushButton("Назад", this);

    pageLayout = new QVBoxLayout(this);
    pageLayout->addWidget(goToStatistics);
    pageLayout->addLayout(diagramLayout);
    pageLayout->addWidget(addMeal);
    pageLayout->addWidget(updateWeight);
    pageLayout->addWidget(backButton);

    this->setMinimumSize(900, 500);
    this->setLayout(pageLayout);

    connect(addMeal, &QPushButton::clicked, this, &UsersPage::onAddMealClicked);
    connect(backButton, &QPushButton::clicked, this, [this](){ emit backRequested(); });
    connect(goToStatistics, &QPushButton::clicked, this, [this](){ emit statisticsRequested(); });
    connect(updateWeight, &QPushButton::clicked, this, &UsersPage::onUpdateWeightClicked);
}

void UsersPage::setActiveUserId(int id){
    currentUserId = id;
}

void UsersPage::updateCharts(MetabolicCore& updatedCore){
    this->core.copyDataFrom(updatedCore);

    totalKcal = core.getDelta();
    if(totalKcal <= 0) totalKcal = 1;

    kcalSeries->clear();

    kcalSeries->append("Калорії", kcalEaten)->setColor(Qt::blue);
    int kcalRemaining = totalKcal - kcalEaten;
    if(kcalRemaining < 0) kcalRemaining = 0;
    kcalSeries->append("Залишок", kcalRemaining)->setColor(QColor("#ecf0f1"));
    kcalChart->setTitle(QString("Калорії: %1 / %2").arg(totalKcal - 1).arg(kcalEaten));

    totalProtein = core.getProtein();
    if(totalProtein <= 0) totalProtein = 1;

    proteinSeries->clear();

    proteinSeries->append("Білки", proteinEaten)->setColor(Qt::green);
    int proteinRemaining = totalProtein - proteinEaten;
    if(proteinRemaining < 0) proteinRemaining = 0;
    proteinSeries->append("Залишок", proteinRemaining)->setColor(QColor("#ecf0f1"));
    proteinChart->setTitle(QString("Білки: %1 / %2").arg(totalProtein - 1).arg(proteinEaten));

    totalFat = core.getFat();
    if(totalFat <= 0) totalFat = 1;

    fatSeries->clear();

    fatSeries->append("Жири", fatEaten)->setColor(Qt::yellow);
    int fatRemaining = totalFat - fatEaten;
    if(fatRemaining < 0) fatRemaining = 0;
    fatSeries->append("Залишок", fatRemaining)->setColor(QColor("#ecf0f1"));
    fatChart->setTitle(QString("Жири: %1 / %2").arg(totalFat - 1).arg(fatEaten));

    totalCarbs = core.getCarbs();
    if(totalCarbs <= 0) totalCarbs = 1;

    carbsSeries->clear();

    carbsSeries->append("Вуглеводи", carbsEaten)->setColor(QColor("orange"));
    int carbsRemaining = totalCarbs - carbsEaten;
    if(carbsRemaining < 0) carbsRemaining = 0;
    carbsSeries->append("Залишок", carbsRemaining)->setColor(QColor("#ecf0f1"));
    carbsChart->setTitle(QString("Вуглеводи: %1 / %2").arg(totalCarbs - 1).arg(carbsEaten));
}

void UsersPage::onAddMealClicked(){
    QDialog dialog(this);
    dialog.setWindowTitle("Додавання їжі");
    dialog.setMinimumWidth(250);

    QFormLayout form(&dialog);

    QSpinBox kcalBox(&dialog);
    kcalBox.setRange(0, 8000);

    QSpinBox proteinBox(&dialog);
    proteinBox.setRange(0, 2000);

    QSpinBox fatBox(&dialog);
    fatBox.setRange(0, 1000);

    QSpinBox carbsBox(&dialog);
    carbsBox.setRange(0, 2000);

    form.addRow("Калорії", &kcalBox);
    form.addRow("Білки", &proteinBox);
    form.addRow("Жири", &fatBox);
    form.addRow("Вуглеводи", &carbsBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        kcalEaten += kcalBox.value();
        proteinEaten += proteinBox.value();
        fatEaten += fatBox.value();
        carbsEaten += carbsBox.value();

        updateCharts(this->core);

        QDate today = QDate::currentDate();

        dbManager.addMealToLog(this->currentUserId, today, kcalBox.value(), proteinBox.value(), fatBox.value(), carbsBox.value());
    }
}

void UsersPage::onUpdateWeightClicked(){
    QDialog dialog(this);
    dialog.setWindowTitle("Оновлення ваги");
    dialog.setMinimumWidth(250);

    QFormLayout form(&dialog);

    QDoubleSpinBox weightBox(&dialog);
    weightBox.setRange(30, 300);
    weightBox.setDecimals(1);

    form.addRow("Вага", &weightBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        double newWeight = weightBox.value();

        if (dbManager.updateUserWeight(this->currentUserId, newWeight)) {
            User updatedUser;
            if(dbManager.loadUser(updatedUser, this->currentUserId)){
                this->core.calculateNorm(updatedUser);
                updateCharts(this->core);
            }
        }
    }
}

void UsersPage::loadEatenData(int k, int p, int f, int c){
    kcalEaten = k;
    proteinEaten = p;
    fatEaten = f;
    carbsEaten = c;
}