#pragma once

#include <ostream>
#include <string_view>
#include <cstdint>

enum Colour : uint8_t {
    Red,
    Black,
    ColourCount = 2
};

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
    RedPawn,
    RedKnight,
    RedBishop, // 相
    RedRook,
    RedCannon,
    RedAdvisor,
    RedKing,
    BlackPawn = 8,
    BlackKnight,
    BlackBishop,
    BlackRook,
    BlackCannon,
    BlackAdvisor,
    BlackKing,

    None, // Use in board for empty squares
};

// Returns the PieceType of the given Piece
constexpr inline PieceType GetPieceType(Piece p) { return (PieceType)(p & 0b0111); }

// Returns the Colour of the given Piece
constexpr inline Colour GetPieceColour(Piece p) { return (Colour)((p & 0b1000) >> 3); }

// Returns the opposite Colour of the given Colour
constexpr inline Colour OppositeColour(Colour c) { return (Colour)(1 - c); }

// Returns the Piece of the given PieceType and Colour
constexpr inline Piece MakePiece(PieceType pt, Colour c) { return (Piece)(pt | (c << 3)); }

inline char PieceToChar(Piece p) {
    switch (p) {
        case RedPawn: return 'P';
        case RedKnight: return 'N';
        case RedBishop: return 'B';
        case RedRook: return 'R';
        case RedCannon: return 'C';
        case RedAdvisor: return 'A';
        case RedKing: return 'K';
        case BlackPawn: return 'p';
        case BlackKnight: return 'n';
        case BlackBishop: return 'b';
        case BlackRook: return 'r';
        case BlackCannon: return 'c';
        case BlackAdvisor: return 'a';
        case BlackKing: return 'k';
    }
}

inline PieceType CharToPieceType(char c) {
    char piece = std::tolower(c);
    switch (piece) {
        case 'p': return Pawn;
        case 'n': return Knight;
        case 'b': return Bishop;
        case 'r': return Rook;
        case 'c': return Cannon;
        case 'a': return Advisor;
        case 'k': return King;
    }
}



using Square = uint8_t;

enum SquareValues : Square {
    INVALID_SQUARE = 0xFF,
};



inline constexpr Square ToSquare(float file,float rank) {
    Square square = 51 + (uint8_t)rank * 16 + (uint8_t)file;
    return square;
}

inline constexpr Square RankOf(Square s) {
    return s / 16;
}

inline constexpr Square FileOf(Square s) {
    return s % 16;
}