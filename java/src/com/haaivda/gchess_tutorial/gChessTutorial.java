package com.haaivda.gchess_tutorial;

import com.haaivda.gchess_tutorial.board.Board;

/**
 *
 * @author Gerald van Dalen
 */
public class gChessTutorial {

    public static void main(String[] args) {
        Board board = Board.createStandardBoard();
        
        System.out.println(board);
    }    
}
