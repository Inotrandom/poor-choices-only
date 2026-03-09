#ifndef H_ACTOR
#define H_ACTOR

#include "utils.h"
#include <cstdint>

#include <map>
#include <any>
#include <optional>
#include <memory>
#include <vector>
#include <string>

struct damageable_t
{
	std::uint32_t m_health;
	std::uint32_t m_max_health;

	void take_damage(std::uint32_t d)
	{
		m_health -= d;

		if (m_health < m_max_health)
		{
			m_health = 0;
		}

		if (m_health > m_max_health)
		{
			m_health = m_max_health;
		}
	}

	auto is_dead() -> bool
	{
		if (m_health == 0)
		{
			return true;
		}

		return false;
	}
};

enum class ITEM_TYPE : std::uint16_t
{
	WEAPON
};

enum class ITEM_ATTRIBUTE_TYPE : std::uint16_t
{
	DAMAGE,
	USE_TEXT
};

struct item_t
{
	ITEM_TYPE type;
	std::map<ITEM_ATTRIBUTE_TYPE, std::any> dat;

	explicit item_t(ITEM_TYPE atype, std::map<ITEM_ATTRIBUTE_TYPE, std::any> adat = {})
	{
		type = atype;
		dat = adat;
	}

	template <typename T> auto get_data_c(const ITEM_ATTRIBUTE_TYPE attribute_type) -> std::optional<T>
	{
		try
		{
			if (dat.find(attribute_type) == dat.end())
			{
				return std::nullopt;
			}

			return std::any_cast<T>(dat[attribute_type]);
		}
		catch (std::bad_any_cast &e)
		{
			return std::nullopt;
		}
	}

	template <typename T> void set_data(const ITEM_ATTRIBUTE_TYPE attribute_type, const T val)
	{
		if (dat.find(attribute_type) == dat.end())
		{
			return;
		}

		dat[attribute_type] = val;
	}
};

class actor_t
{
public:
	explicit actor_t() {}
	~actor_t() {}

	explicit actor_t(std::uint16_t max_health, std::vector<item_t> inventory)
	{
		m_damageable = {max_health, max_health};
		m_inventory = inventory;
	}

	auto get_weapon() -> std::optional<item_t>
	{
		for (const auto &item : m_inventory)
		{
			if (item.type == ITEM_TYPE::WEAPON)
			{
				return item;
			}
		}

		return std::nullopt;
	}

	void action_attack(std::shared_ptr<actor_t> other)
	{
		std::optional<item_t> weapon = get_weapon();

		std::uint16_t calculated_damage = m_attribute_damage;
		if (weapon.has_value())
		{
			item_t weapon_item = weapon.value();
			std::uint16_t weapon_damage = weapon_item.get_data_c<std::uint16_t>(ITEM_ATTRIBUTE_TYPE::DAMAGE).value();
			calculated_damage += weapon_damage;
		}

		std::uint16_t random_damage = rand_n(calculated_damage);

		other->get_damageable().take_damage(random_damage);
	}

	auto get_damageable() -> damageable_t & { return m_damageable; }

private:
	std::string m_name;

	damageable_t m_damageable = {0, 0};
	std::vector<item_t> m_inventory = {};

	std::uint16_t m_attribute_damage = 5;
};

#endif // H_ACTOR