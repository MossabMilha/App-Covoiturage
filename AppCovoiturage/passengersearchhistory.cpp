#include "passengersearchhistory.h"
#include "ui_passengersearchhistory.h"

PassengerSearchHistory::PassengerSearchHistory(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PassengerSearchHistory)
{
    ui->setupUi(this);

    // Get the user search history
    std::vector<Search> UserSearch = Search::getUserSearch(user->getId());
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Scrollable area to hold the search history items
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Container widget inside the scroll area
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (auto& search : UserSearch) {
        QWidget* searchWidget = new QWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout(searchWidget);

        // Left section (Details)
        QVBoxLayout* detailsLayout = new QVBoxLayout();
        QLabel* routeLabel = new QLabel(
            QString::fromStdString(search.getDepart()) + " ➝ " +
                QString::fromStdString(search.getDestination()), searchWidget
            );

        QLabel* dateTimeLabel = new QLabel(
            QString::fromStdString(search.getDateTime()), searchWidget
            );

        QLabel* searchTimeLabel = new QLabel(
            "Search Time: " + QString::fromStdString(search.getSearchTime()), searchWidget
            );

        detailsLayout->addWidget(routeLabel);
        detailsLayout->addWidget(dateTimeLabel);
        detailsLayout->addWidget(searchTimeLabel);

        // Button for "Research"
        QPushButton* researchButton = new QPushButton("Research", searchWidget);
        researchButton->setFixedWidth(100);

        // Button Actions (You can modify this to do whatever action is needed when clicking the button)
        connect(researchButton, &QPushButton::clicked, this, [=]() {
            qDebug()<< "YOw";
        });

        // Layout adjustments
        hLayout->addLayout(detailsLayout);
        hLayout->addStretch();
        hLayout->addWidget(researchButton, 0, Qt::AlignVCenter);

        searchWidget->setLayout(hLayout);
        layout->addWidget(searchWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);

    // Add scroll area to the main layout
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}


PassengerSearchHistory::~PassengerSearchHistory()
{
    delete ui;
}
