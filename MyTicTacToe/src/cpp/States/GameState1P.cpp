#include <sstream>
#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <algorithm>

#include "src/hpp/DEFINITIONS.hpp"

#include "src/hpp/States/GameState1P.hpp"
#include "src/hpp/States/PauseState.hpp"
#include "src/hpp/States/GameOverState.hpp"

namespace hgw
{
	Move::Move(int c, int r) : col(c), row(r)
	{

	}

	Move::Move()
	{

	}

	GameState1P::GameState1P(GameDataRef data, int diff) : _data(data), difficulty(diff)
	{

	}

	void GameState1P::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width,
			_pauseButton.getPosition().y);
		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

		InitGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				gridArray[x][y] = EMPTY_PIECE;
			}
		}
	}

	void GameState1P::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_pauseButton, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.ClickSound1);
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.IsSpriteClicked(this->_gridSprite, event.type, this->_data->window) && 
				turn == PLAYER_PIECE)
			{
				if (STATE_PLAYING == gameState)
				{
					this->CheckAndPlacePiece();
				}
			}
		}
	}

	void GameState1P::Update(float dt)
	{
		this->FadeGame();
		this->FadeWin();

		if (gameState == STATE_WON || gameState == STATE_LOSE || gameState == STATE_DRAW)
		{
			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAMEOVER)
			{
				this->_data->machine.AddState(StateRef(new GameOverState(_data, gameState, true, difficulty)), true);
			}
		}

		if (turn == AI_PIECE && this->_aiClock.getElapsedTime().asSeconds() > AI_FAKE_TIME)
		{
			this->_data->sounds.Play(this->_data->sounds.GridClickSound);

			gridArray[aiMove.col][aiMove.row] = AI_PIECE;
			_gridPieces[aiMove.col][aiMove.row].setTexture(this->_data->assets.GetTexture("O Piece"));
			_gridPieces[aiMove.col][aiMove.row].setColor(sf::Color(255, 255, 255, 0));
			this->isFading[aiMove.col][aiMove.row] = true;
			this->CheckPlayerHasWon(turn);

			turn = PLAYER_PIECE;
		}
	}

	void GameState1P::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
			this->_data->window.draw(this->_winningPieces[x]);
		}

		this->_data->window.display();
	}

	void GameState1P::InitGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				//_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x +
					(tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y +
					(tempSpriteSize.y * y) - 7);
				//_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState1P::CheckAndPlacePiece()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2,
			(SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x,
			touchPoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column, row;

		if (gridLocalTouchPos.x < gridSectionSize.x)
		{
			column = 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2)
		{
			column = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width)
		{
			column = 3;
		}

		if (gridLocalTouchPos.y < gridSectionSize.y)
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2)
		{
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height)
		{
			row = 3;
		}

		if (gridArray[column - 1][row - 1] == EMPTY_PIECE)
		{
			gridArray[column - 1][row - 1] = turn;

			this->_data->sounds.Play(this->_data->sounds.GridClickSound);

			_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));
			this->CheckPlayerHasWon(turn);
			this->isFading[column - 1][row - 1] = true;
			//_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));

			if (gameState != STATE_DRAW && gameState != STATE_LOSE && gameState != STATE_WON)
			{
				turn = AI_PIECE;

				switch (difficulty)
				{
				case AI_DIFFICULTY_EASY:
					aiMove = MakeMove_AiEasy();
					break;
				case AI_DIFFICULTY_MEDIUM:
					aiMove = MakeMove_AiMedium();
					break;
				case AI_DIFFICULTY_IMPOSSIBLE:
					aiMove = MakeMove_AiImpossible();
					break;
				}

				this->_aiClock.restart();
			}
		}
	}

	void GameState1P::CheckPlayerHasWon(int player)
	{
		int emptyNum = 9;
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (EMPTY_PIECE != gridArray[x][y])
				{
					emptyNum--;
				}
			}
		}

		if ((emptyNum == 0) && (gameState != STATE_WON) && (gameState != STATE_LOSE))
		{
			gameState = STATE_DRAW;
		}

		if (gameState == STATE_DRAW || gameState == STATE_LOSE || gameState == STATE_WON)
		{
			this->_clock.restart();
		}

		std::cout << gameState << std::endl;
	}

	void GameState1P::Check3PiecesForMatch(int x1, int y1, int x2,
		int y2, int x3, int y3, int pieceToCheck)
	{
		if (pieceToCheck == gridArray[x1][y1] &&
			pieceToCheck == gridArray[x2][y2] &&
			pieceToCheck == gridArray[x3][y3] &&
			gameState != STATE_DRAW && gameState != STATE_WON && gameState != STATE_LOSE)
		{
			std::string winningPieceStr;

			if (O_PIECE == pieceToCheck)
			{
				winningPieceStr = "O Winning Piece";
			}
			else
			{
				winningPieceStr = "X Winning Piece";
			}

			this->playerWinningPieces[0][0] = x1;
			this->playerWinningPieces[0][1] = y1;
			this->playerWinningPieces[1][0] = x2;
			this->playerWinningPieces[1][1] = y2;
			this->playerWinningPieces[2][0] = x3;
			this->playerWinningPieces[2][1] = y3;

			this->isWinFading = true;

			if (pieceToCheck == PLAYER_PIECE)
			{
				gameState = STATE_WON;
			}
			else
			{
				gameState = STATE_LOSE;
			}
		}
	}
	
	int GameState1P::Random(int min, int max)
	{
		//sprobwoav static pozniej
		unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed);
		std::uniform_int_distribution<int> range(min, max);
		return range(generator);
	}

	Move GameState1P::MakeMove_AiEasy()
	{
		int x, y;
		do
		{
			x = Random(0, 2);
			y = Random(0, 2);
		} while (gridArray[x][y] != EMPTY_PIECE);
		//gridArray[x][y] = AI_PIECE;
		//_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("O Piece"));
		return Move(x, y);
	}

	Move GameState1P::MakeMove_AiMedium()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (gridArray[i][j] == EMPTY_PIECE)
				{
					gridArray[i][j] = PLAYER_PIECE;

					if (Evaluate(gridArray) == -10)
					{
						//gridArray[i][j] = AI_PIECE;
						//_gridPieces[i][j].setTexture(this->_data->assets.GetTexture("O Piece"));
						//to exit the function quickly
						return Move(i, j);
					}
					else
					{
						gridArray[i][j] = EMPTY_PIECE;
					}
				}
			}
		}

		int x, y;

		do
		{
			x = Random(0, 2);
			y = Random(0, 2);
		} while (gridArray[x][y] != EMPTY_PIECE);

		//gridArray[x][y] = AI_PIECE;
		//_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("O Piece"));

		return Move(x, y);
	}

	Move GameState1P::MakeMove_AiImpossible()
	{
		Move bestMove = FindBestMove(gridArray);

		//gridArray[bestMove.row][bestMove.col] = AI_PIECE;

		//_gridPieces[bestMove.row][bestMove.col].setTexture(this->_data->assets.GetTexture("O Piece"));

		return Move(bestMove.row, bestMove.col);

	}

	Move GameState1P::FindBestMove(int grid[3][3])
	{
		Move bestMove(-1,-1);

		int bestMoveVal = -1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (grid[i][j] == EMPTY_PIECE)
				{
					grid[i][j] = AI_PIECE;

					int moveVal = MinMax(grid, 0, false);

					grid[i][j] = EMPTY_PIECE;

					if (bestMoveVal < moveVal)
					{
						bestMoveVal = moveVal;
						bestMove.row = i;
						bestMove.col = j;
					}
				}
			}
		}

		return bestMove;
	}

	int GameState1P::MinMax(int grid[3][3], int depth, bool isMax)
	{
		int score = Evaluate(grid);

		//return if AI won
		if (score == 10)
		{
			return 10 - depth;
		}

		//return if Player won
		if (score == -10)
		{
			return -10 + depth;
		}

		//return if draw occured
		if (AreMovesLeft(grid) == false)
		{
			return 0;
		}

		if (isMax)
		{
			int bestVal = -1000;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (grid[i][j] == EMPTY_PIECE)
					{
						grid[i][j] = AI_PIECE;

						bestVal = std::max(bestVal, MinMax(grid, depth + 1, !isMax));

						grid[i][j] = EMPTY_PIECE;
					}
				}
			}

			return bestVal;
		}
		else
		{
			int bestVal = 1000;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (grid[i][j] == EMPTY_PIECE)
					{
						grid[i][j] = PLAYER_PIECE;

						bestVal= std::min(bestVal, MinMax(grid, depth + 1, !isMax));

						grid[i][j] = EMPTY_PIECE;
					}
				}
			}

			return bestVal;
		}
	}

	int GameState1P::Evaluate(int grid[3][3])
	{
		for (int i = 0; i < 3; i++)
		{
			if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
			{
				if (grid[i][0] == AI_PIECE)
				{
					return 10;
				}
				else if (grid[i][0] == PLAYER_PIECE)
				{
					return -10;
				}
			}
			
			if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
			{
				if (grid[0][i] == AI_PIECE)
				{
					return 10;
				}
				else if (grid[0][i] == PLAYER_PIECE)
				{
					return -10;
				}
			}
		}

		if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
		{
			if (grid[0][0] == AI_PIECE)
			{
				return 10;
			}
			else if (grid[0][0] == PLAYER_PIECE)
			{
				return -10;
			}
		}

		if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
		{
			if (grid[0][2] == AI_PIECE)
			{
				return 10;
			}
			else if (grid[0][2] == PLAYER_PIECE)
			{
				return -10;
			}
		}

		return 0;
	}

	bool GameState1P::AreMovesLeft(int grid[3][3])
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (grid[i][j] == EMPTY_PIECE)
				{
					return true;
				}
			}
		}

		return false;
	}

	void GameState1P::FadeGame()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (this->isFading[i][j])
				{
					_gridPieces[i][j].setColor(sf::Color(255, 255, 255, oppacity[i][j] += 6));
					if (static_cast<int>(_gridPieces[i][j].getColor().a) >= 249)
					{
						_gridPieces[i][j].setColor(sf::Color(255, 255, 255, 255));
						this->isFading[i][j] = false;
					}
				}
			}
		}
	}

	void GameState1P::FadeWin()
	{
		if (isWinFading)
		{
			winOppacity += 6;
			for (int i = 0; i < 3; i++)
			{
				this->playerWinningPieces[i];
				_winningPieces[i].setPosition(_gridPieces[playerWinningPieces[i][0]][playerWinningPieces[i][1]].getPosition());
				if (gameState == STATE_WON)
				{
					_winningPieces[i].setTexture(this->_data->assets.GetTexture("X Winning Piece"));
				}
				else if (gameState == STATE_LOSE)
				{
					_winningPieces[i].setTexture(this->_data->assets.GetTexture("O Winning Piece"));
				}
			}

			_winningPieces[0].setColor(sf::Color(255, 255, 255, winOppacity));
			_winningPieces[1].setColor(sf::Color(255, 255, 255, winOppacity));
			_winningPieces[2].setColor(sf::Color(255, 255, 255, winOppacity));
			if (static_cast<int>(_winningPieces[0].getColor().a) >= 249)
			{
				_winningPieces[0].setColor(sf::Color(255, 255, 255, 255));
				_winningPieces[1].setColor(sf::Color(255, 255, 255, 255));
				_winningPieces[2].setColor(sf::Color(255, 255, 255, 255));
				this->isWinFading = false;
			}
		}

		
	}

}