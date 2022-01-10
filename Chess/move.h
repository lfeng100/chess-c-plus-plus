#ifndef _MOVE_H_
#define _MOVE_H_

#include <memory>

class Cell;
class Piece;

class Move {
  std::shared_ptr<Cell> fromCell;
  std::shared_ptr<Cell> toCell;
  // std::shared_ptr<Piece> piece;
  std::shared_ptr<Piece> capturedPiece;
  bool castleMove;
  bool enPassantMove;
  bool pawnPromotionMove;
  
  public:
    Move(std::shared_ptr<Cell> fromCell, std::shared_ptr<Cell> toCell, std::shared_ptr<Piece> capturedPiece);
    
    std::shared_ptr<Cell> getFromCell();
    std::shared_ptr<Cell> getToCell();
    
    int getXChange();
    int getYChange();
    std::shared_ptr<Piece> getCapturedPiece();
    bool isCastleMove();
    bool isEnPassantMove();
    bool isPawnPromotionMove();

    void setCastleMove();
    void setEnPassantMove();
    void setPawnPromotionMove();
    void setCapturedPiece(std::shared_ptr<Piece> thePiece);
};

#endif