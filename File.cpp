//
//  file.cpp
//  BINS_file_analysis_3.0
//
//  Created by Denis Fedorov on 25.11.2022.
//

#include <stdexcept>
#include <format>
#include "file.h"
#include "math.h"

namespace FL
{
	File::File(std::string_view path) : _path(path) {}
	
	Load::Load(std::string_view path) : File(path) {}
	
	DAT::DAT(std::string_view path) : Load(path)
	{
		_fin.open(_path, std::ios_base::binary | std::ios_base::in);
		if (!_fin.is_open())
		{
			throw std::runtime_error {std::format("Не удаётся открыть \"{}\"", _path.string())};
		}
	}
	
	void DAT::find_start()
	{
		unsigned int count {};
		while (!_fin.eof())
		{
			_fin.read(reinterpret_cast<char*>(&count), 2);
			if (count < _start)
			{
				_fin.seekg(_fin.tellg() += 299);
			}
			else
			{
				_fin.seekg(_fin.tellg() -= 2);
				break;
			}
		}
		if (_fin.bad())
		{
			throw std::runtime_error {std::format("\"{}\" неподдерживаемая структура", _path.filename().string())};
		}
	}
	
	const std::vector<Row> & DAT::read()
	{
		Row row {};
		while (_fin.good())
		{
			_fin.read(reinterpret_cast<char*>(&row.count), 2);
			_fin.read(reinterpret_cast<char*>(&row.mode), 2);
			_fin.read(reinterpret_cast<char*>(&row.system_time), 4);
			_fin.read(reinterpret_cast<char*>(&row.mode_time), 4);
			_fin.read(reinterpret_cast<char*>(&row.pitch), 4);
			_fin.read(reinterpret_cast<char*>(&row.roll), 4);
			_fin.read(reinterpret_cast<char*>(&row.heading), 4);
			_fin.read(reinterpret_cast<char*>(&row.azimuth), 4);
			_fin.read(reinterpret_cast<char*>(&row.thdg), 4);
			_fin.read(reinterpret_cast<char*>(&row.latitude), 4);
			_fin.read(reinterpret_cast<char*>(&row.longtitude), 4);
			_fin.read(reinterpret_cast<char*>(&row.H), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ve), 4);
			_fin.read(reinterpret_cast<char*>(&row.Vn), 4);
			_fin.read(reinterpret_cast<char*>(&row.Vu), 4);
			_fin.read(reinterpret_cast<char*>(&row.dAt_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.dAt_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.dAt_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.dVt_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.dVt_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.dVt_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.gyro_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.gyro_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.gyro_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.acc_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.acc_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.acc_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ucplc_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ucplc_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ucplc_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.Uhfo_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.Uhfo_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.Uhfo_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.Fout_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.Fout_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.Fout_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.Fdith_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.Fdith_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.Fdith_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.gyro_X_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.gyro_Y_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.gyro_Z_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.acc_X_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.acc_Y_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.acc_Z_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.dpb_X_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.dpb_Y_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.dpb_Z_temperature), 4);
			_fin.read(reinterpret_cast<char*>(&row.drift_X), 4);
			_fin.read(reinterpret_cast<char*>(&row.drift_Y), 4);
			_fin.read(reinterpret_cast<char*>(&row.drift_Z), 4);
			_fin.read(reinterpret_cast<char*>(&row.faults), 2);
			_fin.read(reinterpret_cast<char*>(&row.D12), 4);
			_fin.read(reinterpret_cast<char*>(&row.D13), 4);
			_fin.read(reinterpret_cast<char*>(&row.D21), 4);
			_fin.read(reinterpret_cast<char*>(&row.D23), 4);
			_fin.read(reinterpret_cast<char*>(&row.D31), 4);
			_fin.read(reinterpret_cast<char*>(&row.D32), 4);
			_fin.read(reinterpret_cast<char*>(&row.Mg1), 4);
			_fin.read(reinterpret_cast<char*>(&row.Mg2), 4);
			_fin.read(reinterpret_cast<char*>(&row.Mg3), 4);
			_fin.read(reinterpret_cast<char*>(&row.Wo1), 4);
			_fin.read(reinterpret_cast<char*>(&row.Wo2), 4);
			_fin.read(reinterpret_cast<char*>(&row.Wo3), 4);
			_fin.read(reinterpret_cast<char*>(&row.E12), 4);
			_fin.read(reinterpret_cast<char*>(&row.E13), 4);
			_fin.read(reinterpret_cast<char*>(&row.E21), 4);
			_fin.read(reinterpret_cast<char*>(&row.E23), 4);
			_fin.read(reinterpret_cast<char*>(&row.E31), 4);
			_fin.read(reinterpret_cast<char*>(&row.E32), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ma1), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ma2), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ma2), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ao1), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ao2), 4);
			_fin.read(reinterpret_cast<char*>(&row.Ao3), 4);
			_fin.read(reinterpret_cast<char*>(&row.reserve), 1);
			_fin.read(reinterpret_cast<char*>(&row.crc8), 1);
			_fin.read(reinterpret_cast<char*>(&row.error), 1);
			_file.push_back(row);
			if (_fin.bad())
			{
				throw std::runtime_error {std::format("\"{}\" неподдерживаемая структура", _path.filename().string())};
			}
		}
		return _file;
	}
	
	TXT::TXT(std::string_view path) : Load(path)
	{
		_fin.open(_path, std::ios_base::in);
		if (!_fin.is_open())
		{
			throw std::runtime_error {std::format("Не удаётся открыть \"{}\"", _path.string())};
		}
	}
	
	void TXT::find_start()
	{
		unsigned int count {};
		while (_fin >> count)
		{
			if (count < _start)
			{
				_fin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			}
			else
			{
				_fin.seekg(_fin.tellg() -= 2);
				break;
			}
		}
		if (_fin.bad())
		{
			throw std::runtime_error {std::format("\"{}\" неподдерживаемая структура", _path.filename().string())};
		}
	}
	
	const std::vector<Row> & TXT::read()
	{
		Row row {};
		while (_fin.good())
		{
			_fin >> row.count;
			_fin >> row.mode;
			_fin >> row.system_time;
			_fin >> row.mode_time;
			_fin >> row.pitch;
			_fin >> row.heading;
			_fin >> row.azimuth;
			_fin >> row.thdg;
			_fin >> row.latitude;
			_fin >> row.longtitude;
			_fin >> row.H;
			_fin >> row.Ve >> row.Vn >> row.Vu;
			_fin >> row.dAt_X >> row.dAt_Y >> row.dAt_Z;
			_fin >> row.gyro_X >> row.gyro_Y >> row.gyro_Z;
			_fin >> row.acc_X >> row.acc_Y >> row.acc_Z;
			_fin >> row.Ucplc_X >> row.Ucplc_Y >> row.Ucplc_Z;
			_fin >> row.Uhfo_X >> row.Uhfo_Y >> row.Uhfo_Z;
			_fin >> row.Fout_X >> row.Fout_Y >> row.Fout_Z;
			_fin >> row.gyro_X_temperature >> row.gyro_Y_temperature >> row.gyro_Z_temperature;
			_fin >> row.acc_X_temperature >> row.acc_Y_temperature >> row.acc_Z_temperature;
			_fin >> row.dpb_X_temperature >> row.dpb_Y_temperature >> row.dpb_Z_temperature;
			_fin >> row.drift_X >> row.drift_Y >> row.drift_Z;
			_fin >> row.faults;
			_fin >> row.D12 >> row.D13 >> row.D21 >> row.D23 >> row.D31 >> row.D32;
			_fin >> row.Mg1 >> row.Mg2 >> row.Mg3;
			_fin >> row.Wo1 >> row.Wo2 >> row.Wo3;
			_fin >> row.E12 >> row.E13 >> row.E21 >> row.E23 >> row.E31 >> row.E32;
			_fin >> row.Ma1 >> row.Ma2 >> row.Ma3;
			_fin >> row.Ao1 >> row.Ao2 >> row.Ao3;
			_fin >> row.reserve;
			_fin >> row.crc8;
			_fin >> row.error;
			_file.push_back(row);
		}
		if (_fin.bad())
		{
			throw std::runtime_error {std::format("\"{}\" неподдерживаемая структура", _path.filename().string())};
		}
		return _file;
	}
												  
	Save::Save(std::string_view path) : File(path)
	{
		_fout.open(_path, std::ios_base::out);
		if (!_fout.is_open())
		{
			throw std::runtime_error {std::format("Не удаётся открыть \"{}\"", _path.filename().string())};
		}
	}
												  
	void Save::write(const std::vector<Row> & file)
	{
		for (const Row & row : file)
		{
			_fout << std::format("{}\t", row.count);
			_fout << std::format("{}\t", row.mode);
			_fout << std::format("{}\t", row.system_time);
			_fout << std::format("{}\t", row.mode_time);
			_fout << std::format("{: .5f}\t", row.pitch);
			_fout << std::format("{: .5f}\t", row.roll);
			_fout << std::format("{: .2f}\t", row.heading);
			_fout << std::format("{:.5f}\t", row.azimuth);
			_fout << std::format("{: .5f}\t", row.thdg);
			_fout << std::format("{:.4f}\t", row.latitude);
			_fout << std::format("{:.4f}\t", row.longtitude);
			_fout << std::format("{:.2f}\t", row.H);
			_fout << std::format("{: .5f}\t{: .5f}\t{: .5f}\t", row.Ve, row.Vn, row.Vu);
			_fout << std::format("{: .5f}\t{: .5f}\t{: .5f}\t", row.dAt_X, row.dAt_Y, row.dAt_Z);
			_fout << std::format("{: .5f}\t{: .5f}\t{: .5f}\t", row.dVt_X, row.dVt_Y, row.dVt_Z);
			_fout << std::format("{: .5f}\t{: .5f}\t{: .5f}\t", row.gyro_X, row.gyro_Y, row.gyro_Z);
			_fout << std::format("{: .5f}\t{: .5f}\t{: .5f}\t", row.acc_X, row.acc_Y, row.acc_Z);
			_fout << std::format("{: .2f}\t{: .2f}\t{: .2f}\t", row.Ucplc_X, row.Ucplc_Y, row.Ucplc_Z);
			_fout << std::format("{: .2f}\t{: .2f}\t{: .2f}\t", row.Uhfo_X, row.Uhfo_Y, row.Uhfo_Z);
			_fout << std::format("{:.1f}\t{:.1f}\t{:.1f}\t", row.Fout_X, row.Fout_Y, row.Fout_Z);
			_fout << std::format("{:.1f}\t{:.1f}\t{:.1f}\t", row.Fdith_X, row.Fdith_Y, row.Fdith_Z);
			_fout << std::format("{}\t{}\t{}\t", row.gyro_X_temperature, row.gyro_Y_temperature, row.gyro_Z_temperature);
			_fout << std::format("{}\t{}\t{}\t", row.acc_X_temperature, row.acc_Y_temperature, row.acc_Z_temperature);
			_fout << std::format("{}\t{}\t{}\t", row.dpb_X_temperature, row.dpb_Y_temperature, row.dpb_Z_temperature);
			_fout << std::format("{:.0f}\t{:.0f}\t{:.0f}\t", row.drift_X, row.drift_Y, row.drift_Z);
			_fout << std::format("{}\t", row.faults);
			_fout << std::format("{: .4f}\t{: .4f}\t{: .4f}\t{: .4f}\t{: .4f}\t{: .4f}\t", row.D12, row.D13, row.D21, row.D23, row.D31, row.D32);
			_fout << std::format("{: .4f}\t{: .4f}\t{: .4f}\t", row.Mg1, row.Mg2, row.Mg3);
			_fout << std::format("{: .4f}\t{: .4f}\t{: .4f}\t", row.Wo1, row.Wo2, row.Wo3);
			_fout << std::format("{: .4f}\t{: .4f}\t{: .4f}\t{: .4f}\t{: .4f}\t{: .4f}\t", row.E12, row.E13, row.E21, row.E23, row.E31, row.E32);
			_fout << std::format("{: .4f}\t{: .4f}\t{: .4f}\t", row.Ma1, row.Ma2, row.Ma3);
			_fout << std::format("{: .4f}\t{: .4f}\t{: .4f}\t", row.Ao1, row.Ao2, row.Ao3);
			_fout << std::format("{}\t", row.reserve);
			_fout << std::format("{}\t", row.crc8);
			_fout << std::format("{}\n", row.error);
		}
		if (_fout.bad())
		{
			throw std::runtime_error {std::format("Не удаётся записать \"{}\"", _path.filename().string())};
		}
	}
												  
	void Save::write(const std::multimap<std::string, Result> & results)
	{
		for (auto result {results.cbegin()}; result != results.cend(); ++result)
		{
			// filename
			_fout << std::format("{:-<66}\n", result->first);
			// first row
			_fout << std::format("Heading:\t{}°\t", result->second.heading);
			_fout << std::format("THdg:\t{}°{}'{}\"\t", result->second.thdg.degree, result->second.thdg.minute, result->second.thdg.second);
			_fout << std::format("{}°{:0>2}'{:0>2}\"\t", result->second.thdg.degree_error, result->second.thdg.minute_error, result->second.thdg.second_error);
			_fout << std::format("X\t{:.4f}\n", result->second.deviation_X);
			// second row
			_fout << std::format("Duration:\t{} s.\t", result->second.duration);
			_fout << std::format("Roll:\t{}°{}'{}\"\t", result->second.roll.degree, result->second.roll.minute, result->second.roll.second);
			_fout << std::format("{}°{:0>2}'{:0>2}\"\t", result->second.roll.degree_error, result->second.roll.minute_error, result->second.roll.second_error);
			_fout << std::format("Y\t{:.4f}\n", result->second.deviation_Y);
			// third row
			_fout << std::format("Temperature:\t{}°C\t", (result->second.temperature_X + result->second.temperature_Y + result->second.temperature_Z) / 3);
			_fout << std::format("Pitch:\t{}°{}'{}\"\t", result->second.pitch.degree, result->second.pitch.minute, result->second.pitch.second);
			_fout << std::format("{}°{:0>2}'{:0>2}\"\t", result->second.pitch.degree_error, result->second.pitch.minute_error, result->second.pitch.second_error);
			_fout << std::format("Z\t{:.4f}\n\n", result->second.deviation_Z);
		}
	}
}
