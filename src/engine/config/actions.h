#ifndef H_ACTIONS
#define H_ACTIONS

#include <string>
#include <vector>

// clang-format off
const std::vector<std::string> ATTACK_UNARMED_ATTACKER =
{
    "ATTACKER swings their fists at your face for DAMAGE damage",
    "ATTACKER slaps you for DAMAGE damage",
    "ATTACKER punches you in the face for DAMAGE damage",
    "ATTACKER wildly flails and smacks you for DAMAGE damage",
    "ATTACKER kicks your stomach for DAMAGE damage"
};

const std::vector<std::string> ATTACK_UNARMED_YOU =
{
    "You beat VICTIM up for DAMAGE damage",
    "You punch VICTIM for DAMAGE damage"
};
// clang-format on

#endif // H_ACTIONS