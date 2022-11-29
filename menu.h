//
//  menu.h
//  BINS_file_analysis_3.0
//
//  Created by Denis Fedorov on 25.11.2022.
//

#pragma once
#include <string>
#include <string_view>

namespace FL
{
	class Interaction;
	class Menu
	{
	public:
		Menu();
		virtual ~Menu() = default;
		void clear() const noexcept;
		void send_msg(std::string_view message) noexcept;
		void clear_msg() noexcept;
		virtual void show(const Interaction * i) const noexcept = 0;
	protected:
		void show_msg(std::string_view message) const noexcept;
	protected:
		std::string _message;
	};
	
	class Short : public Menu
	{
	public:
		Short();
		void show(const Interaction * i) const noexcept override;
	};
	
	class Long: public Menu
	{
	public:
		Long();
		void show(const Interaction * i) const noexcept override;
	};
	
	class Convert: public Menu
	{
	public:
		Convert();
		void show(const Interaction * i) const noexcept override;
	};
	
	class Write : public Menu
	{
	public:
		Write();
		void show(const Interaction * i) const noexcept override;
	};
	
	class Help: public Menu
	{
	public:
		Help();
		void show(const Interaction * i) const noexcept override final;
	};
}
