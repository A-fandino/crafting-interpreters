package com.craftinginterpreters.lox;

class BreakException extends RuntimeError {
    BreakException(Token token) {
        super(token, "Unexpected break statment outside a loop.");
    }
}
