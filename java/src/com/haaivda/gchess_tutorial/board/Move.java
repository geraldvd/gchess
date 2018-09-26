package com.haaivda.gchess_tutorial.board;

import com.haaivda.gchess_tutorial.pieces.Piece;

public abstract class Move {
    
    final Board board;
    final Piece movedPiece;
    final int destinationCoordinate;
    
    private Move(Board board, Piece movedPiece, int destinationCoordinate) {
        this.board = board;
        this.movedPiece = movedPiece;
        this.destinationCoordinate = destinationCoordinate;
    }
    
    public static final class MajorMove extends Move {
        public MajorMove(Board board, Piece movedPiece, int destinationCoordinate) {
            super(board, movedPiece, destinationCoordinate);
        }
    }
    
    public static final class AttackMove extends Move {
        final Piece attackedPiece;
        
        public AttackMove(Board board, Piece movedPiece, int destinationCoordinate, Piece attackedPiece) {
            super(board, movedPiece, destinationCoordinate);
            this.attackedPiece = attackedPiece;
        }
    }
}