#include "Profile.h"
#include <QMessageBox>
#include <QString>

Profile::Profile(QWidget *parent) :QWidget(parent){
    nameBox = new QLineEdit(this);

    ageBox = new QSpinBox(this);

    ageBox->setRange(0, 100);
    ageBox->setValue(20);      
    ageBox->setSuffix(" років");

    weightBox = new QDoubleSpinBox(this);

    weightBox->setRange(30.0, 300.0);
    weightBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

    heightBox = new QDoubleSpinBox(this);

    heightBox->setRange(100.0, 300.0);
    heightBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

    sexBox = new QComboBox(this);

    sexBox->addItem("male", true);
    sexBox->addItem("female", false);

    activityBox = new QComboBox(this);

    activityBox->addItem("Сидячий спосіб життя", 1.2);
    activityBox->addItem("Легка активність", 1.375);
    activityBox->addItem("Середня активність", 1.55);
    activityBox->addItem("Висока активність", 1.725);
    activityBox->addItem("Екстремальна активність", 1.9);

    goalBox = new QComboBox(this);

    goalBox->addItem("Схуднути", -15);
    goalBox->addItem("Підтримувати вагу", 0);
    goalBox->addItem("Набрати вагу", 15);

    calculateButton = new QPushButton("Розрахувати норму", this);
    backButton = new QPushButton("Назад", this);

    profileLayout = new QFormLayout(this);

    this->resize(400, 500);
    this->setWindowTitle("My Profile");

    profileLayout->addRow("Ім'я:", nameBox);
    profileLayout->addRow("Стать:", sexBox);
    profileLayout->addRow("Вік:", ageBox);
    profileLayout->addRow("Ріст (см):", heightBox);
    profileLayout->addRow("Вага (кг):", weightBox);
    profileLayout->addRow("Рівень активності:", activityBox);
    profileLayout->addRow("Ціль:", goalBox);
    profileLayout->addRow(calculateButton);
    profileLayout->addRow(backButton);

    this->setLayout(profileLayout);

    connect(calculateButton, &QPushButton::clicked, this, [this](){ emit usersPageRequested(); });
    connect(backButton, &QPushButton::clicked, this, [this](){ emit backRequested(); });
}

void Profile::loadDataToUi(){
    nameBox->setText(currentUser.getUserName());
    ageBox->setValue(currentUser.getAge());
    heightBox->setValue(currentUser.getHeight());
    weightBox->setValue(currentUser.getBodyWeight());

    int sexIndex = sexBox->findData(currentUser.getSex());
    if (sexIndex != -1) sexBox->setCurrentIndex(sexIndex);

    int activityIndex = activityBox->findData(currentUser.getActivityCoefficient());
    if (activityIndex != -1) activityBox->setCurrentIndex(activityIndex);

    int goalIndex = goalBox->findData(currentUser.getGoal());
    if (goalIndex != -1) goalBox->setCurrentIndex(goalIndex);
}

void Profile::loadUserFromDB(int userId) {
    dbManager.setupDataBase();
    if (dbManager.loadUser(currentUser, userId)) {
        currentUser.setId(userId);
        loadDataToUi();

        core.calculateNorm(currentUser);
    }
}

void Profile::saveUser(){
    currentUser.setUserName(nameBox->text());
    currentUser.setSex(sexBox->currentData().toBool());
    currentUser.setBodyWeight(weightBox->value());
    currentUser.setHeight(heightBox->value());
    currentUser.setAge(ageBox->value());
    currentUser.setActivityCoefficient(activityBox->currentData().toDouble());
    currentUser.setGoal(goalBox->currentData().toInt());

    core.calculateNorm(currentUser);

    dbManager.setupDataBase();
    dbManager.saveUser(currentUser);
}

MetabolicCore& Profile::getCore(){
    return core;
}

int Profile::getCurrentUserId(){
    return currentUser.getId();
}