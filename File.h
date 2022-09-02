//
//  File.h - classes to read and write files
//  BINS_file_analysis
//
//  Created by Den Fedorov on 27.08.2022.
//

#pragma once
#include "Interaction.h"
#include <iomanip>
#include <fstream>
#include <stdexcept>

namespace fl
{
	class Interaction;
	class Math;

	class Read
	{
	private:
		friend class Interaction;
		friend class Math;

		Read(const std::string & filename, Mode mode);
		~Read();
		auto read(Mode mode) -> void;
		std::ifstream _fin;
		std::vector<unsigned int> _count;                   // duration of file in seconds
		std::vector<float> _thdg;                           // heading of device
		std::vector<float> _roll;                           // roll of device
		std::vector<float> _pitch;                          // pitch of device
		std::vector<float> _gyro_X;                         // impulses of X gyroscope
		std::vector<float> _gyro_Y;                         // impulses of Y gyroscope
		std::vector<float> _gyro_Z;                         // impulses of Z gyroscope
		std::vector<float> _t_gyro_X;                       // temperature of X gyroscope
		std::vector<float> _t_gyro_Y;                       // temperature of Y gyroscope
		std::vector<float> _t_gyro_Z;                       // temperature of Z gyroscope
	};

	class Write
	{
	private:
		friend class Interaction;

		Write(const std::string & s);
		~Write();
		auto write(const Math & math) -> void;
		std::ofstream _fout;
	};
}
