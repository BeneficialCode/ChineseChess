#pragma once

#include <array>
#include <ostream>
#include <string>

#include "Move.h"

class Board {
public:
    Board() { Reset(); }
    Board(const std::string& fen) { FromFEN(fen); }

    void Reset();

    void FromFEN(const std::string& fen);
    std::string ToFEN() const;
    static constexpr std::string_view StartFEN = "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1";

    inline Piece operator[](Square s) const { return m_Board[s]; }

private:

    std::array<Piece, 256> m_Board;
};