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


public class Rook extends Piece {
    private final static int[] CANDIDATE_MOVE_VECTOR_COORDINATES = {-8, -1, 1, 8};

    public Rook(int piecePosition, Alliance pieceAlliance) {
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
                        legalMoves.add(new Move.MajorMove(board, this, candidateDestinationCoordinate));
                    } else {
                        if (this.pieceAlliance != destinationTile.getPiece().getPieceAlliance()) {
                            legalMoves.add(new Move.AttackMove(board, this, candidateDestinationCoordinate, destinationTile.getPiece()));
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
        return BoardUtils.FIRST_COLUMN[currentPosition] && candidateOffset == -1;
    }
     
    private static boolean isEighthColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.EIGHTH_COLUMN[currentPosition] && candidateOffset == 1;
    }
}
