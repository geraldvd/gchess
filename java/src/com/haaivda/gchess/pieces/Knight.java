package com.haaivda.gchess.pieces;

import com.haaivda.gchess.Alliance;
import com.haaivda.gchess.board.Board;
import com.haaivda.gchess.board.BoardUtils;
import com.haaivda.gchess.board.Move;
import com.haaivda.gchess.board.Move.AttackMove;
import com.haaivda.gchess.board.Move.MajorMove;
import com.haaivda.gchess.board.Tile;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public class Knight extends Piece {
    private final int[] CANDIDATE_MOVE_COORDINATES = {-17, -15, -10, -6, 6, 10, 15, 17};

    public Knight(int piecePosition, Alliance pieceAlliance) {
        super(piecePosition, pieceAlliance);
    }

    @Override
    public List<Move> calculateLegalMoves(Board board) {
        final List<Move> legalMoves = new ArrayList<>();
        
        for(int currentCandidateOffset : CANDIDATE_MOVE_COORDINATES) {
            final int candidateDestinationCoordinate = piecePosition + currentCandidateOffset;
            if(BoardUtils.isValidTileCoordinate(candidateDestinationCoordinate)){ 
                if(isFirstColumnExclusion(this.piecePosition, currentCandidateOffset) ||
                        isSecondColumnExclusion(this.piecePosition, currentCandidateOffset) ||
                        isSeventhColumnExclusion(this.piecePosition, currentCandidateOffset) ||
                        isEighthColumnExclusion(this.piecePosition, currentCandidateOffset)) {
                    continue;
                }
                final Tile destinationTile = board.getTile(candidateDestinationCoordinate);
                if(!destinationTile.isTileOccupied()) {
                    legalMoves.add(new MajorMove(board, this, candidateDestinationCoordinate));
                } else {
                    if (this.pieceAlliance != destinationTile.getPiece().getPieceAlliance()) {
                        legalMoves.add(new AttackMove(board, this, candidateDestinationCoordinate, destinationTile.getPiece()));
                    } 
                }
            }            
        }
        return Collections.unmodifiableList(legalMoves);
    }
    
    private static boolean isFirstColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.FIRST_COLUMN[currentPosition] && (candidateOffset == -17 || candidateOffset == -10 || 
                candidateOffset == 6 || candidateOffset == 15);
    }
    
    private static boolean isSecondColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.SECOND_COLUMN[currentPosition] && (candidateOffset == -10 || candidateOffset == 6);
    }
    
    private static boolean isSeventhColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.SEVENTH_COLUMN[currentPosition] && (candidateOffset == -6 || candidateOffset == 10);
    }
    
    private static boolean isEighthColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.EIGHTH_COLUMN[currentPosition] && (candidateOffset == -15 || candidateOffset == -6 || 
                candidateOffset == 10 || candidateOffset == 17);
    }
}
