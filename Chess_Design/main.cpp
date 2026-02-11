#include <bits/stdc++.h>
using namespace std;

enum Color
{
    WHITE,
    BLACK
};

enum PieceType
{
    KING,
    QUEEN,
    KNIGHT,
    BISHOP,
    ROOK,
    PAWN
};

enum GameStatus
{
    WAITING,
    INPROGRESS,
    COMPLETED,
    ABORTED
};

class Board;
class Piece;
class Match;
class User;

class Position
{
    int row, col;

public:
    Position()
    {
        row = 0;
        col = 0;
    }

    Position(int r, int c)
    {
        row = r;
        col = c;
    }

    int getRow()
    {
        return row;
    }

    int getCol()
    {
        return col;
    }

    bool isValid()
    {
        if (row < 0 || row >= 8 || col < 0 || col >= 8)
        {
            return false;
        }
        return true;
    }

    bool operator==(const Position &other) const
    {
        return (row == other.row && col == other.col);
    }
    bool operator<(const Position &otherPosition)
    {
        if (row != otherPosition.row)
            return row < otherPosition.row;

        return col < otherPosition.col;
    }

    string toString()
    {
        return "(" + to_string(row) + "," + to_string(col) + ")";
    }

    string toChessNotation()
    {
        char file = 'a' + col;
        char rank = '8' - row;
        return string(1, file) + string(1, rank);
    }
};

class Move
{
private:
    Position from;
    Position to;
    Piece *piece;
    Piece *capturedPiece;

public:
    Move()
    {
        piece = nullptr;
        capturedPiece = nullptr;
    }

    Move(Position from, Position to, Piece *piece, Piece *capturedPiece)
    {
        this->from = from;
        this->to = to;
        this->piece = piece;
        this->capturedPiece = capturedPiece;
    }

    Position getFrom()
    {
        return from;
    }

    Position getTo()
    {
        return to;
    }

    Piece *getPiece()
    {
        return piece;
    }

    Piece *getCapturedPiece()
    {
        return capturedPiece;
    }
};

class Piece
{
protected:
    Color color;
    PieceType type;
    bool hasMoved;

public:
    Piece(Color color, PieceType type)
    {
        this->color = color;
        this->type = type;
        hasMoved = false;
    }

    virtual ~Piece() = default;

    Color getColor() { return color; }
    PieceType getPieceType() { return type; }
    bool getHasMoved() { return hasMoved; }
    void setMoved(bool moved) { hasMoved = moved; }

    virtual vector<Position> getPossiblePositions(Position pos, Board *board) = 0;
    virtual string getSymbol() = 0;

    string toString()
    {
        string col = color == WHITE ? "W" : "B";
        return col + getSymbol();
    }
};

class King : public Piece
{
public:
    King(Color color) : Piece(color, KING) {}
    vector<Position> getPossiblePositions(Position pos, Board *board) override;
    string getSymbol() override
    {
        return "K";
    }
};

class Queen : public Piece
{
public:
    Queen(Color color) : Piece(color, QUEEN) {}
    vector<Position> getPossiblePositions(Position pos, Board *board) override;
    string getSymbol() override
    {
        return "Q";
    }
};

class Rook : public Piece
{
public:
    Rook(Color color) : Piece(color, ROOK) {}
    vector<Position> getPossiblePositions(Position pos, Board *board) override;
    string getSymbol() override
    {
        return "R";
    }
};

class Bishop : public Piece
{
public:
    Bishop(Color color) : Piece(color, BISHOP) {}
    vector<Position> getPossiblePositions(Position pos, Board *board) override;
    string getSymbol() override
    {
        return "B";
    }
};

class Knight : public Piece
{
public:
    Knight(Color color) : Piece(color, KNIGHT) {}
    vector<Position> getPossiblePositions(Position pos, Board *board) override;
    string getSymbol() override
    {
        return "N";
    }
};

class Pawn : public Piece
{
public:
    Pawn(Color color) : Piece(color, PAWN) {}
    vector<Position> getPossiblePositions(Position pos, Board *board) override;
    string getSymbol() override
    {
        return "P";
    }
};

class PieceFactory
{
public:
    static Piece *createPiece(Color color, PieceType type)
    {
        switch (type)
        {
        case KING:
            return new King(color);
        case QUEEN:
            return new Queen(color);
        case PAWN:
            return new Pawn(color);
        case ROOK:
            return new Rook(color);
        case BISHOP:
            return new Bishop(color);
        case KNIGHT:
            return new Knight(color);
        default:
            return nullptr;
        }
    }
};

class Board
{
private:
    Piece *board[8][8];
    map<Position, Piece *> piecePositions;

public:
    Board()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                board[i][j] = nullptr;
            }
        }
        initializeBoard();
    }

    ~Board()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != nullptr)
                {
                    delete board[i][j];
                    board[i][j] = nullptr;
                }
            }
        }
        piecePositions.clear();
    }

    void placePiece(Position pos, Piece *piece)
    {
        board[pos.getRow()][pos.getCol()] = piece;
        piecePositions[pos] = piece;
        return;
    }

    void initializeBoard()
    {
        placePiece(Position(0, 0), PieceFactory::createPiece(WHITE, ROOK));
        placePiece(Position(0, 1), PieceFactory::createPiece(WHITE, KNIGHT));
        placePiece(Position(0, 2), PieceFactory::createPiece(WHITE, BISHOP));
        placePiece(Position(0, 3), PieceFactory::createPiece(WHITE, KING));
        placePiece(Position(0, 4), PieceFactory::createPiece(WHITE, QUEEN));
        placePiece(Position(0, 5), PieceFactory::createPiece(WHITE, BISHOP));
        placePiece(Position(0, 6), PieceFactory::createPiece(WHITE, KNIGHT));
        placePiece(Position(0, 7), PieceFactory::createPiece(WHITE, ROOK));

        for (int i = 0; i < 8; i++)
        {
            placePiece(Position(1, i), PieceFactory::createPiece(WHITE, PAWN));
        }

        placePiece(Position(7, 0), PieceFactory::createPiece(BLACK, ROOK));
        placePiece(Position(7, 1), PieceFactory::createPiece(BLACK, KNIGHT));
        placePiece(Position(7, 2), PieceFactory::createPiece(BLACK, BISHOP));
        placePiece(Position(7, 3), PieceFactory::createPiece(BLACK, KING));
        placePiece(Position(7, 4), PieceFactory::createPiece(BLACK, QUEEN));
        placePiece(Position(7, 5), PieceFactory::createPiece(BLACK, BISHOP));
        placePiece(Position(7, 6), PieceFactory::createPiece(BLACK, KNIGHT));
        placePiece(Position(7, 7), PieceFactory::createPiece(BLACK, ROOK));

        for (int i = 0; i < 8; i++)
        {
            placePiece(Position(6, i), PieceFactory::createPiece(BLACK, PAWN));
        }
    }

    void removePiece(Position pos)
    {
        board[pos.getRow()][pos.getCol()] = nullptr;
        piecePositions.erase(pos);
    }

    Piece *getPiece(Position pos)
    {
        return board[pos.getRow()][pos.getCol()];
    }

    bool isOccupied(Position pos)
    {
        return getPiece(pos) != nullptr;
    }

    bool isOccupiedBySameColor(Position pos, Color color)
    {
        Piece *piece = getPiece(pos);
        return piece != nullptr && piece->getColor() == color;
    }

    void movePiece(Position from, Position to)
    {
        Piece *piece = getPiece(from);
        if (piece != nullptr)
        {
            Piece *captured = getPiece(to);
            if (captured != nullptr)
            {
                delete captured;
                piecePositions.erase(to);
            }

            board[from.getRow()][from.getCol()] = nullptr;
            board[to.getRow()][to.getCol()] = piece;

            piecePositions[from] = nullptr;
            piecePositions[to] = piece;

            piece->setMoved(true);
        }
    }

    Position findKing(Color color)
    {
        for (auto &pair : piecePositions)
        {
            if (pair.second->getSymbol() == "K" && pair.second->getColor() == color)
            {
                return pair.first;
            }
        }
        return Position(-1, -1);
    }

    vector<Position> getAllPieceOfColor(Color color)
    {
        vector<Position> positions;
        for (auto &it : piecePositions)
        {
            if (it.second->getColor() == color)
            {
                positions.push_back(it.first);
            }
        }

        return positions;
    }

    void display()
    {
    }
};

vector<Position> King::getPossiblePositions(Position pos, Board *board)
{
    vector<Position> possiblePositions;
    int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
    for (auto it : directions)
    {
        Position newPos(pos.getRow() + it[0], pos.getCol() + it[1]);
        if (newPos.isValid() && !board->isOccupiedBySameColor(newPos, this->getColor()))
        {
            possiblePositions.push_back(newPos);
        }
    }
    return possiblePositions;
}

vector<Position> Queen::getPossiblePositions(Position pos, Board *board)
{
    vector<Position> possiblePositions;
    int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
    for (auto it : directions)
    {
        for (int i = 1; i < 8; i++)
        {
            Position newPos(pos.getRow() + it[0] * i, pos.getCol() + it[1] * i);
            if (newPos.isValid() && !board->isOccupiedBySameColor(newPos, this->getColor()) && !board->isOccupied(newPos))
            {
                possiblePositions.push_back(newPos);
            }
            else
            {
                break;
            }
        }
    }
    return possiblePositions;
}

vector<Position> Rook::getPossiblePositions(Position pos, Board *board)
{
    vector<Position> possiblePositions;
    int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    for (auto it : directions)
    {
        for (int i = 1; i < 8; i++)
        {
            Position newPos(pos.getRow() + it[0] * i, pos.getCol() + it[1] * i);
            if (newPos.isValid() && !board->isOccupiedBySameColor(newPos, this->getColor()) && !board->isOccupied(newPos))
            {
                possiblePositions.push_back(newPos);
            }
            else
            {
                break;
            }
        }
    }
    return possiblePositions;
}

vector<Position> Bishop::getPossiblePositions(Position pos, Board *board)
{
    vector<Position> possiblePositions;
    int directions[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    for (auto it : directions)
    {
        for (int i = 1; i < 8; i++)
        {
            Position newPos(pos.getRow() + it[0] * i, pos.getCol() + it[1] * i);
            if (newPos.isValid() && !board->isOccupiedBySameColor(newPos, this->getColor()) && !board->isOccupied(newPos))
            {
                possiblePositions.push_back(newPos);
            }
            else
            {
                break;
            }
        }
    }
    return possiblePositions;
}

vector<Position> Knight::getPossiblePositions(Position pos, Board *board)
{
    vector<Position> possiblePositions;
    int directions[8][2] = {{-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {1, 2}, {1, -2}};
    for (auto it : directions)
    {
        Position newPos(pos.getRow() + it[0], pos.getCol() + it[1]);
        if (newPos.isValid() && !board->isOccupiedBySameColor(newPos, this->getColor()))
        {
            possiblePositions.push_back(newPos);
        }
    }
    return possiblePositions;
}

vector<Position> Pawn::getPossiblePositions(Position pos, Board *board)
{
    vector<Position> possiblePositions;
    int direction = (color == WHITE) ? 1 : -1;

    Position oneStep(pos.getRow() + direction, pos.getCol());
    if (oneStep.isValid() && !board->isOccupiedBySameColor(oneStep, color))
    {
        possiblePositions.push_back(oneStep);
        if (!hasMoved)
        {
            Position twoStep(pos.getRow() + direction * 2, pos.getCol());
            if (twoStep.isValid() && !board->isOccupiedBySameColor(twoStep, color))
            {
                possiblePositions.push_back(twoStep);
            }
        }
    }

    Position leftStep(pos.getRow() + direction, pos.getCol() - direction);
    if (leftStep.isValid() && board->isOccupied(leftStep) && !board->isOccupiedBySameColor(leftStep, color))
    {
        possiblePositions.push_back(leftStep);
    }

    Position rightStep(pos.getRow() + direction, pos.getCol() - direction);
    if (rightStep.isValid() && board->isOccupied(rightStep) && !board->isOccupiedBySameColor(rightStep, color))
    {
        possiblePositions.push_back(rightStep);
    }
    return possiblePositions;
}

class ChessRules
{
public:
    virtual ~ChessRules() = default;
    virtual bool isValidMove(Move move, Board *board) = 0;
    virtual bool isInCheck(Color color, Board *board) = 0;
    virtual bool isCheckMate(Color color, Board *board) = 0;
    virtual bool isStaleMate(Color color, Board *board) = 0;
    virtual bool wouldMoveCauseCheck(Move move, Board *board, Color Color) = 0;
};

class StandardChess : public ChessRules
{
public:
    bool isValidMove(Move move, Board *board) override
    {
        Piece *piece = move.getPiece();
        vector<Position> validMoves = piece->getPossiblePositions(move.getFrom(), board);

        bool validDestination = false;
        for (auto it : validMoves)
        {
            if (it == move.getTo())
            {
                validDestination = true;
                break;
            }
        }

        if (!validDestination)
        {
            return false;
        }

        return !wouldMoveCauseCheck(move, board, piece->getColor());
    }

    bool wouldMoveCauseCheck(Move move, Board *board, Color color) override
    {
        Piece *movingPiece = board->getPiece(move.getTo());
        Piece *caputredPiece = board->getPiece(move.getFrom());

        if (movingPiece == nullptr)
        {
            return true;
        }

        board->removePiece(move.getFrom());
        if (caputredPiece != nullptr)
        {
            board->removePiece(move.getTo());
        }
        board->placePiece(move.getTo(), movingPiece);

        bool inCheck = isInCheck(movingPiece->getColor(), board);

        board->removePiece(move.getTo());
        board->placePiece(move.getFrom(), movingPiece);
        if (caputredPiece != nullptr)
        {
            board->placePiece(move.getTo(), caputredPiece);
        }
        return inCheck;
    }

    bool isInCheck(Color color, Board *board) override
    {
        Position kingPos = board->findKing(color);
        if (kingPos.getRow() == -1)
        {
            return false;
        }
        Color opponentColor = color == WHITE ? BLACK : WHITE;
        vector<Position> opponentPieces = board->getAllPieceOfColor(opponentColor);
        for (auto it : opponentPieces)
        {
            Piece *piece = board->getPiece(it);
            vector<Position> possiblePositions = piece->getPossiblePositions(it, board);
            for (auto pos : possiblePositions)
            {
                if (pos == kingPos)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isCheckMate(Color color, Board *board) override
    {
        if (!isInCheck(color, board))
        {
            return false;
        }

        vector<Position> pieces = board->getAllPieceOfColor(color);
        for (const Position &pos : pieces)
        {
            Piece *piece = board->getPiece(pos);
            vector<Position> possilbePos = piece->getPossiblePositions(pos, board);
            for (const Position &p : possilbePos)
            {
                Move move(pos, p, piece, board->getPiece(p));
                if (isValidMove(move, board))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isStaleMate(Color color, Board *board) override
    {
        if (isInCheck(color, board))
        {
            return false;
        }

        vector<Position> pieces = board->getAllPieceOfColor(color);
        for (const Position &pos : pieces)
        {
            Piece *piece = board->getPiece(pos);
            vector<Position> possilbePos = piece->getPossiblePositions(pos, board);
            for (const Position &p : possilbePos)
            {
                Move move(pos, p, piece, board->getPiece(p));
                if (isValidMove(move, board))
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class ChatMediator
{
public:
    void sendMessage(Message *message, User *user) {}
};

class Message
{
private:
    string senderId;
    string message;
    time_t timestamp;

public:
    Message(string senderId, string message)
    {
        this->senderId = senderId;
        this->message = message;
        this->timestamp = time(0);
    }

    string getSenderId() { return senderId; }
    string getMessage() { return message; }
    time_t getTimeStamp() { return timestamp; }

    string toString()
    {
        return "[" + senderId + "]" + message;
    }
};

class Colleague
{
protected:
    ChatMediator *mediator;

public:
    Colleague() : mediator(nullptr) {}
    virtual ~Colleague() = 0;
    virtual void send(Message *message) = 0;
    virtual void receive(Message *message) = 0;
    void setMediator(ChatMediator *med)
    {
        mediator = med;
    }

    ChatMediator *getMediator() const
    {
        return mediator;
    }
};

class User : public Colleague
{
    string id, name;
    int score;

public:
    User(string uId, string uname)
    {
        id = uId;
        name = uname;
    }

    string getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }

    int getScore() { return score; }

    void incrementScore(int points)
    {
        score += points;
    }

    void decrementScore(int points)
    {
        score -= points;
    }

    void send(Message *message) override
    {
        if (mediator != nullptr)
        {
            mediator->sendMessage(message, this);
        }
    }

    void receive(Message *message) override
    {
        cout << "User " << name << " recieved message from " << message->getSenderId() << endl;
        cout << "Message: " << message->getMessage() << " at " << message->getTimeStamp() << endl;
    }
};

class Match : public ChatMediator
{
private:
    string matchId;
    User *whitePlayer;
    User *blackPlayer;
    Board *board;
    ChessRules *rules;
    Color currentTurn;
    GameStatus status;
    vector<Move> moveHistory;
    vector<Message *> chatHistory;

public:
    Match(string mId, User *white, User *black)
    {
        matchId = mId;
        whitePlayer = white;
        blackPlayer = black;
        board = new Board();
        rules = new StandardChess();
        currentTurn = WHITE;
        status = INPROGRESS;
        whitePlayer->setMediator(this);
        blackPlayer->setMediator(this);
        cout << "Match started between " << whitePlayer->getName() << " & " << blackPlayer->getName() << endl;
    }

    ~Match()
    {
        delete board;
        delete rules;
    }

    Color getPlayerColor(User *player)
    {
        return whitePlayer == player ? WHITE : BLACK;
    }

    bool makeMove(Position from, Position to, User *player)
    {
        if (status != INPROGRESS)
        {
            return false;
        }

        Color playerColor = getPlayerColor(player);
        if (playerColor != currentTurn)
        {
            return false;
        }

        Piece *piece = board->getPiece(from);
    }
};