#pragma once

#include <ostream>
#include <string_view>
#include <cstdint>


enum PieceType : uint8_t
{
    Pawn,   // 兵、卒
    Knight, // 馬
    Bishop, // 相、象
    Rook,   // 車
    Cannon, // 炮
    Advisor,// 仕、士
    King,    // 帥、將

    PieceTypeCount = 7
};

enum Piece: uint8_t {
    BlackPawn,
    BlackKnight,
    BlackBishop,
    BlackRook,
    BlackCannon,
    BlackAdvisor,
    BlackKing,
    RedPawn,
    RedKnight,
    RedBishop, // 相
    RedRook,
    RedCannon,
    RedAdvisor,
    RedKing,

    None, // Use in board for empty squares, PieceCount = 14
};

// Returns the PieceType of the given Piece
constexpr inline PieceType GetPieceType(Piece p) { return (PieceType)(p & 0b0111); }

using Square = uint8_t;