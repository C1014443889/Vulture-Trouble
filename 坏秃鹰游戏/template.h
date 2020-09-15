#ifndef _H_APP
#define _H_APP

// Link to AGK libraries
#include "agk.h"

// Global values for the app
class app
{
	public:

		// main vars

	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// main app functions
		void Begin( void );
		void Loop( void );
		void End( void );

		void displayTitle();
		void hideTitle();
		void displayIntro();
		void hideIntro();
		void playGame();;
		void vultrueMove();
		void basketMove();
		void eggMove();
		void checkCollision();
		void showHitBasket();
		void resetEgg();
		void showBrokenEgg();
		void showGameOver();
		void hideGameOver();
		void displaySummary();
		void hideSummary();
		void hideGame();
		
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif
