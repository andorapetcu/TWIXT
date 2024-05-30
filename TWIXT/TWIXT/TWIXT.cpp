// TWIXT.cpp
#include "TWIXT.h"
#include <QPainter>

TWIXT::TWIXT(QWidget* parent)
    : QMainWindow(parent), currentPlayer(1)
{
    ui.setupUi(this);

    // Set up initial values
    cellSize = 20;  // Adjust the size of each cell
    matrixSize = 24;

    // Initialize the cellStateMatrix with all cells set to 0 (empty)
    cellStateMatrix = QVector<QVector<int>>(matrixSize, QVector<int>(matrixSize, 0));

    // Create play button
    playButton = new QPushButton("Play", this);
    playButton->setGeometry(15, 15, 80, 30);  // Adjust the position and size as needed
    connect(playButton, SIGNAL(clicked()), this, SLOT(onPlayButtonClicked()));

    // Create choose board size button
    chooseSizeButton = new QPushButton("Choose Board Size", this);
    chooseSizeButton->setGeometry(110, 15, 150, 30);  // Adjust the position and size as needed
    connect(chooseSizeButton, SIGNAL(clicked()), this, SLOT(onChooseSizeButtonClicked()));
}

void TWIXT::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int margin = 15;

    int matrixWidth = matrixSize * (cellSize + margin) - margin;
    int matrixHeight = matrixSize * (cellSize + margin) - margin;

    int xStart = (width() - matrixWidth) / 2;
    int yStart = (height() - matrixHeight) / 2;

    // Iterate through the matrix and draw cells with appropriate colors
    for (int row = 0; row < matrixSize; ++row) {
        for (int col = 0; col < matrixSize; ++col) {
            int x = xStart + col * (cellSize + margin);
            int y = yStart + row * (cellSize + margin);

            QRectF cellRect(x, y, cellSize, cellSize);

            // Set the color based on the cell state
            if (cellStateMatrix[row][col] == 1)
                painter.setBrush(Qt::red);
            else if (cellStateMatrix[row][col] == 2)
                painter.setBrush(Qt::black);
            else
                painter.setBrush(Qt::white);

            painter.drawEllipse(cellRect);
        }
    }
}

void TWIXT::onChooseSizeButtonClicked()
{
    bool ok;
    int newSize = QInputDialog::getInt(this, "Choose Board Size", "Enter a size between 6 and 30:", matrixSize, 6, 30, 1, &ok);

    if (ok) {
        // Update the matrix size with the chosen size
        matrixSize = newSize;

        // Initialize the cellStateMatrix with all cells set to 0 (empty)
        cellStateMatrix = QVector<QVector<int>>(matrixSize, QVector<int>(matrixSize, 0));

        // Repaint the widget to reflect the changes
        update();
    }
}

void TWIXT::mousePressEvent(QMouseEvent* event)
{
    int x = event->x();
    int y = event->y();

    int margin = 15;

    int matrixWidth = matrixSize * (cellSize + margin) - margin;
    int matrixHeight = matrixSize * (cellSize + margin) - margin;

    int xStart = (width() - matrixWidth) / 2;
    int yStart = (height() - matrixHeight) / 2;

    // Calculate the cell coordinates based on the mouse click
    int col = (x - xStart) / (cellSize + margin);
    int row = (y - yStart) / (cellSize + margin);

    // Check if the click is within the matrix bounds
    if (row >= 0 && row < matrixSize && col >= 0 && col < matrixSize) {
        // Update the cell state and repaint the widget
        updateCellState(row, col);
        update();
    }
}

void TWIXT::updateCellState(int row, int col)
{
    // Check if the cell is empty
    if (cellStateMatrix[row][col] == 0) {
        // Set the cell color based on the current player
        cellStateMatrix[row][col] = (currentPlayer == 1) ? 1 : 2;

        // Switch to the next player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

void TWIXT::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
}

TWIXT::~TWIXT()
{
}