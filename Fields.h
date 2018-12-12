#pragma once
#include "MLB_Stats.h"
#include<string>

template<typename T>
T stringToField(const std::string& str)
{
	if (str == "Team")
	{
		return reinterpret_cast<T>(&mlb_stats::Team);
	}
	else if (str == "League")
	{
		return reinterpret_cast<T>(&mlb_stats::League);
	}
	else if (str == "G")
	{
		return reinterpret_cast<T>(&mlb_stats::G);
	}
	else if (str == "AB")
	{
		return reinterpret_cast<T>(&mlb_stats::AB);
	}
	else if (str == "R")
	{
		return reinterpret_cast<T>(&mlb_stats::R);
	}
	else if (str == "H")
	{
		return reinterpret_cast<T>(&mlb_stats::H);
	}
	else if (str == "B2")
	{
		return reinterpret_cast<T>(&mlb_stats::B2);
	}
	else if (str == "B3")
	{
		return reinterpret_cast<T>(&mlb_stats::B3);
	}
	else if (str == "HR")
	{
		return reinterpret_cast<T>(&mlb_stats::HR);
	}
	else if (str == "RBI")
	{
		return reinterpret_cast<T>(&mlb_stats::RBI);
	}
	else if (str == "BB")
	{
		return reinterpret_cast<T>(&mlb_stats::BB);
	}
	else if (str == "SO")
	{
		return reinterpret_cast<T>(&mlb_stats::SO);
	}
	else if (str == "SB")
	{
		return reinterpret_cast<T>(&mlb_stats::SB);
	}
	else if (str == "CS")
	{
		return reinterpret_cast<T>(&mlb_stats::CS);
	}
	else if (str == "AVG")
	{
		return reinterpret_cast<T>(&mlb_stats::AVG);
	}
	else if (str == "OBP")
	{
		return reinterpret_cast<T>(&mlb_stats::OBP);
	}
	else if (str == "SLG")
	{
		return reinterpret_cast<T>(&mlb_stats::SLG);
	}
	else if (str == "OPS")
	{
		return reinterpret_cast<T>(&mlb_stats::OPS);
	}
	else
	{
		return NULL;
	}
}

bool isStringField(const std::string& str)
{
	return str == "Team" || str == "League";
}

bool isIntField(const std::string& str)
{
	return str == "G" ||
		str == "AB" ||
		str == "R" ||
		str == "H" ||
		str == "B2" ||
		str == "B3" ||
		str == "HR" ||
		str == "RBI" ||
		str == "BB" ||
		str == "SO" ||
		str == "SB" ||
		str == "CS";

}

bool isFloatField(const std::string& str)
{
	return str == "AVG" ||
		str == "OBP" ||
		str == "SLG" ||
		str == "OPS";
}

template<typename T>
void printTeamsField(mlb_stats* stats, int length, T field)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << stats[i].Team << "\t" << stats[i].*field << '\n';
	}
}

template<typename T>
void printTeamsFieldWithYear(mlb_stats* stats, int* year, int length, T field)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << year[i] << "\t" << stats[i].Team << "\t" << stats[i].*field << '\n';
	}
}
