#ifndef H_CHOICE
#define H_CHOICE

#include <cstdint>

#include <sstream>
#include <iostream>

#include <optional>
#include <vector>
#include <string>

#include "strutils.h"

#define CHOICE_INVALID_ID 0
#define CHOICE_NULL_STRID "undefined"

class choice_t
{
public:
	explicit choice_t() {}
	~choice_t() {}

	explicit choice_t(const std::uint16_t id, const std::string strid, const std::string display)
	{
		m_strid = strid;
		m_id = id;
		m_display = display;
	}

	auto get_id() const -> std::uint16_t { return m_id; }

	auto get_strid() const -> std::string { return m_strid; }

	auto get_display() const -> std::string { return m_display; }

private:
	std::uint16_t m_id = CHOICE_INVALID_ID;
	std::string m_strid = CHOICE_NULL_STRID;
	std::string m_display = CHOICE_NULL_STRID;
};

class choices_t
{
public:
	explicit choices_t() {}
	~choices_t() {}

	auto instantiate_choice(const std::string strid, const std::string display) -> std::uint16_t
	{
		++m_max_id;
		m_choices.emplace_back(m_max_id, strid, display);
		return m_max_id;
	}

	auto parse_choice(std::string which) -> std::string
	{
		std::uint16_t id = CHOICE_INVALID_ID;
		std::stringstream s;
		s << which;
		s >> id;

		if (id == CHOICE_INVALID_ID)
		{
			return CHOICE_NULL_STRID;
		}

		std::optional<choice_t> found = gchoice(id);

		if (found.has_value() == false)
		{
			return CHOICE_NULL_STRID;
		}

		return found->get_strid();
	}

	auto ask() -> std::string
	{
		if (m_choices.size() == 0)
			return CHOICE_NULL_STRID;

		for (const auto &choice : m_choices)
		{
			std::cout << choice.get_id() << "> " << choice.get_display() << "\n";
		}
		std::cout << std::flush;

		std::string buf;
		std::getline(std::cin, buf);
		string_trim(buf);

		return parse_choice(buf);
	}

private:
	auto gchoice(std::uint16_t id) -> std::optional<choice_t>
	{
		for (const auto &choice : m_choices)
		{
			if (choice.get_id() != id)
				continue;

			return choice;
		}

		return std::nullopt;
	}

	std::uint16_t m_max_id = CHOICE_INVALID_ID;
	std::vector<choice_t> m_choices = std::vector<choice_t>();
};

#endif // H_CHOICE