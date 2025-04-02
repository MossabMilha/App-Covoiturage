#include "driverhistoryoftraject.h"
#include "ui_driverhistoryoftraject.h"

DriverHistoryOfTraject::DriverHistoryOfTraject(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DriverHistoryOfTraject)
{
    ui->setupUi(this);

    std::vector<Traject> driverTrajects = Traject::getUserTrajects(user->getId());
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Scrollable area to hold the trajects
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Container widget inside the scroll area
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (auto& traject : driverTrajects) {  // Use non-const reference here
        QWidget* trajectWidget = new QWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout(trajectWidget);

        // Left section (Details)
        QVBoxLayout* detailsLayout = new QVBoxLayout();
        QLabel* routeLabel = new QLabel(
            QString::fromStdString(traject.getDepart()) + " ➝ " +
                QString::fromStdString(traject.getDestination()), trajectWidget
            );

        QLabel* dateTimeLabel = new QLabel(
            QString::fromStdString(traject.getDateTime()), trajectWidget
            );

        QLabel* statusLabel = new QLabel(
            "Status: " + QString::fromStdString(traject.getStatus()), trajectWidget
            );

        detailsLayout->addWidget(routeLabel);
        detailsLayout->addWidget(dateTimeLabel);
        detailsLayout->addWidget(statusLabel);

        // Buttons (Only shown under specific conditions)
        QPushButton* completeButton = new QPushButton("Completed", trajectWidget);
        completeButton->setFixedWidth(100);
        completeButton->setVisible(traject.getStatus() == "confirmed");

        QPushButton* cancelButton = new QPushButton("Cancel", trajectWidget);
        cancelButton->setFixedWidth(100);
        cancelButton->setVisible(traject.getStatus() != "cancelled" && traject.getStatus() != "completed");
        int trajectid = traject.getId();
        // Button Actions
        connect(cancelButton, &QPushButton::clicked, this, [this,trajectid, statusLabel, completeButton, cancelButton]() {
            Traject traject = Traject::getTrajectById(trajectid); // Add debug information
            traject.setStatus("canceled");
            traject.saveTrajectToDB();
            statusLabel->setText("Status: cancelled");
            cancelButton->setVisible(false);
            completeButton->setVisible(false);
        });

        // connect(cancelButton, &QPushButton::clicked, this, [this, trajectid, statusLabel, completeButton, cancelButton]() {
        //     Traject traject = Traject::getTrajectById(trajectid);
        //     traject.setStatus("cancelled");
        //     traject.saveTrajectToDB();
        //     statusLabel->setText("Status: cancelled");
        //     cancelButton->setVisible(false);
        //     completeButton->setVisible(false);
        // });

        // Layout adjustments
        hLayout->addLayout(detailsLayout);
        hLayout->addStretch();
        hLayout->addWidget(completeButton, 0, Qt::AlignVCenter);
        hLayout->addWidget(cancelButton, 0, Qt::AlignVCenter);

        trajectWidget->setLayout(hLayout);
        layout->addWidget(trajectWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);

    // Add scroll area to the main layout
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}



DriverHistoryOfTraject::~DriverHistoryOfTraject()
{
    delete ui;
}
