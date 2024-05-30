#include"Board.h"
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>  
#include <memory>
using namespace std;

Board::Board(uint16_t size)
{
    m_size = size;

    m_board = new uint16_t * [m_size];

    for (uint16_t i = 0; i < m_size; i++)
    {
        m_board[i] = new uint16_t[m_size];

        for (uint16_t j = 0; j < m_size; j++)
        {
            m_board[i][j] = 0;
        }
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    uint16_t numElementsToSet6 = static_cast<uint16_t>(0.15 * m_size * m_size);

    for (uint16_t k = 0; k < numElementsToSet6; ++k)
    {
        uint16_t randomRow = rand() % m_size;
        uint16_t randomCol = rand() % m_size;

        if (m_board[randomRow][randomCol] != 6)
        {
            m_board[randomRow][randomCol] = 6;
        }
        else
        {
            --k;
        }
    }

    for (uint16_t i = 0; i < 50; ++i)
    {
        m_UnusedBlackPegs.push_back(make_shared<Peg>(-1, -1, 1)); 
        m_UnusedRedPegs.push_back(make_shared<Peg>(-1, -1, 2));
    }

    for (uint16_t i = 0; i < 50; ++i)
    {
        m_UnusedBlackBridges.push_back(make_shared<Bridge>(-1, -1, -1, -1));
        m_UnusedRedBridges.push_back(make_shared<Bridge>(-1, -1, -1, -1));
    }
}



Board::~Board()
{
    for (uint16_t i = 0; i < m_size; i++)
    {
        delete[] m_board[i];
    }
    delete[] m_board;

}


bool Board::NoMorePegs()
{
    auto allPegsUsed = [this]() {
        return m_UnusedRedPegs.empty() && m_UnusedRedBridges.empty() &&
            m_UnusedBlackPegs.empty() && m_UnusedBlackBridges.empty();
        };

    if (allPegsUsed()) {
        cout << "Draw, players have used all of their pegs and bridges!";
        return true;
    }
    else {
        return false;
    }
}



void Board::PrintBoard() const
{
    for (uint16_t line = 0; line < m_size; line++)
    {
        for (uint16_t col = 0; col < m_size; col++)
        {
            std::cout << getElement(line, col) << " ";
        }
        std::cout << std::endl;
    }
}

void Board::setElement(uint16_t line, uint16_t column, uint16_t value)
{
    if (value != 0 && value != 1 && value !=2) //daca nu este piesa rosie sau neagra
    {
        cout << "Value is not valid. It should be 0 or 1";
        return;
    }
    else
    {
        if (line >= 0 && line < m_size && column >= 0 && column < m_size)
        {
            m_board[line][column] = value;
        }
    }
}

uint16_t Board::getElement(uint16_t line, uint16_t column) const
{
    if (line >= 0 && line < m_size && column >= 0 && column < m_size)
    {
        return m_board[line][column];
    }

    return -1;
}

uint16_t** Board::GetBoard() const
{
    return m_board;
}

void Board::PlaceBlackPeg(uint16_t row, uint16_t col)
{
    if ((row < 1 || row >(m_size) - 1) || (col < 0 || col > m_size) || m_board[row][col] != 0 || m_board[row][col] != 6)
    {
        cout << "Invalid data!";
        return;
    }
    else
    {
        if (m_board[row][col] != 6)
        {
            cout << "Placed peg on mine. Lost turn!";
        }
        else
        {

            m_board[row][col] = 1;
            m_UsedBlackPegs.push_back(make_shared<Peg>(row, col, 1));  
            m_UnusedBlackPegs.pop_back();  
        }
    }
}

void Board::PlaceRedPeg(uint16_t row, uint16_t col)
{
    if ((row < 0 || row > m_size) || (col < 1 || col >(m_size - 1)) || m_board[row][col] != 0 || m_board[row][col] != 6)
    {
        cout << "Invalid data!";
        return;
    }
    else
    {
        if (m_board[row][col] != 6)
        {
            cout << "Placed peg on mine. Lost turn!";
        }
        else
        {
            m_board[row][col] = 2;
            m_UsedRedPegs.push_back(make_shared<Peg>(row, col, 2));  
            m_UnusedRedPegs.pop_back();  
        }
    }
}


bool Board::IsPegRed(uint16_t row, uint16_t col) const
{
    if ((row < 0 || row> m_size) || (col < 1 || col>(m_size - 1)))
    {
        cout << "Invalid data!";
        return false; 
    }
    else
    {
        if (m_board[row][col] == 2) //verifica
            return true;
        else
            return false;
    }

}
bool Board::IsPegBlack(uint16_t row, uint16_t col) const
{
    if ((row < 1 || row> 23) || (col < 0 || col> 24))
    {
        cout << "Invalid data!";
        return false;
    }
    else
    {
        if (m_board[row][col] == 1)
            return true;
        else
            return false;
    }
}


void Board::RemoveRedPeg(uint16_t row, uint16_t col)
{
    if (row >= 0 && row < m_size && col >= 0 && col < m_size)
    {
        m_board[row][col] = 0;
        std::cout << "Peg removed at row " << row << ", column " << col << std::endl;
        m_UnusedRedPegs.push_back(make_shared<Peg>(-1, -1, 2)); // daca scoatem peg ul de pe tabla il punem in vectorul de Unused red pegs
    }
    else
    {
        std::cout << "Invalid position for peg removal!" << std::endl;
    }
}

void Board::RemoveBlackPeg(uint16_t row, uint16_t col)
{
    if (row >= 0 && row < m_size && col >= 0 && col < m_size)
    {
        m_board[row][col] = 0;
        std::cout << "Peg removed at row " << row << ", column " << col << std::endl;
        m_UnusedBlackPegs.push_back(make_shared<Peg>(-1, -1, 1)); // daca scoatem peg ul de pe tabla il punem in vectorul de Unused black pegs
    }
    else
    {
        std::cout << "Invalid position for peg removal!" << std::endl;
    }
}

//.........................Functii pentru verificare daca un Bridge poate fi plasat pe Board.............................


// 1................ 

// Verificare daca pot pune un Bridge Negru pe board (Both Pegs must be black! )
bool Board::BlackPegsForBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    if (Board::IsPegBlack(row1, col1) && Board::IsPegBlack(row2, col2))
        return true;
    return false;
}

//Verificare daca pot pune un Bridge Rosu pe board(Both Pegs must be red!)

bool Board::RedPegsForBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    if (Board::IsPegRed(row1, col1) && Board::IsPegRed(row2, col2))
        return true;
    return false;
}

//2.....................

// verifica daca bridge-ul e diagonala unui dreptunghi de 2x3
bool Board::CanPlaceBlackBridge_2x3Rectangle(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{

    if ((abs(row1 - row2) == 1 && abs(col1 - col2) == 2) || (abs(row1 - row2) == 2 && abs(col1 - col2) == 1))
        return true;

    return false;
}


//verifica daca bridge - ul e diagonala unui dreptunghi de 2x3
bool Board::CanPlaceRedBridge_2x3Rectangle(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{

    if ((abs(row1 - row2) == 1 && abs(col1 - col2) == 2) || (abs(row1 - row2) == 2 && abs(col1 - col2) == 1))
        return true;

    return false;
}

// 3...........

// verifica daca pozitiile de start(Peg1) si end()Peg2 ale bridge ului sunt valide
bool Board::ValidPositionsForBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    // Check if positions are within bounds
    if (row1 < 0 || row1 >= m_size || col1 < 0 || col1 >= m_size ||
        row2 < 0 || row2 >= m_size || col2 < 0 || col2 >= m_size) {
        cout << "Invalid positions!";
        return false;
    }
}

// 4.....................

// verifica daca exista un alt bridge la pozitia specificata 
// BLACK
bool Board::IsAnotherBlackBridgeAtPosition(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    if (!ValidPositionsForBridge(row1, col1, row2, col2)) {
        return false;
    }

    for (const auto bridge : m_UsedBlackBridges)
    {
        uint16_t bridgeRow1 = bridge->GetLine1();
        uint16_t bridgeCol1 = bridge->GetLine2();
        uint16_t bridgeRow2 = bridge->GetColumn1();
        uint16_t bridgeCol2 = bridge->GetColumn2();
        if ((row1 == bridgeRow1 && col1 == bridgeCol1 && row2 == bridgeRow2 && col2 == bridgeCol2) ||
            (row1 == bridgeRow2 && col1 == bridgeCol2 && row2 == bridgeRow1 && col2 == bridgeCol1)) {
            cout << "Another black bridge already exists at the specified position!";
            return true;
        }
    }

    return false;
}

bool Board::IsAnotherRedBridgeAtPosition(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    if (!ValidPositionsForBridge(row1, col1, row2, col2)) {
        return false;
    }

    for (const auto bridge : m_UsedRedBridges) {
        uint16_t bridgeRow1 = bridge->GetLine1();
        uint16_t bridgeCol1 = bridge->GetLine2();
        uint16_t bridgeRow2 = bridge->GetColumn1();
        uint16_t bridgeCol2 = bridge->GetColumn2();

        if ((row1 == bridgeRow1 && col1 == bridgeCol1 && row2 == bridgeRow2 && col2 == bridgeCol2) ||
            (row1 == bridgeRow2 && col1 == bridgeCol2 && row2 == bridgeRow1 && col2 == bridgeCol1)) {
            cout << "Another red bridge already exists at the specified position!";
            return true;
        }
    }

    return false;
}

// 5.....................

// verifica daca mai exista  bridges nefolosite in vectori
//BLACK
bool Board::AnyUnusedBlackBridgesLeft() const
{
    if (!m_UnusedBlackBridges.empty()) {
        return true;
    }
    else {
        return false;
    }
}

bool Board::AnyUnusedRedBridgesLeft() const
{
    if (!m_UnusedRedBridges.empty()) {
        return true;
    }
    else {
        return false;
    }
}
// 6......................................

// verifica daca un bridge pus pe board intersecteaza un alt bridge existent pe board
bool Board::IsBridgeCrossingOtherBridges(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    // Check if the new Bridge crosses any existing bridges
    for (const auto& bridgePtr : m_UsedBlackBridges)
    {
        if (Intersects(bridgePtr, row1, col1, row2, col2))
        {
            cout << "new Bridge crosses an existing black bridge!";
            return true;
        }
    }
    for (const auto& bridgePtr : m_UsedRedBridges)
    {
        if (Intersects(bridgePtr, row1, col1, row2, col2))
        {
            cout << "new Bridge crosses an existing red bridge!";
            return true;
        }
    }

    return false;
}

bool Board::Intersects(const std::shared_ptr<Bridge>& bridge, uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2) const
{


    uint16_t vec1X = bridge->GetLine1() - bridge->GetLine2();
    uint16_t vec1Y = bridge->GetColumn1() - bridge->GetColumn2();
    uint16_t vec2X = row1 - row2;
    uint16_t vec2Y = col1 - col2;

    uint16_t det = vec1X * vec2Y - vec1Y * vec2X;


    if (det == 0)
    {
        if ((bridge->GetLine1() - row2) * (bridge->GetColumn1() - col2) == (bridge->GetLine2() - row2) * (bridge->GetColumn2() - col2) &&
            (bridge->GetLine1() - row1) * (bridge->GetColumn1() - col1) == (bridge->GetLine2() - row1) * (bridge->GetColumn2() - col1))
        {
            if (std::max(bridge->GetLine1(), bridge->GetLine2()) >= std::min(row1, row2) &&
                std::max(row1, row2) >= std::min(bridge->GetLine1(), bridge->GetLine2()) &&
                std::max(bridge->GetColumn1(), bridge->GetColumn2()) >= std::min(col1, col2) &&
                std::max(col1, col2) >= std::min(bridge->GetColumn1(), bridge->GetColumn2()))
            {
                cout << "Bridges overlap or share endpoints!";
                return true;
            }
        }
    }


    else
    {
        double t = static_cast<double>((vec2Y * (bridge->GetLine1() - row1) + vec2X * (col1 - bridge->GetColumn1()))) / det;
        double u = static_cast<double>((vec1Y * (bridge->GetLine1() - row1) + vec1X * (col1 - bridge->GetColumn1()))) / det;

        if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
        {
            cout << "Bridges intersect!";
            return true;
        }
    }

    return false;
}


bool Board::CanPlaceRedBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    auto invalidPegColors = [this]() {
        cout << "Invalid peg colors for a red bridge!";
        return false;
        };

    auto notDiagonalTo2x3Rectangle = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "Red bridge is not diagonal to a 2x3 rectangle!";
        return false;
        };

    auto positionsNotValid = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "Invalid positions!";
        return false;
        };

    auto anotherRedBridgeExists = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "Another red bridge already exists at the specified position!";
        return true;
        };

    auto intersectsOtherBridges = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "New bridge crosses an existing red bridge!";
        return true;
        };

    auto noUnusedRedBridgesLeft = [this]() {
        cout << "No unused red bridges left!";
        return false;
        };

    if (!RedPegsForBridge(row1, col1, row2, col2)) return invalidPegColors();
    if (!CanPlaceRedBridge_2x3Rectangle(row1, col1, row2, col2)) return notDiagonalTo2x3Rectangle(row1, col1, row2, col2);
    if (!ValidPositionsForBridge(row1, col1, row2, col2)) return positionsNotValid(row1, col1, row2, col2);
    if (IsAnotherRedBridgeAtPosition(row1, col1, row2, col2)) return anotherRedBridgeExists(row1, col1, row2, col2);
    if (IsBridgeCrossingOtherBridges(row1, col1, row2, col2)) return intersectsOtherBridges(row1, col1, row2, col2);
    if (!AnyUnusedRedBridgesLeft()) return noUnusedRedBridgesLeft();

    return true;
}

bool Board::CanPlaceBlackBridge(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2)
{
    auto invalidPegColors = [this]() {
        cout << "Invalid peg colors for a red bridge!";
        return false;
        };

    auto notDiagonalTo2x3Rectangle = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "Red bridge is not diagonal to a 2x3 rectangle!";
        return false;
        };

    auto positionsNotValid = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "Invalid positions!";
        return false;
        };

    auto anotherBlackBridgeExists = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "Another red bridge already exists at the specified position!";
        return true;
        };

    auto intersectsOtherBridges = [this](uint16_t r1, uint16_t c1, uint16_t r2, uint16_t c2) {
        cout << "New bridge crosses an existing red bridge!";
        return true;
        };

    auto noUnusedBlackBridgesLeft = [this]() {
        cout << "No unused red bridges left!";
        return false;
        };

    if (!BlackPegsForBridge(row1, col1, row2, col2)) return invalidPegColors();
    if (!CanPlaceBlackBridge_2x3Rectangle(row1, col1, row2, col2)) return notDiagonalTo2x3Rectangle(row1, col1, row2, col2);
    if (!ValidPositionsForBridge(row1, col1, row2, col2)) return positionsNotValid(row1, col1, row2, col2);
    if (IsAnotherBlackBridgeAtPosition(row1, col1, row2, col2)) return anotherBlackBridgeExists(row1, col1, row2, col2);
    if (IsBridgeCrossingOtherBridges(row1, col1, row2, col2)) return intersectsOtherBridges(row1, col1, row2, col2);
    if (!AnyUnusedBlackBridgesLeft()) return noUnusedBlackBridgesLeft();

    return true;
}

void Board::PlaceRedBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol)
{
    if (CanPlaceRedBridge(startRow, startCol, endRow, endCol) == true)
    {
        m_UsedRedBridges.push_back((make_shared<Bridge>(startRow, startCol, endRow, endCol)));

        m_board[startRow][startCol] = 2;
        m_board[endRow][endCol] = 2;
    }
    else
    {
        cout << "Cannot place red bridge!" << endl;
    }
}

void Board::PlaceBlackBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol)
{
    if (CanPlaceBlackBridge(startRow, startCol, endRow, endCol))
    {
        m_UsedBlackBridges.push_back(make_shared<Bridge>(startRow, startCol, endRow, endCol));

        m_board[startRow][startCol] = 1;
        m_board[endRow][endCol] = 1;
    }
    else
    {
        cout << "Cannot place black bridge!" << endl;
    }
}

void Board::Bulldozer()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    uint16_t coin = rand() % 2;

    // Randomly select a position on the board
    uint16_t randomRow = rand() % m_size;
    uint16_t randomCol = rand() % m_size;

    if (coin == 0)
    {
        if (m_board[randomRow][randomCol] == 1 || m_board[randomRow][randomCol] == 2)
        {
            DestroyPegAndBridges(randomRow, randomCol);
            std::cout << "Bulldozer destroyed a peg and connected bridges at row " << randomRow << ", column " << randomCol << std::endl;
        }
    }
    else
    {
        if (m_board[randomRow][randomCol] == 0)
        {
            m_board[randomRow][randomCol] = 4; 
            std::cout << "Bulldozer filled an empty spot at row " << randomRow << ", column " << randomCol << std::endl;
        }
    }
}

bool Board::IsBridgeAtPosition(uint16_t row1, uint16_t col1, uint16_t row2, uint16_t col2) const
{
    for (const auto& bridgePtr : m_UsedBlackBridges) {
        uint16_t bridgeRow1 = bridgePtr->GetLine1();
        uint16_t bridgeCol1 = bridgePtr->GetLine2();
        uint16_t bridgeRow2 = bridgePtr->GetColumn1();
        uint16_t bridgeCol2 = bridgePtr->GetColumn2();

        if ((row1 == bridgeRow1 && col1 == bridgeCol1 && row2 == bridgeRow2 && col2 == bridgeCol2) ||
            (row1 == bridgeRow2 && col1 == bridgeCol2 && row2 == bridgeRow1 && col2 == bridgeCol1)) {
            return true;
        }
    }

    for (const auto& bridgePtr : m_UsedRedBridges) {
        uint16_t bridgeRow1 = bridgePtr->GetLine1();
        uint16_t bridgeCol1 = bridgePtr->GetLine2();
        uint16_t bridgeRow2 = bridgePtr->GetColumn1();
        uint16_t bridgeCol2 = bridgePtr->GetColumn2();

        if ((row1 == bridgeRow1 && col1 == bridgeCol1 && row2 == bridgeRow2 && col2 == bridgeCol2) ||
            (row1 == bridgeRow2 && col1 == bridgeCol2 && row2 == bridgeRow1 && col2 == bridgeCol1)) {
            return true;
        }
    }

    return false;
}


void Board::DeleteRedPeg(uint16_t row, uint16_t col)
{
    if (row >= 0 && row < m_size && col >= 0 && col < m_size)
    {
        if (m_board[row][col] == 2)
        {
            m_board[row][col] = 0;
            cout << "Red Peg deleted at row " << row << ", column " << col << endl;
            m_UnusedRedPegs.push_back(make_shared<Peg>(-1, -1, 2)); // Add the peg back to the unused red pegs
        }
        else
        {
            cout << "No red peg at the specified position!" << endl;
        }
    }
    else
    {
        cout << "Invalid position for peg deletion!" << endl;
    }
}

void Board::DeleteBlackPeg(uint16_t row, uint16_t col)
{
    if (row >= 0 && row < m_size && col >= 0 && col < m_size)
    {
        if (m_board[row][col] == 1)
        {
            m_board[row][col] = 0;
            cout << "Black Peg deleted at row " << row << ", column " << col << endl;
            m_UnusedBlackPegs.push_back(make_shared<Peg>(-1, -1, 1)); // Add the peg back to the unused black pegs
        }
        else
        {
            cout << "No black peg at the specified position!" << endl;
        }
    }
    else
    {
        cout << "Invalid position for peg deletion!" << endl;
    }
}

void Board::DeleteRedBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol)
{
    auto it = std::remove_if(m_UsedRedBridges.begin(), m_UsedRedBridges.end(),
        [=](const std::shared_ptr<Bridge>& bridge)
        {
            return (bridge->GetLine1() == startRow && bridge->GetLine2() == startCol &&
                bridge->GetColumn1() == endRow && bridge->GetColumn2() == endCol) ||
                (bridge->GetLine1() == endRow && bridge->GetLine2() == endCol &&
                    bridge->GetColumn1() == startRow && bridge->GetColumn2() == startCol);
        });

    if (it != m_UsedRedBridges.end())
    {
        m_UsedRedBridges.erase(it, m_UsedRedBridges.end());

        m_board[startRow][startCol] = 0;
        m_board[endRow][endCol] = 0;

        cout << "Red bridge deleted successfully!" << endl;
    }
    else
    {
        cout << "Red bridge not found on the board!" << endl;
    }
}


void Board::DeleteBlackBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol)
{
    auto it = std::remove_if(m_UsedBlackBridges.begin(), m_UsedBlackBridges.end(),
        [=](const std::shared_ptr<Bridge>& bridge)
        {
            return (bridge->GetLine1() == startRow && bridge->GetLine2() == startCol &&
                bridge->GetColumn1() == endRow && bridge->GetColumn2() == endCol) ||
                (bridge->GetLine1() == endRow && bridge->GetLine2() == endCol &&
                    bridge->GetColumn1() == startRow && bridge->GetColumn2() == startCol);
        });

    if (it != m_UsedBlackBridges.end())
    {
        m_UsedBlackBridges.erase(it, m_UsedBlackBridges.end());

        m_board[startRow][startCol] = 0;
        m_board[endRow][endCol] = 0;

        cout << "Black bridge deleted successfully!" << endl;
    }
    else
    {
        cout << "Black bridge not found on the board!" << endl;
    }
}


bool Board::CheckWinner() const
{
    for (uint16_t col = 0; col < m_size; ++col)
    {
        if (IsPegRed(0, col))
        {
            if (ConnectedToLastRow(0, col, 2))
            {
                cout << "Red player wins! Connected bridges from top to bottom." << endl;
                return true;
            }
        }
    }

    for (uint16_t row = 0; row < m_size; ++row)
    {
        if (IsPegBlack(row, 0))
        {
            if (ConnectedToLastColumn(row, 0, 1))
            {
                cout << "Black player wins! Connected bridges from left to right." << endl;
                return true;
            }
        }
    }

    return false; 
}

bool Board::ConnectedToLastRow(uint16_t row, uint16_t col, uint16_t pegColor) const
{
    // a juns la ultimul rand
    if (row == m_size - 1)
    {
        return true;
    }

    m_board[row][col] = 3; 

    if (row > 0 && m_board[row - 1][col] == pegColor && m_board[row - 1][col] != 3)
    {
        if (ConnectedToLastRow(row - 1, col, pegColor))
        {
            return true;
        }
    }
    if (row < m_size - 1 && m_board[row + 1][col] == pegColor && m_board[row + 1][col] != 3)
    {
        if (ConnectedToLastRow(row + 1, col, pegColor))
        {
            return true;
        }
    }
    if (col > 0 && m_board[row][col - 1] == pegColor && m_board[row][col - 1] != 3)
    {
        if (ConnectedToLastRow(row, col - 1, pegColor))
        {
            return true;
        }
    }
    if (col < m_size - 1 && m_board[row][col + 1] == pegColor && m_board[row][col + 1] != 3)
    {
        if (ConnectedToLastRow(row, col + 1, pegColor))
        {
            return true;
        }
    }

    return false; 
}

bool Board::ConnectedToLastColumn(uint16_t row, uint16_t col, uint16_t pegColor) const
{
    //a ajuns la ultima coloana
    if (col == m_size - 1)
    {
        return true;
    }

    m_board[row][col] = 3; 

    if (row > 0 && m_board[row - 1][col] == pegColor && m_board[row - 1][col] != 3)
    {
        if (ConnectedToLastColumn(row - 1, col, pegColor))
        {
            return true;
        }
    }
    if (row < m_size - 1 && m_board[row + 1][col] == pegColor && m_board[row + 1][col] != 3)
    {
        if (ConnectedToLastColumn(row + 1, col, pegColor))
        {
            return true;
        }
    }
    if (col > 0 && m_board[row][col - 1] == pegColor && m_board[row][col - 1] != 3)
    {
        if (ConnectedToLastColumn(row, col - 1, pegColor))
        {
            return true;
        }
    }
    if (col < m_size - 1 && m_board[row][col + 1] == pegColor && m_board[row][col + 1] != 3)
    {
        if (ConnectedToLastColumn(row, col + 1, pegColor))
        {
            return true;
        }
    }

    return false; 
}



void Board::DestroyPegAndBridges(uint16_t row, uint16_t col)
{
    // Destroy the peg
    m_board[row][col] = 4; // Bulldozer number

    // Destroy connected bridges
    /*for (auto it = m_UsedBlackBridges.begin(); it != m_UsedBlackBridges.end();)
    {
        if ((*it)->GetLine1() == row && (*it)->GetColumn1() == col)
        {
            delete* it;
            it = m_UsedBlackBridges.erase(it);
        }
        else if ((*it)->GetLine2() == row && (*it)->GetColumn2() == col)
        {
            delete* it;
            it = m_UsedBlackBridges.erase(it);
        }
        else
        {
            ++it;
        }

    }*/

   /* for (auto it = m_UsedRedBridges.begin(); it != m_UsedRedBridges.end();)
    {
        if ((*it)->GetLine1() == row && (*it)->GetColumn1() == col)
        {
            delete* it;
            it = m_UsedRedBridges.erase(it);
        }
        else if ((*it)->GetLine2() == row && (*it)->GetColumn2() == col)
        {
            delete* it;
            it = m_UsedRedBridges.erase(it);
        }
        else
        {
            ++it;
        }
    }*/
}

//
//
//bool Board::IsDraw() const
//{
//    // Check if both players used all their black bridges and pegs
//    if (m_UnusedBlackBridges.empty() && m_UnusedBlackPegs.empty()) {
//        cout << "Player with black pieces used all bridges and pegs." << endl;
//    }
//
//    // Check if both players used all their red bridges and pegs
//    if (m_UnusedRedBridges.empty() && m_UnusedRedPegs.empty()) {
//        cout << "Player with red pieces used all bridges and pegs." << endl;
//    }
//    // If both players used all their bridges and pegs, it's a draw
//    if (m_UnusedBlackBridges.empty() && m_UnusedBlackPegs.empty() &&
//        m_UnusedRedBridges.empty() && m_UnusedRedPegs.empty()) {
//        cout << "The game is a draw!" << endl;
//        return true;
//    }
//
//    return false;
//}
//
//
//void Board::DisplayBlackPlayerInfo() const
//{
//    cout << "Black Player Information:" << endl;
//    cout << "Unused Black Pegs: " << m_UnusedBlackPegs.size() << endl;
//    cout << "Used Black Pegs: " << m_UsedBlackPegs.size() << endl;
//    cout << "Unused Black Bridges: " << m_UnusedBlackBridges.size() << endl;
//    cout << "Used Black Bridges: " << m_UsedBlackBridges.size() << endl;
//}
//
//bool Board::CheckForWinner(uint16_t player)
//{
//    // Check if the player has connected two opposite sides horizontally
//    if (player == 1) {
//        // Check if the black player has connected the left and right sides
//        for (uint16_t row = 1; row < m_size - 1; ++row) {
//            if (m_board[row][0] == 1 && m_board[row][m_size - 1] == 1) {
//                cout << "Black player wins!" << endl;
//                return true;
//            }
//        }
//    }
//    else if (player == 2) {
//        // Check if the red player has connected the top and bottom sides
//        for (uint16_t col = 1; col < m_size - 1; ++col) {
//            if (m_board[0][col] == 2 && m_board[m_size - 1][col] == 2) {
//                cout << "Red player wins!" << endl;
//                return true;
//            }
//        }
//    }
//
//    return false;
//}
//
//void Board::RemoveRedBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol)
//{
//    // Find the bridge in the used red bridges vector
//    auto redBridgeIter = std::find_if(m_UsedRedBridges.begin(), m_UsedRedBridges.end(),
//        [=](const Bridge* bridge)
//        {
//            return (bridge->GetLine1() == startRow && bridge->GetLine2() == startCol &&
//                bridge->GetColumn1() == endRow && bridge->GetColumn2() == endCol) ||
//                (bridge->GetLine1() == endRow && bridge->GetLine2() == endCol &&
//                    bridge->GetColumn1() == startRow && bridge->GetColumn2() == startCol);
//        });
//    if (redBridgeIter != m_UsedRedBridges.end()) {
//        delete* redBridgeIter;
//        m_UsedRedBridges.erase(redBridgeIter);
//        // Clear the cells occupied by the red bridge
//        m_board[startRow][startCol] = 0;
//        m_board[endRow][endCol] = 0;
//        cout << "Red bridge removed successfully!" << endl;
//    }
//    else {
//        cout << "Red bridge not found on the board!" << endl;
//    }
//}
//void Board::RemoveBlackBridge(uint16_t startRow, uint16_t startCol, uint16_t endRow, uint16_t endCol)
//{
//    // Find the bridge in the used black bridges vector
//    auto blackBridgeIter = std::find_if(m_UsedBlackBridges.begin(), m_UsedBlackBridges.end(),
//        [=](const Bridge* bridge)
//        {
//            return (bridge->GetLine1() == startRow && bridge->GetLine2() == startCol &&
//                bridge->GetColumn1() == endRow && bridge->GetColumn2() == endCol) ||
//                (bridge->GetLine1() == endRow && bridge->GetLine2() == endCol &&
//                    bridge->GetColumn1() == startRow && bridge->GetColumn2() == startCol);
//        });
//    if (blackBridgeIter != m_UsedBlackBridges.end()) {
//        delete* blackBridgeIter;
//        m_UsedBlackBridges.erase(blackBridgeIter);
//        // Clear the cells occupied by the black bridge
//        m_board[startRow][startCol] = 0;
//        m_board[endRow][endCol] = 0;
//        cout << "Black bridge removed successfully!" << endl;
//    }
//    else {
//        cout << "Black bridge not found on the board!" << endl;
//    }
//}