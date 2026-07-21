# mod-full-group-xp

An [AzerothCore](https://www.azerothcore.org/) module that removes the XP penalty
normally applied when killing mobs in a group. With this module enabled, every
group member receives full experience per kill, regardless of party size.

## Requirements

- [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk) (Docker setup)

## Installation

1. Clone this module into your AzerothCore `modules` folder:

```bash
   git clone https://github.com/rebosar/mod-full-group-xp.git modules/mod-full-group-xp
```

2. Rebuild your containers so the module gets compiled in:

```bash
   docker compose build ac-worldserver
   docker compose up -d
```

   > If you're building multiple services (e.g. `ac-db-import`, `ac-worldserver`,
   > `ac-authserver`), rebuild whichever ones your compose setup requires. A full
   > clean rebuild can help avoid stale build cache issues after adding a new module:
   >
   > ```bash
   > docker compose build --no-cache
   > docker compose up -d
   > ```

3. Copy the default config file into your mounted config folder and rename it:

```bash
   cp modules/mod-full-group-xp/conf/full_group_xp.conf.dist configs/modules/full_group_xp.conf
```

   > Adjust the destination path to match wherever your `docker-compose.yml`
   > mounts the `etc/modules/` (or `configs/modules/`) directory on the host.

4. Restart the worldserver container to pick up the new config:

```bash
   docker compose restart ac-worldserver
```

## Configuration

Edit `full_group_xp.conf` to configure the module:

| Option                | Description                          | Default |
|------------------------|---------------------------------------|---------|
| `FullGroupXP.Enable`   | Enable or disable the module (1/0)   | `1`     |

## How it works

By default, AzerothCore reduces the XP awarded per kill based on how many
players are in the group sharing credit for that kill. This module hooks into
`OnPlayerRewardKillRewarder` and, when enabled, forces the XP rate multiplier
to `1.0`, removing the group-size penalty entirely.

## License

This module is released under the GNU AGPL v3 license, in line with
AzerothCore. See [LICENSE](LICENSE) for details.

## Contributing

Issues and pull requests are welcome.
