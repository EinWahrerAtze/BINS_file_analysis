//
//  File.cpp
//  BINS_file_analysis
//
//  Created by Den Fedorov on 27.08.2022.
//

#pragma once
#include "File.h"
#include "Math.h"

namespace fl
{
	fl::Read::Read(const std::string & filename, Mode mode)
	{
		// reserve some memory to avoid allocations
		_count.reserve(5000);
		_thdg.reserve(5000);
		_roll.reserve(5000);
		_pitch.reserve(5000);
		_gyro_X.reserve(5000);
		_gyro_Y.reserve(5000);
		_gyro_Z.reserve(5000);
		_t_gyro_X.reserve(5000);
		_t_gyro_Y.reserve(5000);
		_t_gyro_Z.reserve(5000);

		if (mode == Mode::DAT)
		{
			_fin.open(filename, std::ios_base::in | std::ios_base::binary);

			if (!_fin.is_open())
			{
				throw std::runtime_error("Не удалось открыть " + filename + '!');
			}
		}
		else
		{
			_fin.open(filename);

			if (!_fin.is_open())
			{
				throw std::runtime_error("Не удалось открыть " + filename + '!');
			}
		}
	}

	fl::Read::~Read()
	{
		_fin.close();
	}

	auto fl::Read::read(Mode mode) -> void
	{
		if (mode == Mode::DAT)
		{
			unsigned int count{ 0 };
			float pitch{ 0.0f };
			float roll{ 0.0f };
			float thdg{ 0.0f };
			float gyro_X{ 0.0f };
			float gyro_Y{ 0.0f };
			float gyro_Z{ 0.0f };
			int t_gyro_X{ 0 };
			int t_gyro_Y{ 0 };
			int t_gyro_Z{ 0 };

			int n{ 8428 };                                      // set the input buffer pointer to skip the first 59 rows of file

			while (_fin.good())
			{
				_fin.seekg(n, std::ios_base::beg);
				_fin.read((char *)&count, 2);

				_count.push_back(count);

				_fin.seekg(n += 12, std::ios_base::beg);
				_fin.read((char *)&pitch, 4);					// 12-16
				_pitch.push_back(pitch);
				_fin.read((char *)&roll, 4);					// 16-20
				_roll.push_back(roll);

				_fin.seekg(n += 16, std::ios_base::beg);
				_fin.read((char *)&thdg, 4);					// 28-32
				_thdg.push_back(thdg);

				_fin.seekg(n += 52, std::ios_base::beg);
				_fin.read((char *)&gyro_X, 4);					// 80-84
				_gyro_X.push_back(gyro_X);
				_fin.read((char *)&gyro_Y, 4);					// 84-88
				_gyro_Y.push_back(gyro_Y);
				_fin.read((char *)&gyro_Z, 4);					// 88-92
				_gyro_Z.push_back(gyro_Z);

				_fin.seekg(n += 72, std::ios_base::beg);
				_fin.read((char *)&t_gyro_X, 4);				// 152-156
				_t_gyro_X.push_back(t_gyro_X);
				_fin.read((char *)&t_gyro_Y, 4);				// 156-160
				_t_gyro_Y.push_back(t_gyro_Y);
				_fin.read((char *)&t_gyro_Z, 4);				// 160-164
				_t_gyro_Z.push_back(t_gyro_Z);

				n += 149;
			}

			// for some reason reading does not stop at the end of file and adds additional row to the end
			_count.pop_back();
			_pitch.pop_back();
			_roll.pop_back();
			_thdg.pop_back();
			_gyro_X.pop_back();
			_gyro_Y.pop_back();
			_gyro_Z.pop_back();
			_t_gyro_X.pop_back();
			_t_gyro_X.pop_back();
			_t_gyro_X.pop_back();
		}
		else
		{
			float tmp{ 0.0f };                   // temporary variable to read numbers to
			int column_num{ 0 };                 // variable to count columns in file

			while (_fin >> tmp)                  // to skip the first 59 seconds of file
			{
				if (tmp < 60)
				{
					_fin.ignore(10000, '\n');
				}
				else
				{
					break;
				}
			}

			// set the input pointer back to 2 bytes to read "count"
			_fin.seekg(_fin.tellg() -= 2);

			while (_fin.good() && _fin >> tmp)
			{
				switch (column_num)
				{
					case 0: _count.push_back(static_cast<unsigned int>(tmp));
						break;
					case 4: _pitch.push_back(tmp);
						break;
					case 5: _roll.push_back(tmp);
						break;
					case 8: _thdg.push_back(tmp);
						break;
					case 21: _gyro_X.push_back(tmp);
						break;
					case 22: _gyro_Y.push_back(tmp);
						break;
					case 23: _gyro_Z.push_back(tmp);
						break;
					case 39: _t_gyro_X.push_back(static_cast<int>(tmp));
						break;
					case 40: _t_gyro_Y.push_back(static_cast<int>(tmp));
						break;
					case 41: _t_gyro_Z.push_back(static_cast<int>(tmp));
						_fin.ignore(10000, '\n');
						break;
				}

				column_num == 41 ? column_num = 0 : ++column_num;
			}
		}

		// shrink all vectors to its actual sizes
		_count.shrink_to_fit();
		_pitch.shrink_to_fit();
		_roll.shrink_to_fit();
		_thdg.shrink_to_fit();
		_gyro_X.shrink_to_fit();
		_gyro_Y.shrink_to_fit();
		_gyro_Z.shrink_to_fit();
		_t_gyro_X.shrink_to_fit();
		_t_gyro_Y.shrink_to_fit();
		_t_gyro_Z.shrink_to_fit();
	}

	fl::Write::Write(const std::string & filename)
	{
		_fout.open(filename);

		if (!_fout.is_open())
		{
			throw std::runtime_error("Не удалось открыть файл " + filename + " для записи!");
		}

		// writing upper row first
		_fout << std::right << std::setw(24);
		_fout << "Выставка";
		_fout << std::right << std::setw(18);
		_fout << "Ошибка";
		_fout << std::right << std::setw(15);
		_fout << "СКО";
		_fout << std::right << std::setw(10);
		_fout << "°C\n";
		_fout << "------------------------------------------------\n";
	}

	fl::Write::~Write()
	{
		_fout.close();
	}

	auto fl::Write::write(const Math & math) -> void
	{
		_fout << std::setfill(' ');
		_fout.setf(std::ios_base::fixed);
		_fout.precision(0);

		_fout << "Курс:";
		_fout << std::right << std::setw(5);
		_fout << math._thdg._degrees << "°";
		_fout << std::right << std::setw(2);
		_fout << math._thdg._minutes << '\'';
		_fout << std::right << std::setw(2);
		_fout << math._thdg._seconds << '"';
		_fout << std::right << std::setw(6);
		_fout << math._thdg._degrees_error << "°";
		_fout << std::right << std::setw(2);
		_fout << math._thdg._minutes_error << '\'';
		_fout << std::right << std::setw(2);
		_fout << math._thdg._seconds_error << '"';
		_fout << std::right << std::setw(4);
		_fout << 'X';
		_fout << std::right << std::setw(9);
		_fout.precision(4);
		_fout << math._X_deviation;
		_fout << std::right << std::setw(5);
		_fout.precision(0);
		_fout << math._X_tempreture;

		_fout << "\nКрен:";
		_fout << std::right << std::setw(5);
		_fout << math._roll._degrees << "°";
		_fout << std::right << std::setw(2);
		_fout << math._roll._minutes << '\'';
		_fout << std::right << std::setw(2);
		_fout << math._roll._seconds << '"';
		_fout << std::right << std::setw(6);
		_fout << math._roll._degrees_error << "°";
		_fout << std::right << std::setw(2);
		_fout << math._roll._minutes_error << '\'';
		_fout << std::right << std::setw(2);
		_fout << math._roll._seconds_error << '"';
		_fout << std::right << std::setw(4);
		_fout << 'Y';
		_fout << std::right << std::setw(9);
		_fout.precision(4);
		_fout << math._Y_deviation;
		_fout << std::right << std::setw(5);
		_fout.precision(0);
		_fout << math._Y_tempreture;

		_fout << "\nТангаж:";
		_fout << std::right << std::setw(3);
		_fout << math._pitch._degrees << "°";
		_fout << std::right << std::setw(2);
		_fout << math._pitch._minutes << '\'';
		_fout << std::right << std::setw(2);
		_fout << math._pitch._seconds << '"';
		_fout << std::right << std::setw(6);
		_fout << math._pitch._degrees_error << "°";
		_fout << std::right << std::setw(2);
		_fout << math._pitch._minutes_error << '\'';
		_fout << std::right << std::setw(2);
		_fout << math._pitch._seconds_error << '"';
		_fout << std::right << std::setw(4);
		_fout << 'Z';
		_fout << std::right << std::setw(9);
		_fout.precision(4);
		_fout << math._Y_deviation;
		_fout << std::right << std::setw(5);
		_fout.precision(0);
		_fout << math._Z_tempreture << '\n';

		_fout << "------------------------------------------------\n";
	}
}
