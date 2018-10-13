package com.haaivda.gchess_tutorial.engine.player;

import com.haaivda.gchess_tutorial.engine.board.Board;
import com.haaivda.gchess_tutorial.engine.board.Move;

public class MoveTransition {
    private final Board transitionBoard;
    private final Move move; // TODO: is this class parameter needed?
    private final MoveStatus moveStatus;

    MoveTransition(Board transitionBoard, Move move, MoveStatus moveStatus) {
        this.transitionBoard = transitionBoard;
        this.move = move;
        this.moveStatus = moveStatus;
    }

    public MoveStatus getMoveStatus() {
        return this.moveStatus;
    }

    public Board getTransitionBoard() {
        return this.transitionBoard;
    }
}
