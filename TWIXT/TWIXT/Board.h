#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "Bridge.h"
#include <memory>
#include "Peg.h"


class Board
{

public:
    Board(uint16_t size);
    ~Board();
    uint16_t getElement(uint16_t line, uint16_t column) const;
    void setElement(uint16_t line, uint16_t column, uint16_t value);
    void PrintBoard() const;
    uint16_t** GetBoard() const;

    void PlaceRedPeg(uint16_t row, uint16_t col);
    void PlaceBlackPeg(uint16_t row, uint16_t col);
    bool IsPegBlack(uint16_t row, uint16_t col) const;
    bool IsPegRed(uint16_t row, uint16_t col) const;
    bool BlackPegsForBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool RedPegsForBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    void RemoveRedPeg(uint16_t row, uint16_t col);
    void RemoveBlackPeg(uint16_t row, uint16_t col);
    bool CanPlaceBlackBridge_2x3Rectangle(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool CanPlaceRedBridge_2x3Rectangle(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool ValidPositionsForBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool IsAnotherBlackBridgeAtPosition(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool IsAnotherRedBridgeAtPosition(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool AnyUnusedBlackBridgesLeft() const;
    bool AnyUnusedRedBridgesLeft() const;
    bool IsBridgeCrossingOtherBridges(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool Intersects(const std::shared_ptr<Bridge>& bridge, uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2) const;
    void PlaceRedBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol);
    void PlaceBlackBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol);
    bool NoMorePegs();
    bool CanPlaceRedBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool CanPlaceBlackBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
    bool IsBridgeAtPosition(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2) const;
    void DeleteBlackBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol);
    void DeleteRedBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol);

    void DeleteBlackPeg(uint16_t row, uint16_t col);
    void DeleteRedPeg(uint16_t row, uint16_t col);
    bool CheckWinner() const;
    bool ConnectedToLastRow(uint16_t row, uint16_t col, uint16_t pegColor) const;
    bool ConnectedToLastColumn(uint16_t row, uint16_t col, uint16_t pegColor) const;

    void Bulldozer();
    void DestroyPegAndBridges(uint16_t row, uint16_t col);
    //  void CreateBridge(uint16_t line1, uint16_t col1, uint16_t line2, uint16_t col2) override;
     // void PlaceRedBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2);
     // bool FindBridge1(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2, uint16_t offset);
     // bool FindBridge2(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2, uint16_t offset);

private:

    uint16_t** m_board;
    uint16_t m_size;

    //std::vector<Peg*> m_UsedBlackPegs;    // piloni black folositi
    //std::vector<Peg*> m_UnusedBlackPegs;  // piloni black nefolositi (50 la inceput, se tot scot pe rand piloni) 

    //std::vector<Peg*> m_UsedRedPegs;      // piloni red folositi
    //std::vector<Peg*> m_UnusedRedPegs;    // piloni red nefolositi  (50 la inceput, se tot scot pe rand piloni) 

    //std::vector<Bridge*> m_UsedBlackBridges;
    //std::vector<Bridge*> m_UnusedBlackBridges; //(50 la inceput, se tot scot pe rand bridges)

    //std::vector<Bridge*> m_UnusedRedBridges; //(50 la inceput, se tot scot pe rand bridges)
    //std::vector<Bridge*> m_UsedRedBridges;

    std::vector<std::shared_ptr<Peg>> m_UsedBlackPegs;
    std::vector<std::shared_ptr<Peg>> m_UnusedBlackPegs;

    std::vector<std::shared_ptr<Peg>> m_UsedRedPegs;
    std::vector<std::shared_ptr<Peg>> m_UnusedRedPegs;

    std::vector<std::shared_ptr<Bridge>> m_UsedBlackBridges;
    std::vector<std::shared_ptr<Bridge>> m_UnusedBlackBridges;

    std::vector<std::shared_ptr<Bridge>> m_UnusedRedBridges;
    std::vector<std::shared_ptr<Bridge>> m_UsedRedBridges;
};