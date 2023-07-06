# MultiplayerShooter

**Description**: This is a multiplayer shooting game made in unreal engine 5. it is a prototype game for me to learn mainly on the replication system in unreal engine. This game consists for 3 different game mode:

| Game Mode        | Description                                                                                      |
| ---------        | ------------------------------------------------------------------------------------------------ |
| Free for all     | Death Match. Everyone is an enemy to everyone. Get as much kill as you can until the game ended. |
| Team Match       | Players are separated into 2 teams. Kill the opponent team to get points.                        |
| Capture the Flag | Capture enemy's team flag and send them back to your base to get point.                          |

## Game Feature of the game
* **A multiplayer session plugin with steam** - This plugin provides api for devs to handle the game session such as create / join / destroy a session
* **Weapon system** - Different weapon type such as hit scan weapon, projectile based weapon, and shotgun (pew pew)
* **Multiple game modes** - Different game modes for player to play on. Each game modes sets specific rules to win the game
* **Attribute Pickup system** - Different attribute related pickup will be spawned randomly by respective spawners that are placed across the game map
* **Multiplayer support with Unreal Replication system** - Allow player to the game through online with steam account using server client model set by unreal engine
* **Lag compensation** - Different lag compensation technique such as client prediction and server-side-rewind are used to handle minor lag (100ping ~ 200ping)

## Demo of the game
[Youtube link](https://youtu.be/6b8HuOOOY04)