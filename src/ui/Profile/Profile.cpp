#include "Profile.h"

Profile::Profile(QWidget *parent) :QWidget(parent){
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

    button = new QPushButton("Розрахувати норму", this);

    profileLayout = new QFormLayout(this);

    this->resize(400, 500);
    this->setWindowTitle("My Profile");

    profileLayout->addRow("Стать:", sexBox);
    profileLayout->addRow("Вік:", ageBox);
    profileLayout->addRow("Ріст (см):", heightBox);
    profileLayout->addRow("Вага (кг):", weightBox);
    profileLayout->addRow("Рівень активності:", activityBox);
    profileLayout->addRow("Ціль:", goalBox);
    profileLayout->addRow(button);

    this->setLayout(profileLayout);

    connect(button, &QPushButton::clicked, this, &Profile::onButtonClicked);
}

void Profile::onButtonClicked(){
 bool userSex = sexBox->currentData().toBool();
    double userBodyWeight = weightBox->value();
    double userHeight = heightBox->value();
    int userAge = ageBox->value();
    double activityCoefficient = activityBox->currentData().toDouble();
    int goal = goalBox->currentData().toInt();

    core.calculateNorm(userSex, userBodyWeight, userHeight, userAge, activityCoefficient, goal);

    qDebug() << "Розрахунок завершено!";
    qDebug() << "Калорії:" << core.delta;
    qDebug() << "Білки:" << core.protein;
    qDebug() << "Жири:" << core.fat;
    qDebug() << "Вуглеводи:" << core.carbs;
}