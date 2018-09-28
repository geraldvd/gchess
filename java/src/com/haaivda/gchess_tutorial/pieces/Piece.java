package com.haaivda.gchess_tutorial.pieces;

import com.haaivda.gchess_tutorial.Alliance;
import com.haaivda.gchess_tutorial.board.Board;
import com.haaivda.gchess_tutorial.board.Move;
import java.util.Collection;


public abstract class Piece {
    protected final int piecePosition;
    protected final Alliance pieceAlliance;
    protected final boolean isFirstMove;
    
    Piece(int piecePosition, Alliance pieceAlliance) {
        this.piecePosition = piecePosition;
        this.pieceAlliance = pieceAlliance;
        this.isFirstMove = false; // TODO more work here!
    }
    
    public final Alliance getPieceAlliance() {
        return this.pieceAlliance;
    }
    
    public final int getPiecePosition() {
        return this.piecePosition;
    }
    
    public final boolean isFirstMove() {
        return this.isFirstMove;
    }
    
    public abstract Collection<Move> calculateLegalMoves(Board board);
}
