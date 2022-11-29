//
//  interaction.cpp
//  BINS_file_analysis_3.0
//
//  Created by Denis Fedorov on 25.11.2022.
//

#include <iostream>
#include "file.h"
#include "menu.h"
#include "interaction.h"

namespace FL
{
	Interaction::Interaction() : _format(Format::DAT),
	_menu(std::make_unique<Short>()) {}
	
	Interaction::~Interaction() {}
	
	void Interaction::run() noexcept
	{
		bool quit {false};
		std::string input;
		while (!quit)
		{
			_menu->clear();
			_menu->show(this);
			_menu->clear_msg();
			std::getline(std::cin, input);
			if (input.empty())
			{
				continue;
			}
			else if (input.size() < 2)
			{
				switch (input.front())
				{
					case '1':
					{
						if (_files.empty())
						{
							_menu.reset(new Short);
						}
						else
						{
							_menu.reset(new Long);
						}
						break;
					}
					case 'v':
					case 'V':
					case '2':
					{
						_menu.reset(new Convert);
						break;
					}
					case 's':
					case 'S':
					case '3':
					{
						_menu.reset(new Write);
						break;
					}
					case '4':
					{
						_menu.reset(new Help);
						break;
					}
					case 'a':
					case 'A':
					{
						this->check_directory(std::filesystem::current_path().string());
						break;
					}
					case 'c':
					case 'C':
					{
						_format == Format::DAT ? _format = Format::TXT : _format = Format::DAT;
						break;
					}
					case 'x':
					case 'X':
					{
						_menu->clear();
						quit = true;
					}
					default:
					{
						_menu->send_msg("Неизвестная команда");
					}
				}
			}
			else
			{
				if (dynamic_cast<Convert*>(_menu.get()))
				{
					if (std::filesystem::is_directory(input))
					{
						for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(input))
						{
							if (entry.path().filename().extension().string() == ".dat")
							{
								try
								{
									std::unique_ptr<Load> load {std::make_unique<DAT>(entry.path().string())};
									std::filesystem::path temp_path {entry.path().string()};
									temp_path.replace_extension(".txt");
									std::unique_ptr<Save> save {std::make_unique<Save>(temp_path.string())};
									save->write(load->read());
									_converted_files.push_back(std::format("\"{}\" конвертирован", entry.path().string()));
								}
								catch (const std::runtime_error & ex)
								{
									_converted_files.push_back(std::move(ex.what()));
								}
							}
						}
					}
					else
					{
						_menu->send_msg(std::format("\"{}\" неверный путь", input));
					}
				}
				else if (dynamic_cast<Write*>(_menu.get()))
				{
					if (_files.empty())
					{
						_menu->send_msg("Неверный ввод");
					}
					else
					{
						auto path {std::filesystem::current_path()};
						path.replace_filename(input);
						if (!path.has_extension())
						{
							path.replace_extension(".txt");
						}
						std::unique_ptr<Save> save {std::make_unique<Save>(path.string())};
						try
						{
							save->write(_files);
							_menu->send_msg(std::format("\"{}\" успешно записан", path.string()));
						}
						catch(const std::runtime_error & ex)
						{
							_menu->send_msg(std::move(ex.what()));
						}
					}
				}
				else if (std::filesystem::is_regular_file(input))
				{
					this->add(input);
					_menu.reset(new Long);
				}
				else if (std::filesystem::is_directory(input))
				{
					this->check_directory(input);
				}
				else
				{
					_menu->send_msg(std::format("Не удалось открыть \"{}\"", input));
				}
			}
		}
	}
	
	void Interaction::check_directory(std::string_view path) noexcept
	{
		auto new_path {_paths.insert(path.data())};
		if (!new_path.second)
		{
			_menu->send_msg(std::format("Файлы в папке \"{}\" уже добавлены!", *new_path.first));
		}
		else
		{
			auto old_size {_files.size()};
			this->add(new_path.first);
			if (old_size == _files.size())
			{
				_menu->send_msg(std::format("Нет файлов в \"{}\"", *new_path.first));
				_paths.erase(*new_path.first);
			}
			else
			{
				_menu.reset(new Long);
			}
		}
	}
	void Interaction::add(std::set<std::string>::iterator path) noexcept
	{
		std::unique_ptr<Math> math {std::make_unique<Math>()};
		for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(*path))
		{
			if (entry.path().filename().extension().string() == (_format == Format::DAT ? ".dat" : ".txt"))
			{
				try
				{
					if (_format == Format::DAT)
					{
						std::unique_ptr<Load> file {std::make_unique<DAT>(entry.path().string())};
						file->find_start();
						_files.emplace(std::make_pair(entry.path().filename().string(), math->calculation(file->read())));
					}
					else
					{
						std::unique_ptr<Load> file {std::make_unique<TXT>(*path)};
						file->find_start();
						_files.emplace(std::make_pair(entry.path().filename().string(), math->calculation(file->read())));
					}
				}
				catch (const std::runtime_error & ex)
				{
					_errors.push_back(std::move(ex.what()));
				}
				catch (const std::invalid_argument & ex)
				{
					_errors.push_back(std::move(ex.what()) + entry.path().filename().string());
				}
			}
		}
	}
	
	void Interaction::add(const std::filesystem::path & path) noexcept
	{
		std::unique_ptr<Math> math {std::make_unique<Math>()};
		try
		{
			if (path.extension() == ".dat")
			{
				std::unique_ptr<Load> file {std::make_unique<DAT>(path.string())};
				file->find_start();
				_files.emplace(std::make_pair(path.filename().string(), math->calculation(file->read())));
			}
			else
			{
				std::unique_ptr<Load> file {std::make_unique<TXT>(path.string())};
				file->find_start();
				_files.emplace(std::make_pair(path.filename().string(), math->calculation(file->read())));
			}
		}
		catch (const std::runtime_error & ex)
		{
			_errors.push_back(ex.what());
		}
		catch (const std::invalid_argument & ex)
		{
			_errors.push_back(ex.what() + path.filename().string());
		}
	}
}
