#include "StatisticsPage.h"
#include <QPainter>
#include <QPen>

StatisticsPage::StatisticsPage(QWidget *parent) : QWidget(parent) {
    backButton = new QPushButton("Назад", this);
    backButton->setFixedSize(100, 30);
    
    btnCalories = new QPushButton("Калорії", this);
    btnWeight = new QPushButton("Вага", this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(backButton);
    topLayout->addWidget(btnCalories);
    topLayout->addWidget(btnWeight);
    topLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addStretch();

    this->setMinimumSize(600, 400);

    connect(backButton, &QPushButton::clicked, this, [this](){ emit backRequested(); });
    
    connect(btnCalories, &QPushButton::clicked, this, [this]() {
        showWeightGraph = false;
        update();
    });

    connect(btnWeight, &QPushButton::clicked, this, [this]() {
        showWeightGraph = true;
        update();
    });
}

void StatisticsPage::loadStatistics(int userId, DataBaseManager* dbManager) {
    currentUserId = userId;
    historyData = dbManager->getMonthlyHistory(userId); 
    update(); 
}

void StatisticsPage::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    if (historyData.isEmpty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int paddingLeft = 50;
    int paddingBottom = 50;
    int paddingTop = 80;
    int paddingRight = 30;

    int chartWidth = width() - paddingLeft - paddingRight;
    int chartHeight = height() - paddingTop - paddingBottom;

    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(paddingLeft, paddingTop + chartHeight, paddingLeft + chartWidth, paddingTop + chartHeight);
    painter.drawLine(paddingLeft, paddingTop, paddingLeft, paddingTop + chartHeight);

    double maxVal = 0;
    double minVal = 99999;

    for (const DailyLog& log : historyData) {
        double val = showWeightGraph ? log.getWeight() : log.getKcal();
        if (showWeightGraph && val == 0) continue; 
        if (val > maxVal) maxVal = val;
        if (val < minVal) minVal = val;
    }

    double topLimit, bottomLimit;
    
    if (showWeightGraph) {
        topLimit = maxVal + 2.0;
        bottomLimit = (minVal > 2.0) ? minVal - 2.0 : 0.0;
    } else {
        topLimit = maxVal + (maxVal * 0.2);
        bottomLimit = 0.0;
    }

    double range = topLimit - bottomLimit;
    if (range <= 0) range = 1;

    int stepX = chartWidth / (historyData.size() > 1 ? historyData.size() - 1 : 1);
    QPoint previousPoint;

    for (int i = 0; i < historyData.size(); ++i) {
        int stepX = chartWidth / (historyData.size() > 1 ? historyData.size() - 1 : 1);
        
        QPoint previousPoint;
        bool hasPrevious = false;

        for (int i = 0; i < historyData.size(); ++i) {
            double val = showWeightGraph ? historyData[i].getWeight() : historyData[i].getKcal();
            
            if (showWeightGraph && val == 0.0) continue; 

            QString dateStr = historyData[i].getDate().toString("dd.MM");

            int x = paddingLeft + (i * stepX);
            int y = (paddingTop + chartHeight) - ((val - bottomLimit) / range * chartHeight);

            QPoint currentPoint(x, y);

            if (hasPrevious) {
                painter.setPen(QPen(showWeightGraph ? Qt::darkGreen : Qt::blue, 3));
                painter.drawLine(previousPoint, currentPoint);
            }

            painter.setPen(Qt::NoPen);
            painter.setBrush(Qt::red);
            painter.drawEllipse(currentPoint, 5, 5);

            painter.setPen(Qt::black);
            painter.drawText(x - 15, paddingTop + chartHeight + 20, dateStr);
            
            QString valText = showWeightGraph ? QString::number(val, 'f', 1) : QString::number((int)val);
            painter.drawText(x - 15, y - 10, valText);

            previousPoint = currentPoint;
            hasPrevious = true;
        }
    }
}