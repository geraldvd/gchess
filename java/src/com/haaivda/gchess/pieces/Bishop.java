package com.haaivda.gchess.pieces;

import com.haaivda.gchess.Alliance;
import com.haaivda.gchess.board.Board;
import com.haaivda.gchess.board.BoardUtils;
import com.haaivda.gchess.board.Move;
import com.haaivda.gchess.board.Move.AttackMove;
import com.haaivda.gchess.board.Move.MajorMove;
import com.haaivda.gchess.board.Tile;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;


public class Bishop extends Piece {
    private final static int[] CANDIDATE_MOVE_VECTOR_COORDINATES = {-9, -7, 7, 9};

    public Bishop(int piecePosition, Alliance pieceAlliance) {
        super(piecePosition, pieceAlliance);
    }

    @Override
    public Collection<Move> calculateLegalMoves(Board board) {
        final List<Move> legalMoves = new ArrayList<>();
        for(int currentCandidateCoordinateOffset : CANDIDATE_MOVE_VECTOR_COORDINATES) {
            int candidateDestinationCoordinate = this.piecePosition;
            while(BoardUtils.isValidTileCoordinate(candidateDestinationCoordinate)) {
                if(isFirstColumnExclusion(candidateDestinationCoordinate, currentCandidateCoordinateOffset) ||
                        isEighthColumnExclusion(candidateDestinationCoordinate, currentCandidateCoordinateOffset))
                
                candidateDestinationCoordinate += currentCandidateCoordinateOffset;
                if(BoardUtils.isValidTileCoordinate(candidateDestinationCoordinate)) {
                    final Tile destinationTile = board.getTile(candidateDestinationCoordinate);
                    if(!destinationTile.isTileOccupied()) {
                        legalMoves.add(new MajorMove(board, this, candidateDestinationCoordinate));
                    } else {
                        if (this.pieceAlliance != destinationTile.getPiece().getPieceAlliance()) {
                            legalMoves.add(new AttackMove(board, this, candidateDestinationCoordinate, destinationTile.getPiece()));
                        }
                        // Break, if tile on the line is occupied; cannot go past that piece!
                        break;
                    }   
                }
            }
        }
        return Collections.unmodifiableList(legalMoves);
    }
    
    private static boolean isFirstColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.FIRST_COLUMN[currentPosition] && (candidateOffset == -9 || candidateOffset == 7);
    }
     
    private static boolean isEighthColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.EIGHTH_COLUMN[currentPosition] && (candidateOffset == -7 || candidateOffset == 9);
    }
}
