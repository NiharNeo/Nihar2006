import tkinter as tk
from tkinter import messagebox
import random


class TicTacToe(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Tic-Tac-Toe")
        self.current_player = 'X'
        self.ai_player = 'O'
        self.human_player = 'X'
        self.scores = {'X': 0, 'O': 0}
        self.player_names = {'X': 'Player 1', 'O': 'AI'}
        self.buttons = [[None, None, None],
                        [None, None, None],
                        [None, None, None]]
        self.board = [[' ', ' ', ' '],
                      [' ', ' ', ' '],
                      [' ', ' ', ' ']]
        self.create_widgets()
        self.ai_mode = True  # Set True if playing against AI

    def create_widgets(self):
        self.name_frame = tk.Frame(self)
        self.name_frame.grid(row=0, column=0, columnspan=3)

        tk.Label(self.name_frame, text="Player X: ").pack(side=tk.LEFT)
        self.player_x_name = tk.Entry(self.name_frame)
        self.player_x_name.pack(side=tk.LEFT)
        self.player_x_name.insert(0, "Player 1")

        self.score_label = tk.Label(self, text="Scores: Player 1 (X) 0 - 0 AI (O)")
        self.score_label.grid(row=1, column=0, columnspan=3)

        for i in range(3):
            for j in range(3):
                button = tk.Button(self, text=' ', font=('normal', 40), width=5, height=2,
                                   command=lambda row=i, col=j: self.on_button_click(row, col))
                button.grid(row=i + 2, column=j)
                self.buttons[i][j] = button

        self.restart_button = tk.Button(self, text='Restart', command=self.reset_game)
        self.restart_button.grid(row=5, column=0, columnspan=3)

    def on_button_click(self, row, col):
        if self.board[row][col] == ' ' and self.current_player == self.human_player:
            self.make_move(row, col)
            if not self.check_win() and not self.check_draw():
                if self.ai_mode:
                    self.ai_move()

    def make_move(self, row, col):
        if self.board[row][col] == ' ':
            self.board[row][col] = self.current_player
            self.buttons[row][col].config(text=self.current_player)
            if self.check_win():
                self.scores[self.current_player] += 1
                messagebox.showinfo("Tic-Tac-Toe", f"{self.get_current_player_name()} wins!")
                self.update_scores()
                self.reset_game()
            elif self.check_draw():
                messagebox.showinfo("Tic-Tac-Toe", "The game is a draw!")
                self.reset_game()
            else:
                self.switch_player()

    def switch_player(self):
        self.current_player = 'O' if self.current_player == 'X' else 'X'

    def check_win(self):
        for i in range(3):
            if self.board[i][0] == self.board[i][1] == self.board[i][2] == self.current_player:
                return True
            if self.board[0][i] == self.board[1][i] == self.board[2][i] == self.current_player:
                return True
        if self.board[0][0] == self.board[1][1] == self.board[2][2] == self.current_player:
            return True
        if self.board[0][2] == self.board[1][1] == self.board[2][0] == self.current_player:
            return True
        return False

    def check_draw(self):
        for row in self.board:
            if ' ' in row:
                return False
        return True

    def reset_game(self):
        self.board = [[' ', ' ', ' '],
                      [' ', ' ', ' '],
                      [' ', ' ', ' ']]
        for i in range(3):
            for j in range(3):
                self.buttons[i][j].config(text=' ')
        self.current_player = 'X'
        if self.ai_mode and self.current_player == self.ai_player:
            self.ai_move()

    def update_scores(self):
        self.player_names['X'] = self.player_x_name.get()
        self.score_label.config(
            text=f"Scores: {self.player_names['X']} (X) {self.scores['X']} - {self.scores['O']} {self.player_names['O']} (O)")

    def get_current_player_name(self):
        return self.player_names[self.current_player]

    def ai_move(self):
        best_score = float('-inf')
        best_move = None
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == ' ':
                    self.board[i][j] = self.ai_player
                    score = self.minimax(self.board, 0, False)
                    self.board[i][j] = ' '
                    if score > best_score:
                        best_score = score
                        best_move = (i, j)
        if best_move:
            self.make_move(best_move[0], best_move[1])

    def minimax(self, board, depth, is_maximizing):
        if self.check_winner(self.ai_player):
            return 1
        elif self.check_winner(self.human_player):
            return -1
        elif self.check_draw():
            return 0

        if is_maximizing:
            best_score = float('-inf')
            for i in range(3):
                for j in range(3):
                    if board[i][j] == ' ':
                        board[i][j] = self.ai_player
                        score = self.minimax(board, depth + 1, False)
                        board[i][j] = ' '
                        best_score = max(score, best_score)
            return best_score
        else:
            best_score = float('inf')
            for i in range(3):
                for j in range(3):
                    if board[i][j] == ' ':
                        board[i][j] = self.human_player
                        score = self.minimax(board, depth + 1, True)
                        board[i][j] = ' '
                        best_score = min(score, best_score)
            return best_score

    def check_winner(self, player):
        for i in range(3):
            if self.board[i][0] == self.board[i][1] == self.board[i][2] == player:
                return True
            if self.board[0][i] == self.board[1][i] == self.board[2][i] == player:
                return True
        if self.board[0][0] == self.board[1][1] == self.board[2][2] == player:
            return True
        if self.board[0][2] == self.board[1][1] == self.board[2][0] == player:
            return True
        return False


if __name__ == "__main__":
    app = TicTacToe()
    app.mainloop()
