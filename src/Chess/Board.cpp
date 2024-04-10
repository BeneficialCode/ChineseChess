#include "Board.h"

#include <vector>
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

//各种棋子走法数组
static short KingDir[8] =   {-0x10,		-0x01,	+0x01,	+0x10,	0,		0,		0,		0};     //将
static short AdvisorDir[8]= {-0x11,		-0x0f,	+0x0f,	+0x11,	0,		0,		0,		0};		//士
static short BishopDir[8] = {-0x22,		-0x1e,	+0x1e,	+0x22,	0,		0,		0,		0};	    //象
static short KnightDir[8] = {-0x21,		-0x1f,	-0x12,	-0x0e,	+0x0e,	+0x12,	+0x1f,	+0x21}; //马
static short RookDir[8]   = {-0x01,		+0x01,	-0x10,	+0x10,	0,		0,		0,		0};		//车
static short CannonDir[8] = {-0x01,		+0x01,	-0x10,	+0x10,	0,		0,		0,		0};		//炮
static short PawnDir[2][8]= {
			{-0x01,		+0x01,	-0x10,	0,		0,		0,		0,		0},
			{-0x01,		+0x01,	+0x10,	0,		0,		0,		0,		0}
		};		//兵

// 马腿位置
static short KnightCheck[8] = {-0x10,-0x10,-0x01,+0x01,-0x01,+0x01,+0x10,+0x10};
// 象眼位置
static short BishopCheck[8] = {-0x11,-0x0f,+0x0f,+0x11,0,0,0,0};	
// 双方九宫位置
static short kingpalace[2][9] = {
        {54,55,56,70,71,72,86,87,88},// 对方
        {166,167,168,182,183,184,198,199,200} // 我方
    };

static unsigned char LegalPosition[2][256] ={
	{ // 我方
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 1,25, 1, 9, 1,25, 1, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 0, 0, 0, 0,
		0, 0, 0, 17, 1, 1, 7, 19, 7, 1, 1, 17, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 3, 7, 3, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 17, 7, 3, 7, 17, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // 对方
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 17, 7, 3, 7, 17, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 3, 7, 3, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 17, 1, 1, 7, 19, 7, 1, 1, 17, 0, 0, 0, 0,
		0, 0, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 1,25, 1, 9, 1,25, 1, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}
};

// 将（帅）、士（仕）、象（相）、车（車）、马（馬）、炮、卒（兵）的能到达位置掩码
static unsigned char PositionMask[7] = {2, 4, 16, 1, 1, 1, 8};

void Board::Reset() {
    m_Board = s_StartBoard;
}

std::vector<Move> Board::GetPieceLegalMoves(Square s) const {
    Piece piece = m_Board[s];

    if(piece == INVALID_SQUARE || piece == None)
        return {};

    
    Colour playerColour = GetPieceColour(piece);
    Colour enemyColour = OppositeColour(playerColour);

    // 对方行棋
    if(enemyColour == m_PlayerTurn)
        return {};

    std::vector<Move> moves;

    PieceType type = GetPieceType(piece);
    switch (type)
    {
    case PieceType::King:
        for(int i=0;i<4;i++){
            Square to = s + KingDir[i];
            if(LegalPosition[playerColour][to] & PositionMask[0]){
                if(m_Board[to] == None || GetPieceColour(m_Board[to]) == enemyColour){
                    moves.push_back({s,to,m_Board[to]});
                }
            }
        }
        break;
    case PieceType::Advisor:
        for(int i=0;i<4;i++){
            Square to = s + AdvisorDir[i];
            if(LegalPosition[playerColour][to] & PositionMask[1]){
                if(m_Board[to] == None || GetPieceColour(m_Board[to]) == enemyColour){
                    moves.push_back({s,to,m_Board[to]});
                }
            }
        }
        break;
    case PieceType::Bishop:
        for(int i=0;i<4;i++){
            Square to = s + BishopDir[i];
            if(LegalPosition[playerColour][to] & PositionMask[2]){
                if(m_Board[to] == None || GetPieceColour(m_Board[to]) == enemyColour){
                    if(m_Board[s + BishopCheck[i]] == None){
                        moves.push_back({s,to,m_Board[to]});
                    }
                }
            }
        }
        break;
    case PieceType::Knight:
        for(int i=0;i<8;i++){
            Square to = s + KnightDir[i];
            if(LegalPosition[playerColour][to] & PositionMask[4]){
                if(m_Board[to] == None || GetPieceColour(m_Board[to]) == enemyColour){
                    if(m_Board[s + KnightCheck[i]] == None){
                        moves.push_back({s,to,m_Board[to]});
                    }
                }
            }
        }
        break;
    case PieceType::Rook:
        for(int i=0;i<4;i++){
            Square to = s + RookDir[i];
            while(LegalPosition[playerColour][to] & PositionMask[3]){
                if(m_Board[to] == None){
                    moves.push_back({s,to,m_Board[to]});
                }else{
                    if(GetPieceColour(m_Board[to]) == enemyColour){
                        moves.push_back({s,to,m_Board[to]});
                    }
                    break;
                }
                to += RookDir[i];
            }
        }
        break;
    case PieceType::Cannon:
        for(int i=0;i<4;i++){
            Square to = s + CannonDir[i];
            bool flag = false;
            while(LegalPosition[playerColour][to] & PositionMask[5]){
                if(m_Board[to] == None){
                    if(!flag){
                        moves.push_back({s,to,m_Board[to]});
                    }
                }else{
                    if(!flag){
                        flag = true;
                    }else{
                        if(GetPieceColour(m_Board[to]) == enemyColour){
                            moves.push_back({s,to,m_Board[to]});
                        }
                        break;
                    }
                }
                to += CannonDir[i];
            }
        }
        break;

    case PieceType::Pawn:
        for(int i=0;i<4;i++){
            Square to = s + PawnDir[playerColour][i];
            if(LegalPosition[playerColour][to] & PositionMask[6]){
                if(m_Board[to] == None || GetPieceColour(m_Board[to]) == enemyColour){
                    moves.push_back({s,to,m_Board[to]});
                }
            }
        }
        break;
    default:
        break;
    }

    return std::move(moves);
}