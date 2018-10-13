package com.haaivda.gchess_tutorial.engine.player;

import com.google.common.collect.ImmutableList;
import com.google.common.collect.Iterables;
import com.haaivda.gchess_tutorial.engine.Alliance;
import com.haaivda.gchess_tutorial.engine.board.Board;
import com.haaivda.gchess_tutorial.engine.board.Move;
import com.haaivda.gchess_tutorial.engine.pieces.King;
import com.haaivda.gchess_tutorial.engine.pieces.Piece;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public abstract class Player {

    protected final Board board;
    final King playerKing;
    private final Collection<Move> legalMoves;
    private final boolean isInCheck;

    Player(Board board, Collection<Move> legalMoves, Collection<Move> opponentMoves) {
        this.board = board;
        this.playerKing = this.establishKing();
        this.legalMoves = ImmutableList.copyOf(Iterables.concat(legalMoves, calculateKingCastles(legalMoves, opponentMoves))); // Google Guava needed to concat collections
        this.isInCheck = !Player.calculateAttacksOnTile(this.playerKing.getPiecePosition(), opponentMoves).isEmpty();
    }

    static Collection<Move> calculateAttacksOnTile(int piecePosition, Collection<Move> moves) {
        final List<Move> attackMoves = new ArrayList<>();
        for(Move move : moves) {
            if(piecePosition == move.getDestinationCoordinate()) {
                attackMoves.add(move);
            }
        }

        return Collections.unmodifiableList(attackMoves);
    }

    private King establishKing() {
        King king = null;

        for(Piece piece : this.getActivePieces()) {
            if(piece.getPieceType().isKing()) {
                if(king == null) {
                    king = (King) piece;
                } else {
                    throw new RuntimeException("Not a valid board; multiple Kings found!");
                }
            }
        }
        if(king == null) {
            throw new RuntimeException("Not a valid board; no King found!");
        }
        return king;
    }

    private boolean isMoveLegal(Move move) {
        return this.legalMoves.contains(move);
    }

    public boolean isInCheck() {
        return this.isInCheck;
    }

    public boolean isInCheckMate() {
        return this.isInCheck && !this.hasEscapeMoves();
    }

    public boolean isInStaleMate() {
        return !this.isInCheck && !this.hasEscapeMoves();
    }

    //TODO implement
    public boolean isCastled() {
        return false;
    }

    private boolean hasEscapeMoves() {
        for(Move move : this.legalMoves) {
            final MoveTransition transition = this.makeMove(move);
            if(transition.getMoveStatus().isDone()) {
                return true;
            }
        }
        return false;
    }

    public MoveTransition makeMove(Move move) {
        if(!this.isMoveLegal(move)) {
            return new MoveTransition(this.board, move, MoveStatus.ILLEGAL_MOVE);
        }

        final Board transitionBoard = move.execute();

        final Collection<Move> kingAttacks = Player.calculateAttacksOnTile(transitionBoard.getCurrentPlayer().getOpponent().getPlayerKing().getPiecePosition(),
                transitionBoard.getCurrentPlayer().getLegalMoves());

        if(!kingAttacks.isEmpty()) {
            return new MoveTransition(this.board, move, MoveStatus.LEAVES_PLAYER_IN_CHECK);
        }

        return new MoveTransition(transitionBoard, move, MoveStatus.DONE);
    }

    public Collection<Move> getLegalMoves() {
        return this.legalMoves;
    }

    private King getPlayerKing() {
        return this.playerKing;
    }

    public abstract Collection<Piece> getActivePieces();
    public abstract Alliance getAlliance();
    public abstract Player getOpponent();
    protected abstract Collection<Move> calculateKingCastles(Collection<Move> playerLegals, Collection<Move> opponentLegals);
}
