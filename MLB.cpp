#include "MLB_Stats.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include "Fields.h"
#include "sort.h"

annual_stats* doInsertionSort(annual_stats* year_stats, int num_years, const std::vector<std::string>& args);
annual_stats* doMergeSort(annual_stats* year_stats, int num_years, const std::vector<std::string>& args);

void doFind(annual_stats* year_stats, const std::vector<std::string>& args);

int main()
{
	int num_years;
	std::cin >> num_years;

	annual_stats* year_stats = new annual_stats[num_years];

	for (int i = 0; i < num_years; i++)
	{
		std::cin >> year_stats[i].year;
		std::cin >> year_stats[i].no_teams;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		year_stats[i].stats = new mlb_stats[year_stats[i].no_teams];
		for (int t = 0; t < year_stats[i].no_teams; t++)
		{
			mlb_stats* stats = &year_stats[i].stats[t];

			std::cin.getline(stats->Team, TEAM_NAME_LEN, '\t');
			stats->Team[TEAM_NAME_LEN - 1] = 0;

			std::cin.getline(stats->League, LEAGUE_NAME, '\t');
			stats->League[LEAGUE_NAME - 1] = 0;

			std::cin >> stats->G >> stats->AB >> stats->R >> stats->H >> stats->B2 >> stats->B3 >> stats->HR >> stats->RBI >> stats->BB >> stats->SO >> stats->SB >> stats->CS >> stats->AVG >> stats->OBP >> stats->SLG >> stats->OPS;

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	}

	int num_commands;
	std::cin >> num_commands;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (int i = 0; i < num_commands; i++)
	{
		std::string cmd;
		std::getline(std::cin, cmd);
		std::vector<std::string> args;
		std::istringstream ss(cmd);

		do
		{
			args.emplace_back();
		}
		while (std::getline(ss, args.back(), ' '));
		args.pop_back();

		if (args.back().back() == '\r')
			args.back().erase(args.back().size() - 1);

		if (args[0] == "isort" && args.size() == 4)
		{
			annual_stats* sorted = doInsertionSort(year_stats, num_years, args);
			if (sorted == NULL)
				continue;

			std::cout << "Team\t" << args[2] << '\n';

			if (isStringField(args[2]))
			{
				if (args[2] == "Team")
				{
					printTeamsField(sorted->stats, sorted->no_teams, stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]));
				}
				else
				{
					printTeamsField(sorted->stats, sorted->no_teams, stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]));
				}
			}
			else if (isIntField(args[2]))
			{
				printTeamsField(sorted->stats, sorted->no_teams, stringToField<int mlb_stats::*>(args[2]));
			}
			else if (isFloatField(args[2]))
			{
				printTeamsField(sorted->stats, sorted->no_teams, stringToField<float mlb_stats::*>(args[2]));
			}
		}
		else if (args[0] == "msort" && args.size() == 4)
		{
			annual_stats* sorted = doMergeSort(year_stats, num_years, args);
			if (sorted == NULL)
				continue;

			std::cout << "Team\t" << args[2] << '\n';

			if (isStringField(args[2]))
			{
				if (args[2] == "Team")
				{
					printTeamsField(sorted->stats, sorted->no_teams, stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]));
				}
				else
				{
					printTeamsField(sorted->stats, sorted->no_teams, stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]));
				}
			}
			else if (isIntField(args[2]))
			{
				printTeamsField(sorted->stats, sorted->no_teams, stringToField<int mlb_stats::*>(args[2]));
			}
			else if (isFloatField(args[2]))
			{
				printTeamsField(sorted->stats, sorted->no_teams, stringToField<float mlb_stats::*>(args[2]));
			}
		}
		else if (args[0] == "ifind")
		{
			annual_stats* sorted = doInsertionSort(year_stats, num_years, args);
			if (sorted == NULL)
				continue;
			doFind(sorted, args);
		}
		else if (args[0] == "mfind")
		{
			annual_stats* sorted = doMergeSort(year_stats, num_years, args);
			if (sorted == NULL)
				continue;
			doFind(sorted, args);
		}
		else if (args[0] == "isort" && args.size() == 6)
		{
			// allocate a new mlb_stats array, large enough to hold the stats from each year
			// fill it with stats from each year
			// then perform sort on it

			int startYear = std::stoi(args[2]);
			int endYear = std::stoi(args[3]);

			int startIdx = 0;
			int endIdx = 0;

			for (int i = 0; i < num_years; i++)
			{
				if (year_stats[i].year == startYear)
				{
					startIdx = i;
				}
				else if (year_stats[i].year == endYear)
				{
					endIdx = i;
					break;
				}
			}

			int totalStats = 0;
			for (int i = startIdx; i <= endIdx; i++)
			{
				totalStats += year_stats[i].no_teams;
			}

			mlb_stats* allYears = new mlb_stats[totalStats];
			int* years = new int[totalStats];

			int copyOffset = 0;
			for (int i = startIdx; i <= endIdx; i++)
			{
				std::memcpy(&allYears[copyOffset], year_stats[i].stats, year_stats[i].no_teams * sizeof(mlb_stats));
				for (int j = copyOffset; j < copyOffset + year_stats[i].no_teams; j++)
					years[j] = year_stats[i].year;
				copyOffset += year_stats[i].no_teams;
			}

			if (isStringField(args[4]))
			{
				if (args[5] == "decr")
				{
					if (args[4] == "Team")
					{
						insertionSort(allYears, totalStats, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
					}
					else
					{
						insertionSort(allYears, totalStats, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
					}
				}
				else
				{
					if (args[4] == "Team")
					{
						insertionSort(allYears, totalStats, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
					}
					else
					{
						insertionSort(allYears, totalStats, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
					}
				}
			}
			else if (isIntField(args[4]))
			{
				if (args[5] == "decr")
				{
					insertionSort(allYears, totalStats, stringToField<int mlb_stats::*>(args[4]), std::less<int>{});
				}
				else
				{
					insertionSort(allYears, totalStats, stringToField<int mlb_stats::*>(args[4]), std::greater<int>{});
				}
			}
			else if (isFloatField(args[4]))
			{
				if (args[5] == "decr")
				{
					insertionSort(allYears, totalStats, stringToField<float mlb_stats::*>(args[4]), std::less<float>{});
				}
				else
				{
					insertionSort(allYears, totalStats, stringToField<float mlb_stats::*>(args[4]), std::greater<float>{});
				}
			}
			else
			{
				std::cout << "Error: no such field \n";
				continue;
			}

			std::cout << "Year\tTeam\t" << args[2] << '\n';

			if (isStringField(args[2]))
			{
				if (args[2] == "Team")
					printTeamsFieldWithYear(allYears, years, totalStats, stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]));
				else
					printTeamsFieldWithYear(allYears, years, totalStats, stringToField<char (mlb_stats::*)[LEAGUE_NAME]>(args[2]));
			}
			else if (isIntField(args[2]))
			{
				printTeamsFieldWithYear(allYears, years, totalStats, stringToField<int mlb_stats::*>(args[2]));
			}
			else if (isFloatField(args[2]))
			{
				printTeamsFieldWithYear(allYears, years, totalStats, stringToField<float mlb_stats::*>(args[2]));
			}

			delete[] allYears;
			delete[] years;
		}
		else if (args[0] == "msort" && args.size() == 6)
		{
			// allocate a new mlb_stats array, large enough to hold the stats from each year
			// fill it with stats from each year
			// then perform sort on it
			int startYear = std::stoi(args[2]);
			int endYear = std::stoi(args[3]);

			int startIdx = 0;
			int endIdx = 0;

			for (int i = 0; i < num_years; i++)
			{
				if (year_stats[i].year == startYear)
				{
					startIdx = i;
				}
				else if (year_stats[i].year == endYear)
				{
					endIdx = i;
					break;
				}
			}

			int totalStats = 0;
			for (int i = startIdx; i <= endIdx; i++)
			{
				totalStats += year_stats[i].no_teams;
			}

			mlb_stats* allYears = new mlb_stats[totalStats];
			int* years = new int[totalStats];

			int copyOffset = 0;
			for (int i = startIdx; i <= endIdx; i++)
			{
				std::memcpy(&allYears[copyOffset], year_stats[i].stats, year_stats[i].no_teams * sizeof(mlb_stats));
				for (int j = copyOffset; j < copyOffset + year_stats[i].no_teams; j++)
					years[j] = year_stats[i].year;
				copyOffset += year_stats[i].no_teams;
			}

			if (isStringField(args[4]))
			{
				if (args[5] == "decr")
				{
					if (args[4] == "Team")
					{
						mergeSort(allYears, totalStats, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
					}
					else
					{
						mergeSort(allYears, totalStats, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
					}
				}
				else
				{
					if (args[4] == "Team")
					{
						mergeSort(allYears, totalStats, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
					}
					else
					{
						mergeSort(allYears, totalStats, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
					}
				}
			}
			else if (isIntField(args[4]))
			{
				if (args[5] == "decr")
				{
					mergeSort(allYears, totalStats, stringToField<int mlb_stats::*>(args[4]), std::less<int>{});
				}
				else
				{
					mergeSort(allYears, totalStats, stringToField<int mlb_stats::*>(args[4]), std::greater<int>{});
				}
			}
			else if (isFloatField(args[4]))
			{
				if (args[5] == "decr")
				{
					mergeSort(allYears, totalStats, stringToField<float mlb_stats::*>(args[4]), std::less<float>{});
				}
				else
				{
					mergeSort(allYears, totalStats, stringToField<float mlb_stats::*>(args[4]), std::greater<float>{});
				}
			}
			else
			{
				std::cout << "Error: no such field \n";
				continue;
			}

			std::cout << "Year\tTeam\t" << args[2] << '\n';

			if (isStringField(args[2]))
			{
				if (args[2] == "Team")
				{
					printTeamsFieldWithYear(allYears, years, totalStats, stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]));
				}
				else
				{
					printTeamsFieldWithYear(allYears, years, totalStats, stringToField<char (mlb_stats::*)[LEAGUE_NAME]>(args[2]));
				}
			}
			else if (isIntField(args[2]))
			{
				printTeamsFieldWithYear(allYears, years, totalStats, stringToField<int mlb_stats::*>(args[2]));
			}
			else if (isFloatField(args[2]))
			{
				printTeamsFieldWithYear(allYears, years, totalStats, stringToField<float mlb_stats::*>(args[2]));
			}

			delete[] allYears;
			delete[] years;
		}

		std::cout << '\n';
	}

	for (int i = 0; i < num_years; i++)
	{
		delete[] year_stats[i].stats;
	}
	delete[] year_stats;

	return 0;
}

annual_stats* doInsertionSort(annual_stats* year_stats, int num_years, const std::vector<std::string>& args)
{
	int year_to_sort = std::stoi(args[1]);

	annual_stats*sort_target = NULL;
	for (int j = 0; j < num_years; j++)
	{
		if (year_stats[j].year == year_to_sort)
		{
			sort_target = &year_stats[j];
			break;
		}
	}
	if (sort_target == NULL)
	{
		std::cout << "Error: no such year \n";
		return NULL;
	}
	if (isStringField(args[2]))
	{
		if (args[3] == "decr")
		{
			if (args[2] == "Team")
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
			}
			else
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
			}
		}
		else
		{
			if (args[2] == "Team")
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
			}
			else
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
			}
		}
	}
	else if (isIntField(args[2]))
	{
		if (args[3] == "decr")
		{
			insertionSort(sort_target->stats, sort_target->no_teams, stringToField<int mlb_stats::*>(args[2]), std::less<int>{});
		}
		else
		{
			insertionSort(sort_target->stats, sort_target->no_teams, stringToField<int mlb_stats::*>(args[2]), std::greater<int>{});
		}
	}
	else if (isFloatField(args[2]))
	{
		if (args[3] == "decr")
		{
			insertionSort(sort_target->stats, sort_target->no_teams, stringToField<float mlb_stats::*>(args[2]), std::less<float>{});
		}
		else
		{
			insertionSort(sort_target->stats, sort_target->no_teams, stringToField<float mlb_stats::*>(args[2]), std::greater<float>{});
		}
	}
	else
	{
		std::cout << "Error: no such field \n";
		return NULL;
	}

	return sort_target;
}

annual_stats* doMergeSort(annual_stats* year_stats, int num_years, const std::vector<std::string>& args)
{
	int year_to_sort = std::stoi(args[1]);

	annual_stats*sort_target = NULL;
	for (int j = 0; j < num_years; j++)
	{
		if (year_stats[j].year == year_to_sort)
		{
			sort_target = &year_stats[j];
			break;
		}
	}
	if (sort_target == NULL)
	{
		std::cout << "Error: no such year \n";
		return NULL;
	}
	if (isStringField(args[2]))
	{
		if (args[3] == "decr")
		{
			if (args[2] == "Team")
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
			}
			else
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) < 0; });
			}
		}
		else
		{
			if (args[2] == "Team")
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::Team, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
			}
			else
			{
				mergeSort(sort_target->stats, sort_target->no_teams, &mlb_stats::League, [](const char* lhs, const char* rhs) { return std::strcmp(lhs, rhs) > 0; });
			}
		}
	}
	else if (isIntField(args[2]))
	{
		if (args[3] == "decr")
		{
			mergeSort(sort_target->stats, sort_target->no_teams, stringToField<int mlb_stats::*>(args[2]), std::less<int>{});
		}
		else
		{
			mergeSort(sort_target->stats, sort_target->no_teams, stringToField<int mlb_stats::*>(args[2]), std::greater<int>{});
		}
	}
	else if (isFloatField(args[2]))
	{
		if (args[3] == "decr")
		{
			mergeSort(sort_target->stats, sort_target->no_teams, stringToField<float mlb_stats::*>(args[2]), std::less<float>{});
		}
		else
		{
			mergeSort(sort_target->stats, sort_target->no_teams, stringToField<float mlb_stats::*>(args[2]), std::greater<float>{});
		}
	}
	else
	{
		std::cout << "Error: no such field \n";
		return NULL;
	}

	return sort_target;
}

void doFind(annual_stats* year_stats, const std::vector<std::string>& args)
{
	if (args[3] == "max")
	{
		if (isStringField(args[2]))
		{
			std::cout << "Team\t" << args[2] << '\n';

			if (args[2] == "Team")
			{
				auto field = stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]);
				mlb_stats* team = &year_stats->stats[0];

				std::cout << team->Team << "\t" << team->*field << '\n';
			}
			else
			{
				auto field = stringToField<char (mlb_stats::*)[LEAGUE_NAME]>(args[2]);
				mlb_stats* team = &year_stats->stats[0];

				std::cout << team->Team << "\t" << team->*field << '\n';
			}
		}
		else if (isIntField(args[2]))
		{
			int mlb_stats::* field = stringToField<int mlb_stats::*>(args[2]);
			mlb_stats* team = &year_stats->stats[year_stats->no_teams - 1];

			std::cout << "Team\t" << args[2] << '\n';
			std::cout << team->Team << "\t" << team->*field << '\n';
		}
		else if (isFloatField(args[2]))
		{
			float mlb_stats::* field = stringToField<float mlb_stats::*>(args[2]);
			mlb_stats* team = &year_stats->stats[year_stats->no_teams - 1];

			std::cout << "Team\t" << args[2] << '\n';
			std::cout << team->Team << "\t" << team->*field << '\n';
		}
	}
	else if (args[3] == "min")
	{
		if (isStringField(args[2]))
		{
			std::cout << "Team\t" << args[2] << '\n';

			if (args[2] == "Team")
			{
				auto field = stringToField<char (mlb_stats::*)[TEAM_NAME_LEN]>(args[2]);
				mlb_stats* team = &year_stats->stats[0];

				std::cout << team->Team << "\t" << team->*field << '\n';
			}
			else
			{
				auto field = stringToField<char (mlb_stats::*)[LEAGUE_NAME]>(args[2]);
				mlb_stats* team = &year_stats->stats[0];

				std::cout << team->Team << "\t" << team->*field << '\n';
			}
		}
		else if (isIntField(args[2]))
		{
			int mlb_stats::* field = stringToField<int mlb_stats::*>(args[2]);
			mlb_stats* team = &year_stats->stats[0];

			std::cout << "Team\t" << args[2] << '\n';
			std::cout << team->Team << "\t" << team->*field << '\n';
		}
		else if (isFloatField(args[2]))
		{
			float mlb_stats::* field = stringToField<float mlb_stats::*>(args[2]);
			mlb_stats* team = &year_stats->stats[0];

			std::cout << "Team\t" << args[2] << '\n';
			std::cout << team->Team << "\t" << team->*field << '\n';
		}
	}
	else if (args[3] == "average")
	{
		if (isIntField(args[2]))
		{
			int mlb_stats::* field = stringToField<int mlb_stats::*>(args[2]);

			int total = 0;
			for (int i = 0; i < year_stats->no_teams; i++)
				total += year_stats->stats[i].*field;

			std::cout << "Team " << args[2] << " average: " << (total / static_cast<float>(year_stats->no_teams)) << '\n';
		}
		else if (isFloatField(args[2]))
		{
			float mlb_stats::* field = stringToField<float mlb_stats::*>(args[2]);

			float total = 0.f;
			for (int i = 0; i < year_stats->no_teams; i++)
				total += year_stats->stats[i].*field;

			std::cout << "Team " << args[2] << " average: " << (total / static_cast<float>(year_stats->no_teams)) << '\n';
		}

	}
	else if (args[3] == "median")
	{
		if (isStringField(args[3]))
		{
			std::cout << "Team\t" << args[2] << '\n';

			if (args[2] == "Team")
			{
				auto field = stringToField<char(mlb_stats::*)[TEAM_NAME_LEN]>(args[2]);
				mlb_stats* team = &year_stats->stats[(year_stats->no_teams-1)/2];

				std::cout << team->Team << "\t" << team->*field << '\n';
			}
			else
			{
				auto field = stringToField<char(mlb_stats::*)[LEAGUE_NAME]>(args[2]);
				mlb_stats* team = &year_stats->stats[0];

				std::cout << team->Team << "\t" << team->*field << '\n';
			}
		}

	}
	else
	{
		std::cout << "Error: no such find selection\n";
		return;
	}
}
