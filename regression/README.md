# Regression Cases

These inputs pin the behaviour that regressed when `HEADLIGHTS` was treated as a fatal collision.

## Stage 3.1

- `stage31_headlights_then_car.txt`
  Expected behaviour: the first move onto `HEADLIGHTS` prints Penny as `0_0` and the game continues; the second move onto the car body prints `Game Over`.
- `stage31_headlights_then_leave.txt`
  Expected behaviour: moving onto `HEADLIGHTS` prints Penny as `0_0`; moving off it restores `^_^` and the game continues.

## Stage 3.4

- `stage34_tunnel_scroll_basic.txt`
  Expected behaviour: tunnel travel works in scrolling mode and quitting still prints `============= Quitting Game =============`.
- `stage34_tunnel_scroll_with_blocker.txt`
  Expected behaviour: tunnel travel still resolves correctly when a tree blocks the square beside the tunnel exit.
- `stage34_tunnel_scroll_to_top.txt`
  Expected behaviour: a tunnel destination in the top seven rows still triggers scrolling from Penny's final post-tunnel position.
