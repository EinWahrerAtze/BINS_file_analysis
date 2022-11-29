//
//  menu.cpp
//  BINS_file_analysis_3.0
//
//  Created by Denis Fedorov on 25.11.2022.
//

#include <format>
#include <iostream>
#include "menu.h"
#include "interaction.h"

namespace FL
{
	Menu::Menu() {}
	
	void Menu::clear() const noexcept
	{
	#if defined(_WIN32)
		system("cls");
	#else
		system("clear");
	#endif
	}
	
	void Menu::send_msg(std::string_view message) noexcept
	{
		_message = std::move(message);
	}
	
	void Menu::clear_msg() noexcept
	{
		_message.clear();
	}
	
	void Menu::show_msg(std::string_view message) const noexcept
	{
		if (_message.empty())
		{
			std::cout << message;
		}
		else
		{
			std::cout << _message;
		}
	}
	
	Short::Short() {}
	
	void Short::show(const Interaction * i) const noexcept
	{
		std::cout << std::format("[{}]", i->_format == Interaction::Format::DAT ? "DAT" : "TXT");
		std::cout << std::format("{:>13}", "[Анализ]");
		std::cout << std::format("{:>18}", "Конвертация");
		std::cout << std::format("{:>17}", "Сохранить");
		std::cout << std::format("{:>14}\n\n", "Помощь");
		this->show_msg("Нажмите '1', '2', '3' или '4' для переключения меню");
		std::cout << "\n\n: ";
	}
	
	Long::Long() {}
	
	void Long::show(const Interaction * i) const noexcept
	{
		std::cout << std::format("[{}]", i->_format == Interaction::Format::DAT ? "DAT" : "TXT");
		std::cout << std::format("{:>13}", "[Анализ]");
		std::cout << std::format("{:>18}", "Конвертация");
		std::cout << std::format("{:>17}", "Сохранить");
		std::cout << std::format("{:>14}\n\n", "Помощь");
		for (const auto & error : i->_errors)
		{
			std::cout << error << "\n";
		}
		std::cout << "\n";
		for (auto file {i->_files.cbegin()}; file != i->_files.cend(); ++file)
		{
			// filename
			std::cout << std::format("{:-<66}\n", file->first);
			
			// first row
			std::cout << std::format("{:12}{:3}{:6}", "Румб:", file->second.heading, "°");
			std::cout << std::format("{:8}{:>3}°{:>2}'{:>2}{:5}", "Курс:", file->second.thdg.degree, file->second.thdg.minute, file->second.thdg.second, "\"");
			if (file->second.thdg.degree_error >= 0.0f && file->second.thdg.minute_error >= 7.0f && file->second.thdg.second_error >= 2.0f)
			{
				std::cout << std::format("\033[41m{:>1}°{:>2}'{:>2}\"\033[0m", file->second.thdg.degree_error, file->second.thdg.minute_error, file->second.thdg.second_error);
			}
			else
			{
				std::cout << std::format("{:>1}°{:>2}'{:>2}\"", file->second.thdg.degree_error, file->second.thdg.minute_error, file->second.thdg.second_error);
			}
			std::cout << std::format("{:^9}{:.4f}\n", "X", file->second.deviation_X);
			// second row
			std::cout << std::format("{:10}{:>6}{:5}", "Длительность:", file->second.duration, " с.");
			std::cout << std::format("{:6}{:> 5}°{:>2}'{:>2}{:5}", "Крен:", file->second.roll.degree, file->second.roll.minute, file->second.roll.second, "\"");
			if (file->second.roll.degree_error >= 0.0f && file->second.roll.minute_error >= 1.0f && file->second.roll.second_error >= 8.0f)
			{
				std::cout << std::format("\033[41m{:>1}°{:>2}'{:>2}\"\033[0m", file->second.roll.degree_error, file->second.roll.minute_error, file->second.roll.second_error);
			}
			else
			{
				std::cout << std::format("{:>1}°{:>2}'{:>2}\"", file->second.roll.degree_error, file->second.roll.minute_error, file->second.roll.second_error);
			}
			std::cout << std::format("{:^9}{:.4f}\n", "Y", file->second.deviation_Y);
			// third row
			std::cout << std::format("{:12}{: 3}{:1}{:5}", "Температура:", (file->second.temperature_X+ file->second.temperature_Y + file->second.temperature_Z) / 3,"°", "C");
			std::cout << std::format("{:6}{:> 5}°{:>2}'{:>2}{:5}", "Тангаж:", file->second.pitch.degree, file->second.pitch.minute, file->second.pitch.second, "\"");
			if (file->second.pitch.degree_error >= 0.0f && file->second.pitch.minute_error >= 1.0f && file->second.pitch.second_error >= 8.0f)
			{
				std::cout << std::format("\033[41m{:>1}°{:>2}'{:>2}\"\033[0m", file->second.pitch.degree_error, file->second.pitch.minute_error, file->second.pitch.second_error);
				
			}
			else
			{
				std::cout << std::format("{:>1}°{:>2}'{:>2}\"", file->second.pitch.degree_error, file->second.pitch.minute_error, file->second.pitch.second_error);
			}
			std::cout << std::format("{:^9}{:.4f}\n\n", "Z", file->second.deviation_Z);
		}
		std::cout << ": ";
	}
	
	Convert::Convert() {}
	
	void Convert::show(const Interaction * i) const noexcept
	{
		std::cout << std::format("[{}]", i->_format == Interaction::Format::DAT ? "DAT" : "TXT");
		std::cout << std::format("{:>12}", "Анализ");
		std::cout << std::format("{:>20}", "[Конвертация]");
		std::cout << std::format("{:>16}", "Сохранить");
		std::cout << std::format("{:>14}\n\n", "Помощь");
		if (i->_converted_files.empty())
		{
			this->show_msg("Введите путь к папке с файлами");
			std::cout << "\n";
		}
		else
		{
			for (const auto & file : i->_converted_files)
			{
				std::cout << file << "\n";
			}
		}
		std::cout << "\n: ";
	}
	
	Write::Write() {}
	
	void Write::show(const Interaction * i) const noexcept
	{
		std::cout << std::format("[{}]", i->_format == Interaction::Format::DAT ? "DAT" : "TXT");
		std::cout << std::format("{:>12}", "Анализ");
		std::cout << std::format("{:>19}", "Конвертация");
		std::cout << std::format("{:>18}", "[Сохранить]");
		std::cout << std::format("{:>13}\n\n", "Помощь");
		if (i->_files.empty())
		{
			this->show_msg("Нет добавленных файлов чтобы сохранить");
		}
		else
		{
			this->show_msg("Введите имя файла");
		}
		std::cout << "\n\n: ";
	}
	
	Help::Help() {}
	
	void Help::show(const Interaction * i) const noexcept
	{
		std::cout << std::format("[{}]", i->_format == Interaction::Format::DAT ? "DAT" : "TXT");
		std::cout << std::format("{:>12}", "Анализ");
		std::cout << std::format("{:>19}", "Конвертация");
		std::cout << std::format("{:>17}", "Сохранить");
		std::cout << std::format("{:>15}\n\n", "[Помощь]");
		this->show_msg("BINS_file_analysis 3.0, Федоров Денис, 2022");
		std::cout << "\n\nЧтобы добавить файлы, предоставьте путь к директории или нажмите 'A' чтобы добавить все .dat\n";
		std::cout << "или .txt файлы в папке, где находится .exe файл. После добавления программа автоматически переключится\n";
		std::cout << "в расширенное меню отображения результатов. При этом красным цветом отмечаются выставки, которые не\n";
		std::cout << "соответствуют требованиям технических условий изделия СГСКЛГ (7.2 угловые минуты для курса, 1.8 для\n";
		std::cout << "крена и тангажа). Результаты можно сохранить в .txt файл, который затем удобно открыть в Microsoft Excel\n";
		std::cout << "с указанием разделителя \"табуляция\". Также доступно преобразование .dat записей TarEmu1 в .txt формат.\n";
		std::cout << "Для этого в меню \"Конвертация\" введите путь к папке с файлами, которые требуется преобразовать. Файлы\n";
		std::cout << "будут сохранены с тем же именем по тому же адресу. Доступные команды (регистр не важен):\n\n";
		std::cout << "'1', '2', '3', '4' переключить меню\n";
		std::cout << "'A' добавить все файлы\n";
		std::cout << "'S' сохранить результаты\n";
		std::cout << "'V' конвертировать файлы\n";
		std::cout << "'C' изменить формат\n";
		std::cout << "'X' выход\n\n";
		std::cout << ": ";
	}
}
