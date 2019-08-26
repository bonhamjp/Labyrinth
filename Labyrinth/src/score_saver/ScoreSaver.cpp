#include "Settings.h"

#include "ScoreSaver.h"

#include <iostream>
#include <fstream> 

namespace Labyrinth
{
	void CreateScoreFile()
	{
		std::ofstream scoreFile(SAVE_FILE_NAME);

		scoreFile.close();
	}

	void SaveScore(double runTime)
	{
		if (!std::ifstream(SAVE_FILE_NAME).good())
		{
			CreateScoreFile();
		}

		std::ofstream scoreFile(SAVE_FILE_NAME);

		scoreFile << "Labyrinth " << MAP_COLUMNS << " x " << MAP_ROWS << ": ";
		scoreFile << runTime << " seconds." << std::endl;

		scoreFile.close();
	}
}
