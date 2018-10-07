package com.haaivda.gchess_tutorial;

import com.haaivda.gchess_tutorial.engine.board.Board;
import com.haaivda.gchess_tutorial.gui.Table;

public class gChessTutorial {

    public static void main(String[] args) {
        Board board = Board.createStandardBoard();
        
        System.out.println(board);

        Table table = new Table();
    }    
}
