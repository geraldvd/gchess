package com.haaivda.gchess_tutorial.pieces;

import com.haaivda.gchess_tutorial.Alliance;
import com.haaivda.gchess_tutorial.board.Board;
import com.haaivda.gchess_tutorial.board.BoardUtils;
import com.haaivda.gchess_tutorial.board.Move;
import com.haaivda.gchess_tutorial.board.Tile;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;


public class King extends Piece {
    private final int[] CANDIDATE_MOVE_COORDINATES = {-9, -8, -7, -1, 1, 7, 8, 9};

    public King(int piecePosition, Alliance pieceAlliance) {
        super(PieceType.KING, piecePosition, pieceAlliance);
    }

    @Override
    public Collection<Move> calculateLegalMoves(Board board) {
        final List<Move> legalMoves = new ArrayList<>();
        for(int currentCandidateOffset : CANDIDATE_MOVE_COORDINATES) {
            int candidateDestinationCoordinate = this.piecePosition + currentCandidateOffset;
            if(BoardUtils.isValidTileCoordinate(candidateDestinationCoordinate)){ 
                if(isFirstColumnExclusion(this.piecePosition, currentCandidateOffset) ||
                        isEighthColumnExclusion(this.piecePosition, currentCandidateOffset)) {
                    continue;
                }
                final Tile destinationTile = board.getTile(candidateDestinationCoordinate);
                if(!destinationTile.isTileOccupied()) {
                    legalMoves.add(new Move.MajorMove(board, this, candidateDestinationCoordinate));
                } else {
                    if (this.pieceAlliance != destinationTile.getPiece().getPieceAlliance()) {
                        legalMoves.add(new Move.AttackMove(board, this, candidateDestinationCoordinate, destinationTile.getPiece()));
                    } 
                }
            }
        }
        return Collections.unmodifiableList(legalMoves);
    }
    @Override
    public String toString() {
        return PieceType.KING.toString();
    }
    

    private boolean isFirstColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.FIRST_COLUMN[currentPosition] && (candidateOffset == -9 || candidateOffset == -1 || 
                candidateOffset == 7);
    }

    private static boolean isEighthColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.EIGHTH_COLUMN[currentPosition] && (candidateOffset == -7 || candidateOffset == 1 || 
                candidateOffset == 9);
    }
    
}
