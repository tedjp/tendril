# Tendril

> You're a multicellular organism who has just landed on an alien planet. Your goal
> is to take over the planet. Unfortunately another multicellular organism trying
> to do the same, so your job is to destroy it.

Tendril is a simple strategy game. It's a mirror-match 1v1.

It involves imperfect knowledge (fog of war) like Battleship or StarCraft. The goal is to find and destroy your opponent's base before they do the same to you.

It is played on a grid. Probably as small as 4x4 or 5x5 for the introductory level, then slightly larger after that (10x10).

Mechanism:
1. Each player chooses a location on the game board as their base (the Cortex) but does not reveal the location to their opponent.
2. Players take turns "growing" a tendril in a location adjacent to their Cortex or an existing tendril. (In other words, they place an adjacent marker.)
3. When a chosen location already contains an opponent's tendril, the tendril in that location is killed and replaced by the attacker's tendril. Any cells that no longer have a connection to the Cortex are killed. Upon killing an opponent's cell, the player currently taking a turn takes another turn immediately. This can happen repeatedly. (This is the core game loop, the extra turn provides an incentive to make aggressive moves and avoids stalemate.)
4. Play continues until one player grows a tendril to their opponent's Cortex, killing the organism and winning the game.

> The victorious organism is now free to conquer the alien planet unopposed!

A key element is that players only know the location of their opponent's tendrils when they stumble across one in the dark (and brutally destroy it).

## Small scope

The small scope version is a text-based, turn-based version with two players taking turns and not looking at each other's view of the game board, or some simple AI in lieu of a human opponent. That's all.

## AI
Here's an AI algorithm:
1. Try to grow to a cell adjacent to the last-spotted opponent cell (but not your own); otherwise
2. Grow to a cell adjacent to the end of the longest tendril (distance from Cortex); otherwise
3. Grow to a random cell.

## Extensibility

This core game format is extensible in all kinds of directions. It can be text-based or graphical, it can be player-vs-player or player-vs-computer with varying levels of AI. It can be multiplayer with more than two players. The game grid can be scaled up. It can have powerups (more on that below). The AI strategy can be adjusted (aggressive/passive/random/cheat/?). It can be turn based or continuous. There can be animation or simple graphics. There can be sound. It can be played over a network with a game server that holds the full game state and only reveals what each player can see.

## Mutations and mutagens

Powerups are called *mutagens*. They cause *mutations* to the cells that reach them.

After choosing start locations, the map will be sparsely populated with *mutagens*. These are power-ups,
like apples in *Snake*. Mutagen locations are visible through the fog-of-war (ie. immediately).
They provide intermediate goals that drive conflict, and should be no more dense than one-in-25,
in other words one mutagen on a 5x5 grid or up to four on a 10x10 grid. (If random spawning of mutagens
ends up feeling lopsided, they can be randomly-and-symmetrically placed. For example randomly place one and mirror
it twice across the midlines of the game board resulting in four.)

Mutations:
  - Photocell: Grants vision of the blocks immediately adjacent to the mutated cell.
  - Claw: Attacks an adjacent cell automatically at the start of the player's turn (always tries to hit a random non-self cell, but if surrounded, will attack and kill a cell from its own organism).
  - Hyperkeratosis: The cell is granted one point of armor. Upon hit, the opponent will be informed that they hit an armored cell. The armor is destroyed but the attacker does not grow a new cell and is not granted the on-hit extra turn. (Akin to armor in fighting games.)

## Etymology

Cortex isn't really the right term anatomically, it's more of a cerebellum, but cortex sounds cooler.
