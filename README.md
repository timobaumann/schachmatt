# A Generic Minimax Implementation

Minimax helps to solve two-player zero-sum games (i.e., games where one player's win is the other's loss).
The game is always in a state and we compute for a given depth the possible successor states, and that successor's successor states, and so on.
We work under the assumption that each player attempts to play as good as possible. 
As our depth will be limited (often much ) more than the depth of the game, we also like to have a valuation function for each state.

thus, minimax only needs a function that provides all possible successor states to a state, and it needs a function that provides a valuation for a state.

Take a look at minimax.h's requirements for `nachfolgezustandsfunktion` and `zustandsbewertungsfunktion` and then take a look at `minimax.c`.
In case you're interested in chess, take a look at `schach_nachfolgezustaende` and laugh about our valuation function in `schach_zustandsbewertung`.

At present, we neither implement alpha nor beta pruning, which, of course, would be desirable for many games.

