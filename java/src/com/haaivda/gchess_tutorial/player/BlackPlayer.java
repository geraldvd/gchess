package com.haaivda.gchess_tutorial.player;

import com.haaivda.gchess_tutorial.Alliance;
import com.haaivda.gchess_tutorial.board.Board;
import com.haaivda.gchess_tutorial.board.Move;
import com.haaivda.gchess_tutorial.pieces.Piece;

import java.util.Collection;

public class BlackPlayer extends Player {
    public BlackPlayer(Board board, Collection<Move> whiteStandardLegalMoves, Collection<Move> blackStandardLegalMoves) {
        super(board, blackStandardLegalMoves, whiteStandardLegalMoves);
    }

    @Override
    public Collection<Piece> getActivePieces() {
        return this.board.getBlackPieces();
    }

    @Override
    public Alliance getAlliance() {
        return Alliance.BLACK;
    }

    @Override
    public Player getOpponent() {
        return this.board.getWhitePlayer();
    }
}
