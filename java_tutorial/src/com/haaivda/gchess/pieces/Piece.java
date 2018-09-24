package com.haaivda.gchess.pieces;

import com.haaivda.gchess.Alliance;
import com.haaivda.gchess.board.Board;
import com.haaivda.gchess.board.Move;
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
    
    public final boolean isFirstMove() {
        return this.isFirstMove;
    }
    
    public abstract Collection<Move> calculateLegalMoves(Board board);
}