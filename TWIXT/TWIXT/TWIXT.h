// TWIXT.h
#pragma once

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include "ui_TWIXT.h"
#include <QPushButton>
#include <QInputDialog>
#include "Peg.h"  // Include your Peg class header

class TWIXT : public QMainWindow {
    Q_OBJECT

public:
    TWIXT(QWidget* parent = Q_NULLPTR);
    ~TWIXT();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void onChooseSizeButtonClicked();

private:
    int cellSize;
    int matrixSize;
    QPushButton* playButton;
    QPushButton* chooseSizeButton;

    // Matrix to represent the state of each cell (empty, red, black)
    QVector<QVector<int>> cellStateMatrix;

    int currentPlayer;  // 1 for red, 2 for black

    void updateCellState(int row, int col);

    Ui::TWIXTClass ui;
};