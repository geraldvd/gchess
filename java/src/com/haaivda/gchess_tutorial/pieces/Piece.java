package com.haaivda.gchess_tutorial.pieces;

import com.haaivda.gchess_tutorial.Alliance;
import com.haaivda.gchess_tutorial.board.Board;
import com.haaivda.gchess_tutorial.board.Move;
import java.util.Collection;


public abstract class Piece {
    protected final PieceType pieceType;
    protected final int piecePosition;
    protected final Alliance pieceAlliance;
    protected final boolean isFirstMove;
    
    Piece(PieceType pieceType, int piecePosition, Alliance pieceAlliance) {
        this.pieceType = pieceType;
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

    public PieceType getPieceType() {
        return this.pieceType;
    }

    public enum PieceType {
        KING("K") {
            @Override
            public boolean isKing() {
                return true;
            }
        },
        QUEEN("Q") {
            @Override
            public boolean isKing() {
                return false;
            }
        },
        ROOK("R") {
            @Override
            public boolean isKing() {
                return false;
            }
        },
        BISHOP("B") {
            @Override
            public boolean isKing() {
                return false;
            }
        },
        KNIGHT("N") {
            @Override
            public boolean isKing() {
                return false;
            }
        },
        PAWN("P") {
            @Override
            public boolean isKing() {
                return false;
            }
        };
        
        private String pieceName;
        
        PieceType(String pieceName) {
            this.pieceName = pieceName;
        }
        
        @Override
        public String toString() {
            return this.pieceName;
        }

        public abstract boolean isKing();
    }
}
