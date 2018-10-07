package com.haaivda.gchess_tutorial.engine.pieces;

import com.haaivda.gchess_tutorial.engine.Alliance;
import com.haaivda.gchess_tutorial.engine.board.Board;
import com.haaivda.gchess_tutorial.engine.board.BoardUtils;
import com.haaivda.gchess_tutorial.engine.board.Move;
import com.haaivda.gchess_tutorial.engine.board.Move.MajorMove;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;


public class Pawn extends Piece {

    private final static int[] CANDIDATE_MOVE_COORDINATES = {8, 16, 7, 9};
    
    public Pawn(int piecePosition, Alliance pieceAlliance) {
        super(PieceType.PAWN, piecePosition, pieceAlliance);
    }

    @Override
    public Collection<Move> calculateLegalMoves(Board board) {
        final List<Move> legalMoves = new ArrayList<>();
        for(final int currentCandidateOffset : CANDIDATE_MOVE_COORDINATES) {
            int candidateDestinationCoordinate = this.getPieceAlliance().getDirection()*this.piecePosition + currentCandidateOffset;
            if(!BoardUtils.isValidTileCoordinate(candidateDestinationCoordinate)) {
                continue;
            }
            if(currentCandidateOffset == 8 && !board.getTile(candidateDestinationCoordinate).isTileOccupied()) {
                legalMoves.add(new MajorMove(board, this, candidateDestinationCoordinate)); // TODO more work to do here (pawn promotion)
            } else if(currentCandidateOffset == 16 && this.isFirstMove() && (BoardUtils.SEVENTH_RANK[this.piecePosition] && (this.getPieceAlliance().isBlack()) ||
                    (BoardUtils.SECOND_RANK[this.piecePosition] && this.getPieceAlliance().isWhite()))) {
                final int behindCandidateDestinationCoordinate = this.piecePosition + this.getPieceAlliance().getDirection()*8;
                if(!board.getTile(behindCandidateDestinationCoordinate).isTileOccupied() && !board.getTile(candidateDestinationCoordinate).isTileOccupied()) {
                    legalMoves.add(new MajorMove(board, this, candidateDestinationCoordinate)); // TODO more work to do here (pawn promotion)
                }
            } else if(currentCandidateOffset == 7 && 
                    !((BoardUtils.EIGHTH_COLUMN[this.piecePosition] && this.getPieceAlliance().isWhite()) ||
                    (BoardUtils.FIRST_COLUMN[this.piecePosition] && this.getPieceAlliance().isBlack()))) {
                if(board.getTile(candidateDestinationCoordinate).isTileOccupied()) {
                    final Piece pieceOnCandidate = board.getTile(candidateDestinationCoordinate).getPiece();
                    if(this.getPieceAlliance() != pieceOnCandidate.getPieceAlliance()) {
                        legalMoves.add(new MajorMove(board, this, candidateDestinationCoordinate)); // TODO more work to do here (pawn promotion)
                    }
                }
            } else if(currentCandidateOffset == 9 && 
                    !((BoardUtils.EIGHTH_COLUMN[this.piecePosition] && this.getPieceAlliance().isBlack()) ||
                    (BoardUtils.FIRST_COLUMN[this.piecePosition] && this.getPieceAlliance().isWhite()))) {
                if(board.getTile(candidateDestinationCoordinate).isTileOccupied()) {
                    final Piece pieceOnCandidate = board.getTile(candidateDestinationCoordinate).getPiece();
                    if(this.pieceAlliance != pieceOnCandidate.getPieceAlliance()) {
                        legalMoves.add(new MajorMove(board, this, candidateDestinationCoordinate)); // TODO more work to do here (pawn promotion)
                    }
                }
            }
        }
        return Collections.unmodifiableList(legalMoves);
    }

    @Override
    public Pawn movePiece(Move move) {
        return new Pawn(move.getDestinationCoordinate(), move.getMovedPiece().getPieceAlliance());
    }
    
    @Override
    public String toString() {
        return PieceType.PAWN.toString();
    }
}
