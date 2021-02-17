#pragma once

#include <SFML/Graphics.hpp>
#include "src/hpp/State.hpp"
#include "src/hpp/Game.hpp"

namespace hgw
{
	struct Move
	{
		Move(int c, int r);
		Move();
		int col, row;
	};

	class GameState1P : public State
	{
	public:
		GameState1P(GameDataRef data, int diff);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:

		void InitGridPieces();
		void CheckAndPlacePiece();
		void CheckPlayerHasWon(int player);
		void Check3PiecesForMatch(int x1, int y1, int x2,
			int y2, int x3, int y3, int pieceToCheck);
		void FadeGame();
		void FadeWin();

		int Random(int min, int max);

		Move MakeMove_AiEasy();
		Move MakeMove_AiMedium();
		Move MakeMove_AiImpossible();

		int MinMax(int grid[3][3], int depth, bool isMax);
		int Evaluate(int grid[3][3]);
		bool AreMovesLeft(int grid[3][3]);
		Move FindBestMove(int grid[3][3]);

		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[3][3];
		sf::Sprite _winningPieces[3];

		int gridArray[3][3];
		int oppacity[3][3] = {0};
		bool isFading[3][3] = { false };
		int playerWinningPieces[3][2]; //never again passing x1, y1, x2...

		int winOppacity = 0;
		bool isWinFading = false;

		int turn;
		int gameState;
		
		int difficulty;

		sf::Clock _clock;
		sf::Clock _aiClock;
		sf::Clock _winClock;

		Move aiMove;
	};

	
}
