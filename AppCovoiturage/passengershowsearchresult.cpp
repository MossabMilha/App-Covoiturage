#include "passengershowsearchresult.h"
#include "qforeach.h"
#include "ui_passengershowsearchresult.h"

QList<int> PassengerShowSearchResult::getSearchResult(int searchId) {
    QList<int> resultList;

    // Define paths
    QString currentDir = QCoreApplication::applicationDirPath();
    QString scriptPath = currentDir + "/../../../../Script/GetResult.py";
    QString pythonInterpreter = currentDir + "/../../../../Script/.venv/Scripts/python.exe";

    // Setup the process
    QProcess process;
    QStringList arguments;
    arguments << scriptPath << QString::number(searchId);

    process.start(pythonInterpreter, arguments);
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    QByteArray errorOutput = process.readAllStandardError();

    if (!errorOutput.isEmpty()) {
        qDebug() << "Python error:" << errorOutput;
    }

    // Parse JSON result
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(output, &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isArray()) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return resultList; // Return empty list on error
    }

    QJsonArray jsonArray = doc.array();
    for (const QJsonValue& val : jsonArray) {
        if (val.isDouble()) {
            resultList.append(val.toInt());
        }
    }

    return resultList;
}

PassengerShowSearchResult::PassengerShowSearchResult(User* user, int searchId, QWidget *parent)
    : QWidget(parent), ui(new Ui::PassengerShowSearchResult)
{
    ui->setupUi(this);

    QList<int> resultList = getSearchResult(searchId);
    qDebug()<< resultList;

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Container for items
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);
    if (!resultList.isEmpty() && resultList.first() == -1) {
        QMessageBox::information(this, "No Exact Match",
                                 "No exact traject found for your search.\nHere are some similar suggestions.");


        resultList.removeFirst();
    }
    for (auto& trajectId : resultList) {
        Traject traject = Traject::getTrajectById(trajectId);

        QWidget* trajectWidget = new QWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout(trajectWidget);

        // Left: details
        QVBoxLayout* detailsLayout = new QVBoxLayout();

        QLabel* routeLabel = new QLabel(
            QString::fromStdString(traject.getDepart()) + " ➝ " +
                QString::fromStdString(traject.getDestination()), trajectWidget
            );

        QLabel* dateTimeLabel = new QLabel(
            QString::fromStdString(traject.getDateTime()), trajectWidget
            );

        QLabel* seatsLabel = new QLabel(
            "Available Seats: " + QString::number(traject.getAvailableSeats()), trajectWidget
            );

        QLabel* priceLabel = new QLabel(
            "Price: " + QString::number(traject.getPrice()) + " MAD", trajectWidget
            );

        QLabel* carLabel = new QLabel(
            "Car Model: " + QString::fromStdString(traject.getCarModel()), trajectWidget
            );

        detailsLayout->addWidget(routeLabel);
        detailsLayout->addWidget(dateTimeLabel);
        detailsLayout->addWidget(seatsLabel);
        detailsLayout->addWidget(priceLabel);
        detailsLayout->addWidget(carLabel);

        // Right: button
        QPushButton* reserveButton = new QPushButton("Reserve", trajectWidget);
        reserveButton->setFixedWidth(100);

        connect(reserveButton, &QPushButton::clicked, this, [=]() {

        });

        hLayout->addLayout(detailsLayout);
        hLayout->addStretch();
        hLayout->addWidget(reserveButton, 0, Qt::AlignVCenter);

        trajectWidget->setLayout(hLayout);
        layout->addWidget(trajectWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}



PassengerShowSearchResult::~PassengerShowSearchResult()
{
    delete ui;
}
