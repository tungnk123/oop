#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define EMPTY                   7
#define DARK                    0
#define LIGHT                   1

#define PAWN                    0
#define BISHOP                  1
#define ELEPHAN                 2
#define KNIGHT                  3
#define CANNON                  4
#define ROOK                    5
#define KING                    6

typedef struct
{
    short   from, dest;
} MOVE, *PMOVE;
typedef struct
{
    short   from, dest;
    int     capture;
} MOVEDATA, *PMOVEDATA;

void gotoxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x, y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void clrscr(void)
{
    CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
    HANDLE  hConsoleOut;
    COORD   Home = { 0, 0 };
    DWORD   dummy;

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

    FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
    csbiInfo.dwCursorPosition.X = 0;
    csbiInfo.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void textcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void textbackground(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void MoveTo(int x, int y)
{
    gotoxy (5*x+1, 2*y+1);
}
void DrawBoard()
{
    textcolor(7);
    textbackground(0);
    clrscr();
    printf("\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    | \\  |  / |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    | /  |  \\ |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    |    |    |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    |    |    |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |                                       |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    |    |    |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    |    |    |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    | \\  |  / |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
    printf(" |    |    |    | /  |  \\ |    |    |    |\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
}
void DrawCell(char color[], char piece[], short pos, BOOL bSelected)
{
    char piece_char[] = "CSTMPXV+";
    if (color[pos] == DARK)
        textcolor(13);
    else if (color[pos] == LIGHT)
        textcolor(14);
    else
        textcolor(7);
    textbackground(bSelected ? 12 : 0);
    MoveTo(pos % 9, pos / 9);
    printf("%c", piece_char[piece[pos]]);
}

void Gen(char Color[], char Piece[], short start[], short end[], char ply, char Side, char xSide, MOVE Gen_dat[])
{
    short Offset[7][8] =
    {
        { -1, 1, 13, 0, 0, 0, 0, 0 },           // PAWN {for DARK side}
        { -12, -14, 12, 14, 0, 0, 0, 0 },           // BISHOP
        { -28, -24, 24, 28, 0, 0, 0, 0 },           // ELEPHAN
        { -11, -15, -25, -27, 11, 15, 25, 27 },         // KNIGHT
        { -1, 1, -13, 13, 0, 0, 0, 0 },         // CANNON
        { -1, 1, -13, 13, 0, 0, 0, 0 },         // ROOK
        { -1, 1, -13, 13, 0, 0, 0, 0 }          // KING
    };
    short Mailbox90[90] =
    {
        28, 29, 30, 31, 32, 33, 34, 35, 36,
        41, 42, 43, 44, 45, 46, 47, 48, 49,
        54, 55, 56, 57, 58, 59, 60, 61, 62,
        67, 68, 69, 70, 71, 72, 73, 74, 75,
        80, 81, 82, 83, 84, 85, 86, 87, 88,
        93, 94, 95, 96, 97, 98, 99, 100, 101,
        106, 107, 108, 109, 110, 111, 112, 113, 114,
        119, 120, 121, 122, 123, 124, 125, 126, 127,
        132, 133, 134, 135, 136, 137, 138, 139, 140,
        145, 146, 147, 148, 149, 150, 151, 152, 153
    };
    short Largebox[182] =
    {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, -1, -1,
        -1, -1, 9, 10, 11, 12, 13, 14, 15, 16, 17, -1, -1,
        -1, -1, 18, 19, 20, 21, 22, 23, 24, 25, 26, -1, -1,
        -1, -1, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1,
        -1, -1, 36, 37, 38, 39, 40, 41, 42, 43, 44, -1, -1,
        -1, -1, 45, 46, 47, 48, 49, 50, 51, 52, 53, -1, -1,
        -1, -1, 54, 55, 56, 57, 58, 59, 60, 61, 62, -1, -1,
        -1, -1, 63, 64, 65, 66, 67, 68, 69, 70, 71, -1, -1,
        -1, -1, 72, 73, 74, 75, 76, 77, 78, 79, 80, -1, -1,
        -1, -1, 81, 82, 83, 84, 85, 86, 87, 88, 89, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
    short Legalposition[90] =
    {
        1, 1, 5, 3, 3, 3, 5, 1, 1,
        1, 1, 1, 3, 3, 3, 1, 1, 1,
        5, 1, 1, 3, 7, 3, 1, 1, 5,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        9, 1, 13, 1, 9, 1, 13, 1, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9
    };
    short   Maskpiece[7] = { 8, 2, 4, 1, 1, 1, 2 };
    short   Knightcheck[8] = { 1, -1, -9, -9, -1, 1, 9, 9 };
    short   Elephancheck[8] = { -10, -8, 8, 10, 0, 0, 0, 0 };
    end[ply] = start[ply];
    for (char i = 0; i < 90; i++)
    if (Color[i]==Side)
    {
        char    p = Piece[i];
        for (char j = 0; j < 8; j++)
        {
            if (!Offset[p][j])
                break;
            short   x = Mailbox90[i];
            char    fcannon = 0;
            char    n;
            if (p == ROOK || p == CANNON)   n = 9;
            else                            n = 1;
            for (char k = 0; k < n; k++)
            {
                if (p == PAWN && Side == LIGHT) x -= Offset[p][j];
                else                            x += Offset[p][j];
                short   y = Largebox[x];
                char    t = ((Side == DARK) ? y : (89 - y));
                if (y == -1 || (Legalposition[t] & Maskpiece[p]) == 0)
                    break;
                if (!fcannon)
                {
                    if (Color[y] != Side)
                    {
                        switch (p)
                        {
                        case KNIGHT:
                            if (Color[i + Knightcheck[j]] == EMPTY)
                            {
                                Gen_dat[end[ply]].from = i;
                                Gen_dat[end[ply]].dest = y;
                                end[ply]++;
                            }
                            break;
                        case ELEPHAN:
                            if (Color[i + Elephancheck[j]] == EMPTY)
                            {
                                Gen_dat[end[ply]].from = i;
                                Gen_dat[end[ply]].dest = y;
                                end[ply]++;
                            }
                            break;
                        case CANNON:
                            if (Color[y] == EMPTY)
                            {
                                Gen_dat[end[ply]].from = i;
                                Gen_dat[end[ply]].dest = y;
                                end[ply]++;
                            }
                            break;
                        default:
                            Gen_dat[end[ply]].from = i;
                            Gen_dat[end[ply]].dest = y;
                            end[ply]++;
                        }
                    }
                    if (Color[y] != EMPTY)
                    {
                        if (p == CANNON)    fcannon++;
                        else                break;
                    }
                }
                else
                {
                    if (Color[y] != EMPTY)
                    {
                        if (Color[y] == xSide)
                        {
                            Gen_dat[end[ply]].from = i;
                            Gen_dat[end[ply]].dest = y;
                            end[ply]++;
                        }
                        break;
                    }
                }
            }
        }
    }
    end[ply + 1] = end[ply];
    start[ply + 1] = end[ply];
}
short AlphaBeta(MOVEDATA MoveData[], MOVE Move[], PMOVE newmove, char color[], char piece[], short start[], short end[], char side, char xside, char Ply, short alpha, short beta, short depth)
{
    static  short   hdp;
    short   value, best;
    if (!depth)
    {
        short   piecevalue[7] = {10, 20, 20, 40, 45, 90, 1000};
        short   iEval = 0;
        for (short i = 0; i < 90; i++)      // EVALUATE
        {
            if (color[i] == side)
                iEval += piecevalue[piece[i]];
            else if (color[i] == xside)
                iEval -= piecevalue[piece[i]];
        }
        return iEval;
    }
    Gen(color, piece, start, end, Ply, side, xside, Move);
    best = -20000;
    for (short i=start[Ply]; i<end[Ply] && best<beta; i++)
    {
        if (best > alpha)
            alpha = best;
        // Thực hiện đi thử
        short from, dest, p;
        from = Move[i].from;
        dest = Move[i].dest;
        MoveData[hdp].dest = Move[i].dest;
        MoveData[hdp].from = Move[i].from;
        MoveData[hdp].capture = p = piece[dest];
        piece[dest] = piece[from];
        piece[from] = EMPTY;
        color[dest] = color[from];
        color[from] = EMPTY;
        hdp++;
        Ply++;
        side = xside;
        xside = 1 - xside;
        if (p == KING)
            value = 1000 - Ply;
        else
            value = -AlphaBeta(MoveData, Move, newmove, color, piece, start, end, side, xside, Ply, -beta, -alpha, depth-1);
        // Hoàn lại nước đi thử
        hdp--;
        Ply--;
        side = xside;
        xside = 1 - xside;
        from = MoveData[hdp].from;
        dest = MoveData[hdp].dest;
        piece[from] = piece[dest];
        color[from] = color[dest];
        piece[dest] = MoveData[hdp].capture;
        if (piece[dest] == EMPTY)
            color[dest] = EMPTY;
        else
            color[dest] = xside;
        // Nếu là nước đi tốt hơn thì nhận dữ liệu nước đi
        if (value > best)
        {
            best = value;
            if (!Ply)
            {
                newmove->dest = Move[i].dest;
                newmove->from = Move[i].from;
            }
        }
    }
    return best;
}
int main()
{
    char color[90] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 0, 7, 7, 7, 7, 7, 0, 7,
        0, 7, 0, 7, 0, 7, 0, 7, 0,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        1, 7, 1, 7, 1, 7, 1, 7, 1,
        7, 1, 7, 7, 7, 7, 7, 1, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    char piece[90] =
    {
        5, 3, 2, 1, 6, 1, 2, 3, 5,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 4, 7, 7, 7, 7, 7, 4, 7,
        0, 7, 0, 7, 0, 7, 0, 7, 0,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        0, 7, 0, 7, 0, 7, 0, 7, 0,
        7, 4, 7, 7, 7, 7, 7, 4, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        5, 3, 2, 1, 6, 1, 2, 3, 5
    };
    short       gen_begin[50] = { 0 };
    short       gen_end[50] = { 0 };
    BOOL        NguoiDiTruoc = TRUE;            // Thay bằng FALSE để cho máy đi trước
    char        side = NguoiDiTruoc ? LIGHT : DARK;
    char        xside = NguoiDiTruoc ? DARK : LIGHT;
    char        computerside = DARK;
    BOOL        bContinue = TRUE;
    POINT       ptCell = { 1, 7 };                      // Vị trí cell của con trỏ chuột
    MOVE        arMove[4096] = { 0 };
    MOVEDATA    MoveData[50] = { 0 };

    DrawBoard();
    for (int i = 0; i < 90; i++)
        DrawCell(color, piece, i, FALSE);
    do
    {
        MOVE        Move = { 0, 0 };
        if (side == computerside)
        {
            AlphaBeta(MoveData, arMove, &Move, color, piece, gen_begin, gen_end, side, xside, 0, -20000, 20000, 4);
        }
        else
        {
            Gen(color, piece, gen_begin, gen_end, 0, side, xside, arMove);
            int         t;
            short           ch, from, selecting = 0;

            while (1)
            {
                MoveTo(ptCell.x, ptCell.y);
                ch = _getch();
                switch (ch)
                {
                case 13:case 32:    // Enter or Spacebar
                    t = ptCell.x + ptCell.y * 9;
                    if (!selecting)                     // Nếu người chơi chưa chọn cell nào
                    {
                        if (color[t] == side)
                        {
                            selecting = 1; from = t; DrawCell(color, piece, t, TRUE);   // Vẽ cell được chọn
                        }
                    }
                    else                                // Người chơi đã chọn 1 cell trước đó
                    {
                        if (t != from)                  // Nếu cell chọn khác với cell đã chọn trước đó
                            DrawCell(color, piece, from, FALSE);        // Chuyển cell chọn trước đó về bình thường
                        if (color[t] == side)               // Nếu cell được chọn là một quân nhà
                        {
                            from = t; DrawCell(color, piece, t, TRUE);                  // Vẽ lại cell chọn mới
                        }
                        else                            // Nếu cell chọn là quân đối phương hoặc cell trống
                        {
                            Move.from = from;
                            Move.dest = t;
                            // Nếu tìm thấy một nước đi có trong danh sách thì trở về để nơi gọi xử lý
                            for (int i = gen_begin[0]; i<gen_end[0]; i++)
                            if (arMove[i].from == Move.from && arMove[i].dest == Move.dest)
                                goto JUMP;
                            DrawCell(color, piece, from, TRUE);                 // Nếu không thì vẽ lại quân chọn từ trước
                        }
                    }
                    break;
                case 27:                                                        return 0;     // ESC
                case 75:    if (ptCell.x) ptCell.x--; else ptCell.x = 8;        break;      // LEFT
                case 77:    if (ptCell.x < 8) ptCell.x++; else ptCell.x = 0;    break;      // RIGHT
                case 72:    if (ptCell.y) ptCell.y--; else ptCell.y = 9;        break;      // UP
                case 80:    if (ptCell.y < 9) ptCell.y++; else ptCell.y = 0;    break;      // DOWN
                }
            }
        }
        JUMP:
        side = xside;
        xside = 1-xside;
        short   p = piece[Move.dest];
        piece[Move.dest] = piece[Move.from];
        piece[Move.from] = EMPTY;
        color[Move.dest] = color[Move.from];
        color[Move.from] = EMPTY;
        DrawCell(color, piece, Move.from, FALSE);
        DrawCell(color, piece, Move.dest, FALSE);
        if(p == KING)
            bContinue = FALSE;
    }
    while(bContinue);
    getchar();
	return 0;
}
