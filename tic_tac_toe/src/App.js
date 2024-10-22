import React, { useState } from "react";
import "./App.css";

function App() {
  const [history, setHistory] = useState([Array(9).fill(null)]);
  const [currentMove, setCurrentMove] = useState(0);
  const [isXTurn, setIsXTurn] = useState(true);

  const currentBoard = history[currentMove];

  const handleClick = (index) => {
    if (currentBoard[index] || checkWinner(currentBoard)) return;
    const newHistory = history.slice(0, currentMove + 1);
    const newBoard = currentBoard.slice();
    newBoard[index] = isXTurn ? "X" : "O";
    setHistory([...newHistory, newBoard]);
    setCurrentMove(newHistory.length);
    setIsXTurn(!isXTurn);
  };

  const checkWinner = (board) => {
    const lines = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8],
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8],
      [0, 4, 8],
      [2, 4, 6],
    ];
    for (let line of lines) {
      const [a, b, c] = line;
      if (board[a] && board[a] === board[b] && board[a] === board[c]) {
        return board[a];
      }
    }
    return null;
  };

  const winner = checkWinner(currentBoard);

  const handleReset = () => {
    setHistory([Array(9).fill(null)]);
    setCurrentMove(0);
    setIsXTurn(true);
  };

  const jumpTo = (move) => {
    setCurrentMove(move);
    setIsXTurn(move % 2 === 0);
  };

  const moves = history.slice(1).map((_, index) => (
    <li key={index + 1}>
      <button onClick={() => jumpTo(index + 1)}>
        Go to move #{index + 1}
      </button>
    </li>
  ));

  return (
    <div className="App">
      <h1>Tic Tac Toe</h1>
      <div className="game-container">
        <div className="game-board">
          <div className="board">
            {currentBoard.map((cell, index) => (
              <button 
                key={index} 
                onClick={() => handleClick(index)} 
                className={`cell ${cell ? 'filled' : ''}`}
              >
                {cell}
              </button>
            ))}
          </div>
        </div>
        <div className="game-info">
          <div className="status">
            {winner
              ? `Winner: ${winner}`
              : currentMove === 9
              ? "It's a draw!"
              : `Next Player: ${isXTurn ? "X" : "O"}`}
          </div>
          <ol>{moves}</ol>
        </div>
      </div>
      <button onClick={handleReset} className="reset-btn">
        Restart Game
      </button>
    </div>
  );
}

export default App;