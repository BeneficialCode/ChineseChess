#include "Board.h"




#include <sstream>

static constexpr std::array<Piece,256> s_StartBoard = {
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, BlackRook, BlackKnight, BlackBishop, BlackAdvisor, BlackKing, BlackAdvisor, BlackBishop, BlackKnight, BlackRook, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, None, BlackCannon, None, None, None, None, None, BlackCannon, None,  None, None, None, None,
    None, None, None, BlackPawn, None, BlackPawn, None, BlackPawn, None, BlackPawn, None, BlackPawn, None, None, None, None, 
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, RedPawn, None, RedPawn, None, RedPawn, None, RedPawn, None, RedPawn, None, None, None, None, 
    None, None, None, None, RedCannon, None, None, None, None, None, RedCannon, None, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, RedRook, RedKnight, RedBishop, RedAdvisor, RedKing,RedAdvisor , RedBishop, RedKnight, RedRook, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
    None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None,
};

void Board::Reset() {
    m_Board = s_StartBoard;
}