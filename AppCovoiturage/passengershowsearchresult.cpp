#include "passengershowsearchresult.h"
#include "ui_passengershowsearchresult.h"
#include <QProcess>
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

#include "traject.h"

PassengerShowSearchResult::PassengerShowSearchResult(User* user, int searchId, QWidget *parent)
    : QWidget(parent), ui(new Ui::PassengerShowSearchResult)
{
    // Create layout for the main window before using it
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Initially hide the UI elements until the Python script is done
    this->setVisible(false);

    // Start Python script with search ID as argument
    QProcess *process = new QProcess(this);

    QString currentDir = QCoreApplication::applicationDirPath();
    QString script_path = currentDir + "/../../../../Script/GetResult.py";
    QString pythonInterpreter = "C:/Users/PC/Desktop/oumayma/Projects/AppCovoiturageProject/Script/.venv/Scripts/python.exe";  // Path to your Python virtual environment
    qDebug() << "Starting Python script at: " << script_path;

    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QString output = process->readAllStandardOutput();
        qDebug() << "Python Output:" << output;

        // Parse output, remove square brackets and split by commas
        QStringList trajectIds = output.trimmed().mid(1, output.length() - 2).split(',', Qt::SkipEmptyParts);
        qDebug() << "Parsed Traject IDs:" << trajectIds;

        if (trajectIds.isEmpty()) {
            QLabel* noResultsLabel = new QLabel("No results found.", this);
            mainLayout->addWidget(noResultsLabel);
        }

        // Create a scrollable area to hold the search history items
        QScrollArea* scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);

        // Container widget inside the scroll area
        QWidget* container = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(container);

        // Loop through each trajectId in the output
        for (const QString &trajectIdStr : trajectIds) {
            bool ok;
            int trajectId = trajectIdStr.trimmed().toInt(&ok);  // Ensure trimming spaces
            if (!ok || trajectId == -1) {
                qDebug() << "Skipping invalid or excluded Traject ID:" << trajectIdStr;
                continue;
            }

            // Get the traject by ID
            Traject traject = Traject::getTrajectById(trajectId);
            if (traject.getId() == 0) {
                qDebug() << "Error: No traject found with ID:" << trajectId;
                continue;  // Skip if traject not found
            }

            qDebug() << "Creating widget for Traject ID:" << trajectId;  // Debug line to check if this is called

            // Create widget for traject details
            QWidget* searchWidget = new QWidget(this);
            QHBoxLayout* hLayout = new QHBoxLayout(searchWidget);

            // Left section (Details)
            QVBoxLayout* detailsLayout = new QVBoxLayout();
            QLabel* routeLabel = new QLabel(
                QString::fromStdString(traject.getDepart()) + " ➝ " +
                    QString::fromStdString(traject.getDestination()), searchWidget
                );

            QLabel* dateTimeLabel = new QLabel(
                QString::fromStdString(traject.getDateTime()), searchWidget
                );

            QLabel* availableSeatsLabel = new QLabel(
                "Available Seats: " + QString::number(traject.getAvailableSeats()), searchWidget
                );

            QLabel* priceLabel = new QLabel(
                "Price: " + QString::number(traject.getPrice(), 'f', 2), searchWidget
                );

            detailsLayout->addWidget(routeLabel);
            detailsLayout->addWidget(dateTimeLabel);
            detailsLayout->addWidget(availableSeatsLabel);
            detailsLayout->addWidget(priceLabel);

            // Button for "Research"
            QPushButton* researchButton = new QPushButton("Research", searchWidget);
            researchButton->setFixedWidth(100);

            // Button Actions
            connect(researchButton, &QPushButton::clicked, this, [=]() {
                qDebug() << "Research button clicked for Traject ID: " << traject.getId();
                // Implement logic when the "Research" button is clicked
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

        // After processing the data, show the UI
        this->setVisible(true);  // Show the UI once data is processed
    });

    connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError error) {
        qDebug() << "Error occurred:" << error;
        qDebug() << "Error string:" << process->errorString();
    });

    if (!process->startDetached(pythonInterpreter, QStringList() << script_path << QString::number(searchId))) {
        qDebug() << "Failed to start Python script!";
    } else {
        qDebug() << "Python script started successfully!";
    }

    ui->setupUi(this);
}



PassengerShowSearchResult::~PassengerShowSearchResult()
{
    delete ui;
}
