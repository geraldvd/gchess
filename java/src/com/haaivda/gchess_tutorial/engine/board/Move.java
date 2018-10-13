package com.haaivda.gchess_tutorial.engine.board;

import com.haaivda.gchess_tutorial.engine.board.Board.Builder;
import com.haaivda.gchess_tutorial.engine.pieces.Pawn;
import com.haaivda.gchess_tutorial.engine.pieces.Piece;
import com.haaivda.gchess_tutorial.engine.pieces.Rook;

public abstract class Move {
    
    protected final Board board;
    final Piece movedPiece;
    final int destinationCoordinate;
    protected final boolean isFirstMove;

    private static final Move NULL_MOVE = new NullMove();
    
    private Move(Board board, Piece movedPiece, int destinationCoordinate) {
        this.board = board;
        this.movedPiece = movedPiece;
        this.destinationCoordinate = destinationCoordinate;
        this.isFirstMove = movedPiece.isFirstMove();
    }

    private Move(Board board, int destinationCoordinate) {
        this.board = board;
        this.destinationCoordinate = destinationCoordinate;
        this.movedPiece = null;
        this.isFirstMove = false;
    }

    @Override
    public int hashCode() {
        int result = 1;
        result = 31 * result + this.destinationCoordinate;
        result = 31 * result + this.movedPiece.hashCode();
        result = 31 * result + this.movedPiece.getPiecePosition();
        return result;
    }

    @Override
    public boolean equals(Object other) {
        if(this == other) {
            return true;
        }
        if(!(other instanceof Move)) {
            return false;
        }
        final Move otherMove = (Move) other;
        return this.getDestinationCoordinate() == otherMove.getDestinationCoordinate() && this.getMovedPiece().equals(otherMove.getMovedPiece()) && getCurrentCoordinate() == otherMove.getCurrentCoordinate();
    }

    public Board getBoard() {
        return this.board;
    }

    public int getDestinationCoordinate() {
        return this.destinationCoordinate;
    }

    public Piece getMovedPiece() {
        return this.movedPiece;
    }

    public boolean isAttack() {
        return false;
    }

    public boolean isCastleMove() {
        return false;
    }

    public Piece getAttackedPiece() {
        return null;
    }

    public Board execute() {
        final Builder builder = new Builder();
        for(Piece piece : this.board.getCurrentPlayer().getActivePieces()) {
            if(!this.movedPiece.equals(piece)) {
                builder.setPiece(piece);
            }
        }
        for(Piece piece : this.board.getCurrentPlayer().getOpponent().getActivePieces()) {
            builder.setPiece(piece);
        }
        // move the moved piece
        builder.setPiece(this.movedPiece.movePiece(this));
        builder.setMoveMaker(this.board.getCurrentPlayer().getOpponent().getAlliance());
        return builder.build();
    }

    public static final class MajorMove extends Move {
        public MajorMove(Board board, Piece movedPiece, int destinationCoordinate) {
            super(board, movedPiece, destinationCoordinate);
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof MajorMove && super.equals(other);
        }

        @Override
        public String toString() {
            assert movedPiece != null;
            return movedPiece.getPieceType().toString() + BoardUtils.getPositionAtCoordinate(this.destinationCoordinate);
        }
    }

    public static class AttackMove extends Move {
        final Piece attackedPiece;

        AttackMove(Board board, Piece movedPiece, int destinationCoordinate, Piece attackedPiece) {
            super(board, movedPiece, destinationCoordinate);
            this.attackedPiece = attackedPiece;
        }

        @Override
        public int hashCode() {
            return this.attackedPiece.hashCode() + super.hashCode();
        }

        @Override
        public boolean equals(Object other) {
            if(this == other) {
                return true;
            }
            if(!(other instanceof AttackMove)) {
                return false;
            }
            final AttackMove otherAttackMove = (AttackMove) other;
            return super.equals(otherAttackMove) && this.getAttackedPiece().equals(otherAttackMove.getAttackedPiece());
        }

        @Override
        public boolean isAttack() {
            return true;
        }

        @Override
        public Piece getAttackedPiece() {
            return this.attackedPiece;
        }
    }

    public static final class MajorAttackMove extends AttackMove {
        public MajorAttackMove(Board board, Piece movedPiece, int destinationCoordinate, Piece pieceAttacked) {
            super(board, movedPiece, destinationCoordinate, pieceAttacked);
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof MajorAttackMove && super.equals(other);
        }

        @Override
        public String toString() {
            assert movedPiece != null;
            return movedPiece.getPieceType() + BoardUtils.getPositionAtCoordinate(this.destinationCoordinate);
        }
    }

    public static final class PawnMove extends Move {
        public PawnMove(Board board, Piece movedPiece, int destinationCoordinate) {
            super(board, movedPiece, destinationCoordinate);
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof PawnMove && super.equals(other);
        }

        @Override
        public String toString() {
            return BoardUtils.getPositionAtCoordinate(this.destinationCoordinate);
        }
    }

    public static class PawnAttackMove extends AttackMove {
        public PawnAttackMove(Board board, Piece movedPiece, int destinationCoordinate, Piece attackedPiece) {
            super(board, movedPiece, destinationCoordinate, attackedPiece);
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof PawnAttackMove && super.equals(other);
        }

        @Override
        public String toString() {
            assert this.movedPiece != null;
            return BoardUtils.getPositionAtCoordinate(this.movedPiece.getPiecePosition()).substring(0, 1) + "x" +
                    BoardUtils.getPositionAtCoordinate(this.destinationCoordinate);
        }
    }

    public static final class PawnEnPassantAttackMove extends PawnAttackMove {
        public PawnEnPassantAttackMove(Board board, Piece movedPiece, int destinationCoordinate, Piece attackedPiece) {
            super(board, movedPiece, destinationCoordinate, attackedPiece);
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof PawnEnPassantAttackMove && super.equals(other);
        }

        @Override
        public Board execute() {
            final Builder builder = new Builder();
            for(Piece piece : this.board.getCurrentPlayer().getActivePieces()) {
                assert this.movedPiece != null;
                if(!this.movedPiece.equals(piece)) {
                    builder.setPiece(piece);
                }
            }
            for(Piece piece : this.board.getCurrentPlayer().getOpponent().getActivePieces()) {
                // Difference with normal move: the attacked piece is not at the destination tile of moved piece
                if(!piece.equals(this.getAttackedPiece())) {
                    builder.setPiece(piece);
                }
            }
            assert this.movedPiece != null;
            builder.setPiece(this.movedPiece.movePiece(this));
            builder.setMoveMaker(this.board.getCurrentPlayer().getOpponent().getAlliance());
            return builder.build();
        }
    }

    public static final class PawnPromotion extends Move {
        // Design pattern: decorator

        final Move decoratedMove;
        final Pawn promotedPawn;

        public PawnPromotion(Move decoratedMove) {
            super(decoratedMove.getBoard(), decoratedMove.getMovedPiece(), decoratedMove.getDestinationCoordinate());
            this.decoratedMove = decoratedMove;
            this.promotedPawn = (Pawn)decoratedMove.getMovedPiece();
        }

        @Override
        public int hashCode() {
            return decoratedMove.hashCode() + (31 * promotedPawn.hashCode());
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof PawnPromotion && super.equals(other);
        }

        @Override
        public Board execute() {
            final Board pawnMovedBoard = this.decoratedMove.execute();
            final Builder builder = new Builder();
            for(Piece piece : pawnMovedBoard.getCurrentPlayer().getActivePieces()) {
                if(!this.promotedPawn.equals(piece)) {
                    builder.setPiece(piece);
                }
            }
            for(Piece piece : pawnMovedBoard.getCurrentPlayer().getOpponent().getActivePieces()) {
                builder.setPiece(piece);
            }
            builder.setPiece(this.promotedPawn.getPromotionPiece().movePiece(this));
            builder.setMoveMaker(pawnMovedBoard.getCurrentPlayer().getAlliance());
            return builder.build();
        }

        @Override
        public boolean isAttack() {
            return this.decoratedMove.isAttack();
        }

        @Override
        public Piece getAttackedPiece() {
            return this.decoratedMove.getAttackedPiece();
        }

        @Override
        public String toString() {
            return "PROMOTION";
        }
    }

    public static final class PawnJump extends Move {
        public PawnJump(Board board, Piece movedPiece, int destinationCoordinate) {
            super(board, movedPiece, destinationCoordinate);
        }

        @Override
        public Board execute() {
            final Builder builder = new Builder();
            for(Piece piece : this.board.getCurrentPlayer().getActivePieces()) {
                assert this.movedPiece != null;
                if(!this.movedPiece.equals(piece)) {
                    builder.setPiece(piece);
                }
            }
            for(Piece piece : this.board.getCurrentPlayer().getOpponent().getActivePieces()) {
                builder.setPiece(piece);
            }
            assert this.movedPiece != null;
            final Pawn movedPawn = (Pawn)this.movedPiece.movePiece(this);
            builder.setPiece(movedPawn);
            builder.setEnPassantPawn(movedPawn);
            builder.setMoveMaker(this.board.getCurrentPlayer().getOpponent().getAlliance());

            return builder.build();
        }

        @Override
        public String toString() {
            return BoardUtils.getPositionAtCoordinate(this.destinationCoordinate);
        }
    }

    static abstract class CastleMove extends Move {

        final Rook castleRook;
        final int castleRookStart;
        final int castleRookDestination;


        CastleMove(Board board, Piece movedPiece, int destinationCoordinate,
                   Rook castleRook, int castleRookStart, int castleRookDestination) {
            super(board, movedPiece, destinationCoordinate);
            this.castleRook = castleRook;
            this.castleRookStart = castleRookStart;
            this.castleRookDestination = castleRookDestination;
        }

        Rook getCastleRook() {
            return this.castleRook;
        }

        @Override
        public boolean isCastleMove() {
            return true;
        }

        @Override
        public Board execute() {
            final Builder builder = new Builder();
            for(Piece piece : this.board.getCurrentPlayer().getActivePieces()) {
                assert this.movedPiece != null;
                if(!this.movedPiece.equals(piece) && !this.castleRook.equals(piece)) {
                    builder.setPiece(piece);
                }
            }
            for(Piece piece : this.board.getCurrentPlayer().getOpponent().getActivePieces()) {
                builder.setPiece(piece);
            }
            assert this.movedPiece != null;
            builder.setPiece(this.movedPiece.movePiece(this));
            builder.setPiece(new Rook(this.castleRookDestination, this.castleRook.getPieceAlliance(), false));
            builder.setMoveMaker(this.board.getCurrentPlayer().getOpponent().getAlliance());
            return builder.build();
        }

        @Override
        public int hashCode() {
            int result = super.hashCode();
            result = 31 * result + this.castleRook.hashCode();
            result = 31 * result + this.castleRookDestination;
            return result;
        }

        @Override
        public boolean equals(Object other) {
            if(this == other) {
                return true;
            }
            if(!(other instanceof CastleMove)) {
                return false;
            }
            final CastleMove otherCastleMove = (CastleMove)other;
            return super.equals(otherCastleMove) && this.castleRook.equals(otherCastleMove.getCastleRook());
        }
    }

    public static final class KingSideCastleMove extends CastleMove {
        public KingSideCastleMove(Board board, Piece movedPiece, int destinationCoordinate,
                                  Rook castleRook, int castleRookStart, int castleRookDestination) {
            super(board, movedPiece, destinationCoordinate, castleRook, castleRookStart, castleRookDestination);
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof KingSideCastleMove && super.equals(other);
        }

        @Override
        public String toString() {
            return "0-0"; // Chess naming convention (PGN)
        }
    }

    public static final class QueenSideCastleMove extends CastleMove {

        public QueenSideCastleMove(Board board, Piece movedPiece, int destinationCoordinate,
                                   Rook castleRook, int castleRookStart, int castleRookDestination) {
            super(board, movedPiece, destinationCoordinate, castleRook, castleRookStart, castleRookDestination);
        }

        @Override
        public boolean equals(Object other) {
            return this == other || other instanceof QueenSideCastleMove && super.equals(other);
        }

        @Override
        public String toString() {
            return "0-0-0"; // Chess naming convention (PGN)
        }
    }

    public static final class NullMove extends Move {
        private NullMove() {
            super(null,-1);
        }

        @Override
        public Board execute() {
        throw new RuntimeException("Cannot execute the null move!");
        }

        @Override
        public int getCurrentCoordinate() {
            return -1;
        }
    }

    public static class MoveFactory {
        private MoveFactory() {
            throw new RuntimeException("Not instantiable!");
        }

        public static Move createMove(Board board, int currentCoordinate, int destinationCoordinate) {
            // Note: in movie #24, board.getAllLegalMoves is introduced, but Guava is required for that.
            for(Move move : board.getCurrentPlayer().getLegalMoves()) {
                if(move.getCurrentCoordinate() == currentCoordinate && move.getDestinationCoordinate() == destinationCoordinate) {
                    return move;
                }
            }
            return NULL_MOVE;
        }
    }

    public int getCurrentCoordinate() {
        return this.movedPiece.getPiecePosition();
    }
}
