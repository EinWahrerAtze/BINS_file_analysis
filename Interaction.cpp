//
//  Interaction.cpp
//  BINS_file_analysis
//
//  Created by Den Fedorov on 25.08.2022.
//

#pragma once
#include "Interaction.h"
#include "File.h"
#include "Math.h"

namespace fl
{
	Interaction::Interaction() : _mode{ Mode::DAT }, _index{ 0 }
	{
	};

	Interaction::~Interaction()
	{
	}

	auto Interaction::get_mode() const -> int
	{
		return (_mode == Mode::DAT ? 0 : 1);
	}

	auto Interaction::set_mode() -> void
	{
		_mode == Mode::DAT ? _mode = Mode::TXT : _mode = Mode::DAT;
	}

	auto Interaction::set_index(char sign) -> void
	{
		switch (sign)
		{
			case '-':
			{
				if (_index == 0)
				{
					_index = _files.size() - 1;
				}
				else
				{
					--_index;
				}

				break;
			}
			case '+':
			{
				if (_index == _files.size() - 1)
				{
					_index = 0;
				}
				else
				{
					++_index;
				}

				break;
			}
		}
	}

	auto Interaction::get_size() const -> std::size_t
	{
		return _files.size();
	}

	auto Interaction::check(const std::string & s) const -> int
	{
		if (s.empty())
		{
			return -1;
		}
		else if (std::isdigit(s.front()))
		{
			try
			{
				return std::stoi(s);
			}
			catch (const std::out_of_range & ex)
			{
				_msg = ex.what();
				return -1;
			}
		}
		else
		{
			return s.front();
		}
	}

	auto Interaction::menu(Menu menu) -> void
	{
		switch (menu)
		{
			case Menu::MAIN:
			{
				if (_msg.empty())
				{
					std::cout << "Введите команду:\n\n";
				}
				else
				{
					std::cout << _msg << "\n\n";
				}

				std::cout << "'A' Добавить файлы\n";
				std::cout << "'Q' Показать анализ\n";
				std::cout << "'D' Удалить файлы\n";
				std::cout << "'W' Экспортировать результаты\n";
				std::cout << "'X' Выход\n\n";
				std::cout << "Ввод: ";
				break;
			}
			case Menu::READ:
			{
				if (!_msg.empty())
				{
					std::cout << _msg;
				}
				else
				{
					std::cout << "Формат: ";
					std::cout << (_mode == Mode::DAT ? ".dat" : ".txt");
				}

				std::cout << "\t'A' добавить все, 'C' сменить формат, 'X' выход\n\n";

				if (_files.empty())
				{
					std::cout << "Введите имя файла или нажмите 'A' чтобы добавить все файлы в папке" << '\n';
				}
				else
				{
					for (int i = 0; i < _files.size(); ++i)
					{
						std::cout << std::right << std::setw(2);
						std::cout << i + 1 << ": ";
						std::cout << std::right << std::setw(8);
						std::cout << _files[i]._filename;
						std::cout << std::right << std::setw(6);
						std::cout << _files[i]._heading << "°";
						std::cout << std::right << std::setw(5);
						std::cout << (_files[i]._X_tempreture + _files[i]._Y_tempreture + _files[i]._Z_tempreture) / 3 << "°C";
						std::cout << std::right << std::setw(6);
						std::cout << _files[i]._duration << " c." << '\n';
					}
				}

				std::cout << "\nВвод: ";
				break;
			}
			case Menu::RESULT:
			{
				std::cout << std::setfill(' ');
				std::cout.setf(std::ios_base::fixed);
				std::cout.precision(0);

				if (_msg.empty())
				{
					std::cout << "Файл: " << _index + 1 << '/' << _files.size();
				}
				else
				{
					std::cout << _msg;
				}

				std::cout << "\t'Q' назад, 'W' вперёд, 'S' показать все, 'X' выход\n\n";
				std::cout << "Название:";
				std::cout << std::right << (_files[_index]._filename.size() > 5 ?
											std::setw(11) : std::setw(10));
				std::cout << _files[_index]._filename << '\n';
				std::cout << "Длительность:";
				std::cout << std::right << (_files[_index]._duration < 1000 ?
											std::setw(4) : std::setw(5));
				std::cout << _files[_index]._duration << " c.\n";
				std::cout << "Курс:";
				std::cout << std::right << (_files[_index]._heading < 10 ?
											std::setw(10) : _files[_index]._heading < 100 ?
											std::setw(11) : std::setw(12));
				std::cout << _files[_index]._heading << "°" << '\n';
				std::cout << "Температура:";
				std::cout << std::right << std::setw(4);
				std::cout << (_files[_index]._X_tempreture + _files[_index]._Y_tempreture + _files[_index]._Z_tempreture) / 3 << "°C\n\n";

				std::cout << std::right << std::setw(24);
				std::cout << "Выставка";
				std::cout << std::right << std::setw(18);
				std::cout << "Ошибка";
				std::cout << std::right << std::setw(16);
				std::cout << "СКО\n";

				std::cout << "Курс:";
				std::cout << std::right << std::setw(5);
				std::cout << _files[_index]._thdg._degrees << "°";
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._thdg._minutes << '\'';
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._thdg._seconds << '"';
				std::cout << std::right << std::setw(6);
				std::cout << _files[_index]._thdg._degrees_error << "°";
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._thdg._minutes_error << '\'';
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._thdg._seconds_error << '"';
				std::cout << std::right << std::setw(4);
				std::cout << 'X';
				std::cout << std::right << std::setw(9);
				std::cout.precision(4);
				std::cout << _files[_index]._X_deviation;
				std::cout << std::right << std::setw(5);
				std::cout.precision(0);

				std::cout << "\nКрен:";
				std::cout << std::right << std::setw(5);
				std::cout << _files[_index]._roll._degrees << "°";
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._roll._minutes << '\'';
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._roll._seconds << '"';
				std::cout << std::right << std::setw(6);
				std::cout << _files[_index]._roll._degrees_error << "°";
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._roll._minutes_error << '\'';
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._roll._seconds_error << '"';
				std::cout << std::right << std::setw(4);
				std::cout << 'Y';
				std::cout << std::right << std::setw(9);
				std::cout.precision(4);
				std::cout << _files[_index]._Y_deviation;
				std::cout << std::right << std::setw(5);
				std::cout.precision(0);

				std::cout << "\nТангаж:";
				std::cout << std::right << std::setw(3);
				std::cout << _files[_index]._pitch._degrees << "°";
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._pitch._minutes << '\'';
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._pitch._seconds << '"';
				std::cout << std::right << std::setw(6);
				std::cout << _files[_index]._pitch._degrees_error << "°";
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._pitch._minutes_error << '\'';
				std::cout << std::right << std::setw(2);
				std::cout << _files[_index]._pitch._seconds_error << '"';
				std::cout << std::right << std::setw(4);
				std::cout << 'Z';
				std::cout << std::right << std::setw(9);
				std::cout.precision(4);
				std::cout << _files[_index]._Z_deviation;
				std::cout << std::right << std::setw(5);
				std::cout.precision(0);
				std::cout << "\n\nВвод: ";

				break;
			}
			case Menu::RESULT_LIST:
			{
				std::cout << std::setfill(' ');
				std::cout.setf(std::ios_base::fixed);
				std::cout.precision(0);

				if (_msg.empty())
				{
					std::cout << "Файлов добавлено: " << _files.size();
				}
				else
				{
					std::cout << _msg;
				}

				std::cout << "\t'X' назад\n\n";
				std::cout << std::right << std::setw(24);
				std::cout << "Выставка";
				std::cout << std::right << std::setw(18);
				std::cout << "Ошибка";
				std::cout << std::right << std::setw(15);
				std::cout << "СКО";
				std::cout << std::right << std::setw(10);
				std::cout << "°C\n";
				std::cout << "------------------------------------------------";

				for (int i = 0; i < _files.size(); ++i)
				{
					std::cout << "\nКурс:";
					std::cout << std::right << std::setw(5);
					std::cout << _files[i]._thdg._degrees << "°";
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._thdg._minutes << '\'';
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._thdg._seconds << '"';
					std::cout << std::right << std::setw(6);
					std::cout << _files[i]._thdg._degrees_error << "°";
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._thdg._minutes_error << '\'';
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._thdg._seconds_error << '"';
					std::cout << std::right << std::setw(4);
					std::cout << 'X';
					std::cout << std::right << std::setw(9);
					std::cout.precision(4);
					std::cout << _files[i]._X_deviation;
					std::cout << std::right << std::setw(5);
					std::cout.precision(0);
					std::cout << _files[i]._X_tempreture;

					std::cout << "\nКрен:";
					std::cout << std::right << std::setw(5);
					std::cout << _files[i]._roll._degrees << "°";
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._roll._minutes << '\'';
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._roll._seconds << '"';
					std::cout << std::right << std::setw(6);
					std::cout << _files[i]._roll._degrees_error << "°";
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._roll._minutes_error << '\'';
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._roll._seconds_error << '"';
					std::cout << std::right << std::setw(4);
					std::cout << 'Y';
					std::cout << std::right << std::setw(9);
					std::cout.precision(4);
					std::cout << _files[i]._Y_deviation;
					std::cout << std::right << std::setw(5);
					std::cout.precision(0);
					std::cout << _files[i]._Y_tempreture;

					std::cout << "\nТангаж:";
					std::cout << std::right << std::setw(3);
					std::cout << _files[i]._pitch._degrees << "°";
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._pitch._minutes << '\'';
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._pitch._seconds << '"';
					std::cout << std::right << std::setw(6);
					std::cout << _files[i]._pitch._degrees_error << "°";
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._pitch._minutes_error << '\'';
					std::cout << std::right << std::setw(2);
					std::cout << _files[i]._pitch._seconds_error << '"';
					std::cout << std::right << std::setw(4);
					std::cout << 'Z';
					std::cout << std::right << std::setw(9);
					std::cout.precision(4);
					std::cout << _files[i]._Z_deviation;
					std::cout << std::right << std::setw(5);
					std::cout.precision(0);
					std::cout << _files[i]._Z_tempreture << '\n';

					std::cout << (i == _files.size() - 1 ?
								  "\n" : "------------------------------------------------");
				}

				std::cout << "Ввод: ";
				break;
			}
			case Menu::REMOVE:
			{
				if (_msg.empty())
				{
					std::cout << "Файлов добавлено: " << _files.size();
				}
				else
				{
					std::cout << _msg;
				}

				if (_files.empty())
				{
					std::cout << "\t'X' выход\n\n";
				}
				else
				{
					std::cout << "\t'D' удалить все, 'X' выход\n\n";
				}

				for (int i = 0; i < _files.size(); ++i)
				{
					std::cout << std::right << std::setw(2);
					std::cout << i + 1 << ": ";
					std::cout << std::right << std::setw(8);
					std::cout << _files[i]._filename;
					std::cout << std::right << std::setw(6);
					std::cout << _files[i]._heading << "°";
					std::cout << std::right << std::setw(5);
					std::cout << (_files[i]._X_tempreture + _files[i]._Y_tempreture + _files[i]._Z_tempreture) / 3 << "°C";
					std::cout << std::right << std::setw(6);
					std::cout << _files[i]._duration << " c." << '\n';
				}

				std::cout << "\nВвод: ";

				break;
			}
			case Menu::WRITE:
			{
				if (!_msg.empty())
				{
					std::cout << _msg;
				}

				std::cout << "Введите название файла: ";

				break;
			}
		}

		_msg.clear();
	}

	auto Interaction::remove(int n) -> void
	{
		switch (n)
		{
			case 'd':
			case 'D':
			{
				_files.clear();
				_msg = "Все файлы удалены!";
				break;
			}
			default:
			{
				if (n < 0 || n > _files.size())
				{
					throw std::runtime_error("Неправильный индекс!");
				}
				else
				{
					_files.erase(_files.begin() + n - 1);
					_msg = "Файл #";
					_msg += std::to_string(n) += " удалён";
				}

				break;
			}
		}
	}

	auto Interaction::message(const std::string & s) -> void
	{
		_msg = s;
	}

	auto Interaction::read(const std::string & filename) -> void
	{
		try
		{
			Read new_file(filename, _mode);
			new_file.read(_mode);
			Math new_math(filename, new_file);
			_files.push_back(new_math);
			std::sort(_files.begin(), _files.end(), new_math.compare);
		}
		catch (const std::runtime_error & ex)
		{
			message(ex.what());
		}
	}

	auto Interaction::write(const std::string & filename) -> void
	{
		try
		{
			Write file(filename);

			for (int i = 0; i < _files.size(); ++i)
			{
				file.write(_files[i]);
			}
		}
		catch (const std::runtime_error & ex)
		{
			message(ex.what());
		}
	}
}
