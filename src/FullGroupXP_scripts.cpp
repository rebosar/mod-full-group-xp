/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ConfigValueCache.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "KillRewarder.h"

enum class MyConfig
{
    ENABLED,

    NUM_CONFIGS,
};

class MyConfigData : public ConfigValueCache<MyConfig>
{
public:
    MyConfigData() : ConfigValueCache(MyConfig::NUM_CONFIGS) { };

    void BuildConfigCache() override
    {
        SetConfigValue<bool>(MyConfig::ENABLED, "FullGroupXP.Enable", true);
    }
};

static MyConfigData myConfigData;

// Add player scripts
class MyPlayer : public PlayerScript
{
public:
    MyPlayer() : PlayerScript("MyPlayer", {
        PLAYERHOOK_ON_REWARD_KILL_REWARDER
    }) { }

    void OnPlayerRewardKillRewarder(
        Player* player,
        KillRewarder* /*rewarder*/,
        bool /*isDungeon*/,
        float& rate) override
    {
        if (!myConfigData.GetConfigValue<bool>(MyConfig::ENABLED))
            return;

        rate = 1.0f;
    }
};

class MyWorldScript : public WorldScript
{
public:
    MyWorldScript() : WorldScript("MyWorldScript", {
        WORLDHOOK_ON_BEFORE_CONFIG_LOAD
    }) { }

    void OnBeforeConfigLoad(bool reload) override
    {
        myConfigData.Initialize(reload);
    }
};

// Add all scripts in one
void Addmod_full_group_xpScripts()
{
    new MyPlayer();
    new MyWorldScript();
}
