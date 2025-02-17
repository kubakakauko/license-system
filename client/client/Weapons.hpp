#pragma once
#include <vector>

struct vector2
{
	int x, y;
};

namespace Weapons
{
	namespace ak
	{
		std::vector<vector2> pattern = { {-35, 50},{5, 46},{-55, 42},{-42, 37},{0, 33},{16, 28},{29, 24},{38, 19},{42, 14},{42, 9},{38, 9},{30, 18},{17, 25},{0, 29},{-15, 32},{-27, 33},{-37, 32},{-43, 29},{-46, 24},{-45, 17},{-42, 8},{-35, 5},{-24, 14},{-11, 21},{12, 25},{36, 28},{49, 28},{49, 26},{38, 21} };
		float delay = 133.3333333;
		std::vector<double> controltime = { 121.96149709966872,92.6333814724611,138.60598637206294,113.37874368443146,66.25151186427745,66.29530438019354,75.9327831420658,85.05526144256157,89.20256669256554,86.68010184667988,78.82145888317788,70.0451048111144,60.85979604582978,59.51642457624619,71.66762996283607,86.74060009403034,98.3363599080854,104.34161954944257,104.09299204005345,97.58780746901739,85.48062700875559,70.4889202349561,56.56417811530545,47.386907899993936,56.63787408680247,91.5937793023631,112.38667610336424,111.39338971888095,87.5067801164596 };
	}
	namespace mp5
	{
		std::vector<vector2> pattern = { {0, 21},{0, 29},{0, 33},{12, 33},{29, 29},{33, 22},{23, 13},{0, 10},{-18, 9},{-25, 8},{-19, 7},{-3, 6},{7, 5},{14, 4},{16, 4},{16, 3},{12, 2},{6, 2},{-1, 1},{-5, 1},{-8, 0},{-10, 0},{-12, 0},{-13, 0},{-13, 0},{-12, 0},{-11, 0},{-8, 0},{-5, 0} };
		float delay = 98;
	}
	namespace smg
	{
		std::vector<vector2> pattern = { {-13, 27},{-6, 27},{0, 26},{6, 25},{10, 23},{11, 21},{9, 18},{4, 16},{-3, 14},{-9, 13},{-11, 12},{-10, 10},{-6, 9},{0, 9},{6, 8},{9, 7},{10, 6},{9, 6},{4, 5},{0, 5},{-4, 5},{-6, 5},{-5, 5} };
		float delay = 99;
	}
	namespace lr
	{
		std::vector<vector2> pattern = { {-2, 25},{-6, 31},{-10, 33},{-14, 31},{-15, 25},{-14, 20},{-9, 17},{-2, 15},{9, 12},{17, 10},{20, 8},{17, 7},{10, 5},{0, 4},{-5, 4},{-9, 4},{-12, 3},{-14, 3},{-15, 3},{-15, 2},{-14, 2},{-13, 2},{-10, 2},{-7, 2},{-3, 2},{13, 2},{30, 2},{36, 3},{30, 3} };
		float delay = 118;
	}
	namespace thompson
	{
		std::vector<vector2> pattern = { {-15, 33},{-5, 32},{3, 31},{11, 29},{13, 26},{10, 22},{2, 18},{-7, 16},{-13, 14},{-13, 13},{-7, 11},{2, 10},{10, 9},{12, 8},{11, 7},{5, 7},{-2, 6},{-6, 6},{-7, 6} };
		float delay = 127;
	}
	namespace semi
	{
		std::vector<vector2> pattern = { {0,75}, {0,75} };
		float delay = 150;
	}
	namespace test
	{
		std::vector<vector2> pattern = { {0,75},{0,75} };
		float delay = 150;
	}
	namespace m249
	{
		std::vector<vector2> pattern = { {0,58},{0,58} };
		float delay = 103;
	}
}