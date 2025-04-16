#include "driverhistoryoftraject.h"
#include "ui_driverhistoryoftraject.h"
#include "driverhomepage.h"

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

    for (auto& traject : driverTrajects) {
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

        // Buttons
        QPushButton* completeButton = new QPushButton("Completed", trajectWidget);
        completeButton->setFixedWidth(100);
        completeButton->setVisible(traject.getStatus() == "confirmed");

        QPushButton* cancelButton = new QPushButton("Cancel", trajectWidget);
        cancelButton->setFixedWidth(100);
        cancelButton->setVisible(traject.getStatus() != "cancelled" && traject.getStatus() != "completed");

        int trajectid = traject.getId();

        connect(cancelButton, &QPushButton::clicked, this, [this, trajectid, statusLabel, completeButton, cancelButton]() {
            Traject traject = Traject::getTrajectById(trajectid);
            traject.setStatus("canceled");
            traject.saveTrajectToDB();
            statusLabel->setText("Status: cancelled");
            cancelButton->setVisible(false);
            completeButton->setVisible(false);
        });

        // Layout for one traject
        hLayout->addLayout(detailsLayout);
        hLayout->addStretch();
        hLayout->addWidget(completeButton, 0, Qt::AlignVCenter);
        hLayout->addWidget(cancelButton, 0, Qt::AlignVCenter);

        trajectWidget->setLayout(hLayout);
        layout->addWidget(trajectWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);

    // Add scroll area and back button to the main layout
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(ui->backBtn); // ✅ Affiche le bouton Retour
    setLayout(mainLayout);

    // Action du bouton backBtn
    connect(ui->backBtn, &QPushButton::clicked, this, [this, user]() {
        DriverHomePage* homePage = new DriverHomePage(user, nullptr);
        homePage->show();
        this->hide();
    });
}

DriverHistoryOfTraject::~DriverHistoryOfTraject()
{
    delete ui;
}
