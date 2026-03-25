// cs_chicken.c
// Written by <INSERT YOUR FULL NAME> <INSERT YOUR ZID> on <INSERT DATE>
//
// Description: CS Chicken implementation up to Stage 2.2

// Provided Libraries
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Add your own #include statements below this line

// Provided constants
#define COLS 10
#define ROWS 10
#define INVALID_ROW -1
#define INVALID_COL -1
#define INITIAL_POINTS 0
#define DEFAULT_POINT_TARGET 20
#define MAX_TUNNELS 10
#define INVALID_TUNNEL_ID -1

// Add your own #define constants below this line
// Provided Enums
// Enum for features on the game board
enum entity {
    EMPTY,
    COIN,
    TREE,
    ROAD,
    CAR_FACING_RIGHT,
    CAR_FACING_LEFT,
    HEADLIGHTS,
    KANGAROO,
    WOMBAT_TUNNEL,
    BABY_CHICKEN
};

// Add your own enums below this line
enum game_mode {
    STATIC_MODE,
    DRIVING_MODE,
    SCROLLING_MODE
};

// Represents a tile on the board (you may edit this and add your own fields)
struct tile {
    enum entity entity;
    int tunnel_id;
};

// Add your own structs below this line

// Provided Function Prototypes
void print_welcome(void);
void initialise_board(struct tile board[ROWS][COLS]);
void print_board(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int curr_score,
    int target_score
);
void print_board_line(void);
void print_board_footer(int curr_score, int target_score);
void print_game_statistics(
    int turns_taken,
    int step_count,
    int coins,
    int score
);

// Additional Function Prototypes
void print_game_won(void);
void print_game_lost(void);

// Add your own function prototypes below this line
void print_setup_phase_banner(void);
void read_starting_position(int *player_row, int *player_col);
int is_position_on_board(int row, int col);
int is_tile_occupied(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int col
);
void place_basic_feature(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    enum entity feature
);
int can_build_road(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int *deforesting
);
void build_road(struct tile board[ROWS][COLS], int row);
void place_car(
    struct tile board[ROWS][COLS],
    int row,
    int col,
    char direction
);
int process_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id,
    int *target_score,
    char command
);
void start_gameplay_phase(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
);
void process_gameplay_phase(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *last_move_used_tunnel,
    enum game_mode mode
);
int process_player_move(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *last_move_used_tunnel,
    char command
);
void update_destination_from_command(
    char command,
    int *destination_row,
    int *destination_col
);
int is_valid_player_destination(
    struct tile board[ROWS][COLS],
    int row,
    int col
);
int resolve_tunnel_move(
    struct tile board[ROWS][COLS],
    int original_row,
    int original_col,
    int *player_row,
    int *player_col,
    int *last_move_used_tunnel,
    char command
);
int find_tunnel_exit(
    struct tile board[ROWS][COLS],
    int entry_row,
    int entry_col,
    int *exit_row,
    int *exit_col
);
int is_gameplay_move_command(char command);
void collect_coin(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *score,
    int *coins_collected
);
void handle_road_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
);
void handle_car_setup_command(struct tile board[ROWS][COLS]);
void handle_target_setup_command(int *target_score);
int handle_wombat_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id
);
int read_wombat_tunnel_command(char *subcommand);
int can_place_wombat_tunnel(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int col
);
void place_wombat_tunnel_pair(
    struct tile board[ROWS][COLS],
    int row_1,
    int col_1,
    int row_2,
    int col_2,
    int tunnel_id
);
int dispatch_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id,
    int *target_score,
    char command
);
int process_gameplay_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
);
int process_driving_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
);
int process_turn_by_mode(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int *last_move_used_tunnel,
    enum game_mode mode,
    char command
);
int process_scrolling_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int *last_move_used_tunnel,
    char command
);
void initialise_scrolling_coin_map(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS]
);
void rotate_board_rows(
    struct tile board[ROWS][COLS],
    int row_ids[ROWS]
);
void restore_top_row_coins(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS],
    int row_ids[ROWS]
);
int handle_game_won(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
);
int should_attempt_scroll(
    int command,
    int original_row,
    int successful_move,
    int last_move_used_tunnel
);
int should_attempt_tunnel_scroll(
    int successful_move,
    int last_move_used_tunnel,
    int player_row
);
int can_scroll_player_to_top(
    struct tile board[ROWS][COLS],
    int player_at_top_before_scroll,
    int player_col
);
int attempt_scroll(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int player_at_top_before_scroll,
    int keep_player_on_top_after_scroll,
    int moved_up
);
int finish_scroll_after_rotation(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int keep_player_on_top_after_scroll
);
int handle_tunnel_under_player(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
);
int finish_scrolling_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int command,
    int original_row,
    int last_move_used_tunnel,
    int successful_move
);
int try_finish_scroll_with_board_rotation(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int command,
    int original_row,
    int last_move_used_tunnel,
    int successful_move
);
int handle_gameplay_status_command(
    int turns_taken,
    int step_count,
    int coins_collected,
    int score,
    char command
);
int handle_move_and_pre_scroll_checks(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command,
    int *original_row,
    int *successful_move
);
int handle_scroll_post_move_checks(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
);
void apply_gameplay_move(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
);
int finish_gameplay_turn(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
);
int is_player_shocked(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
);
int handle_collision(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
);
int is_valid_car_destination(
    struct tile board[ROWS][COLS],
    int row,
    int col
);
void clear_headlights(struct tile board[ROWS][COLS]);
void refresh_headlights(struct tile board[ROWS][COLS]);
void process_left_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
);
void process_right_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
);
void run_car_turn(struct tile board[ROWS][COLS]);
enum game_mode read_setup_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id,
    int *target_score
);
void run_game(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *last_move_used_tunnel,
    enum game_mode mode
);
int finish_driving_turn_before_cars(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
);
int prepare_driving_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
);

// Provided sample main() function (you will need to modify this)
int main(void) {
    struct tile board[ROWS][COLS];
    int player_row = INVALID_ROW;
    int player_col = INVALID_COL;
    int score = INITIAL_POINTS;
    int target_score = DEFAULT_POINT_TARGET;
    int next_tunnel_id = 0;
    int last_move_used_tunnel = 0;
    enum game_mode mode = STATIC_MODE;

    print_welcome();
    initialise_board(board);

    print_setup_phase_banner();
    read_starting_position(&player_row, &player_col);
    if (!is_position_on_board(player_row, player_col)) {
        return 0;
    }

    mode = read_setup_mode(
        board,
        player_row,
        player_col,
        &next_tunnel_id,
        &target_score
    );
    run_game(
        board,
        &player_row,
        &player_col,
        &score,
        target_score,
        &last_move_used_tunnel,
        mode
    );
    return 0;
}

enum game_mode read_setup_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id,
    int *target_score
) {
    char command;
    enum game_mode mode = STATIC_MODE;

    print_board(board, player_row, player_col, INITIAL_POINTS, *target_score);
    printf("Enter setup commands:\n");
    while (scanf(" %c", &command) == 1) {
        if (command == 'e') {
            return mode;
        }
        if (command == 'd') {
            return DRIVING_MODE;
        }
        if (command == 's') {
            return SCROLLING_MODE;
        }
        process_setup_command(
            board,
            player_row,
            player_col,
            next_tunnel_id,
            target_score,
            command
        );
    }
    return mode;
}

void run_game(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *last_move_used_tunnel,
    enum game_mode mode
) {
    start_gameplay_phase(
        board,
        *player_row,
        *player_col,
        *score,
        target_score
    );
    process_gameplay_phase(
        board,
        player_row,
        player_col,
        score,
        target_score,
        last_move_used_tunnel,
        mode
    );
}

void print_setup_phase_banner(void) {
    printf("============== Setup Phase ==============\n");
}

void read_starting_position(int *player_row, int *player_col) {
    while (!is_position_on_board(*player_row, *player_col)) {
        printf("Enter the starting position: ");
        if (scanf("%d %d", player_row, player_col) != 2) {
            return;
        }

        if (!is_position_on_board(*player_row, *player_col)) {
            printf("Penny the Chicken cannot start here!\n");
        }
    }
}

int process_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id,
    int *target_score,
    char command
) {
    return dispatch_setup_command(
        board,
        player_row,
        player_col,
        next_tunnel_id,
        target_score,
        command
    );
}

int read_wombat_tunnel_command(char *subcommand) {
    return scanf(" %c", subcommand) == 1;
}

int can_place_wombat_tunnel(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int col
) {
    return is_position_on_board(row, col)
        && !is_tile_occupied(board, player_row, player_col, row, col);
}

void place_wombat_tunnel_pair(
    struct tile board[ROWS][COLS],
    int row_1,
    int col_1,
    int row_2,
    int col_2,
    int tunnel_id
) {
    board[row_1][col_1].entity = WOMBAT_TUNNEL;
    board[row_1][col_1].tunnel_id = tunnel_id;
    board[row_2][col_2].entity = WOMBAT_TUNNEL;
    board[row_2][col_2].tunnel_id = tunnel_id;
}

int handle_wombat_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id
) {
    int row_1;
    int col_1;
    int row_2;
    int col_2;

    if (scanf("%d %d %d %d", &row_1, &col_1, &row_2, &col_2) != 4) {
        return 1;
    }
    if (*next_tunnel_id >= MAX_TUNNELS) {
        printf("Invalid feature: too many tunnels!\n");
        return 1;
    }
    if (row_1 == row_2 && col_1 == col_2) {
        printf("Invalid location: wombat couldn't dig a tunnel here!\n");
        return 1;
    }
    if (!can_place_wombat_tunnel(board, player_row, player_col, row_1, col_1)
        || !can_place_wombat_tunnel(
            board, player_row, player_col, row_2, col_2
        )) {
        printf("Invalid location: wombat couldn't dig a tunnel here!\n");
        return 1;
    }

    place_wombat_tunnel_pair(board, row_1, col_1, row_2, col_2,
        *next_tunnel_id);
    (*next_tunnel_id)++;
    return 1;
}

void start_gameplay_phase(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
) {
    print_board(board, player_row, player_col, score, target_score);
    printf("============ Gameplay Phase =============\n");
}

void process_gameplay_phase(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *last_move_used_tunnel,
    enum game_mode mode
) {
    int turns_taken = 0;
    int step_count = 0;
    int coins_collected = 0;
    int coin_map[ROWS][COLS] = {{0}};
    int row_ids[ROWS];
    char command;

    initialise_scrolling_coin_map(board, coin_map);
    for (int row = 0; row < ROWS; row++) {
        row_ids[row] = row;
    }

    while (scanf(" %c", &command) == 1) {
        if (process_turn_by_mode(
                board,
                player_row,
                player_col,
                score,
                target_score,
                &turns_taken,
                &step_count,
                &coins_collected,
                coin_map,
                row_ids,
                last_move_used_tunnel,
                mode,
                command
            )) {
            return;
        }
    }
}

int process_turn_by_mode(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int *last_move_used_tunnel,
    enum game_mode mode,
    char command
) {
    if (mode == SCROLLING_MODE) {
        return process_scrolling_turn(board, player_row, player_col, score,
            target_score, turns_taken, step_count, coins_collected, coin_map,
            row_ids, last_move_used_tunnel, command);
    }
    if (mode == DRIVING_MODE) {
        return process_driving_turn(board, player_row, player_col, score,
            target_score, turns_taken, step_count, coins_collected,
            last_move_used_tunnel, command);
    }
    return process_gameplay_turn(board, player_row, player_col, score,
        target_score, turns_taken, step_count, coins_collected,
        last_move_used_tunnel, command);
}

int process_gameplay_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
) {
    if (handle_gameplay_status_command(
            *turns_taken,
            *step_count,
            *coins_collected,
            *score,
            command
        )) {
        return 1;
    }
    if (!is_gameplay_move_command(command)) {
        return 0;
    }

    (*turns_taken)++;
    apply_gameplay_move(
        board,
        player_row,
        player_col,
        score,
        step_count,
        coins_collected,
        last_move_used_tunnel,
        command
    );
    return finish_gameplay_turn(
        board,
        *player_row,
        *player_col,
        *score,
        target_score,
        *turns_taken,
        *step_count,
        *coins_collected
    );
}

int process_driving_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
) {
    int turn_ready = prepare_driving_turn(
        board,
        player_row,
        player_col,
        score,
        turns_taken,
        step_count,
        coins_collected,
        last_move_used_tunnel,
        command
    );

    if (turn_ready < 0) {
        return 1;
    }
    if (turn_ready != 1) {
        return turn_ready;
    }
    if (finish_driving_turn_before_cars(board, *player_row, *player_col,
            *score, target_score, *turns_taken, *step_count,
            *coins_collected)) {
        return 1;
    }

    run_car_turn(board);
    return finish_gameplay_turn(board, *player_row, *player_col, *score,
        target_score, *turns_taken, *step_count, *coins_collected);
}

int prepare_driving_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
) {
    if (command == 'q') {
        printf("============= Quitting Game =============\n");
        return -1;
    }
    if (command == 'p') {
        print_game_statistics(
            *turns_taken,
            *step_count,
            *coins_collected,
            *score
        );
        return 0;
    }
    if (!is_gameplay_move_command(command)) {
        return 0;
    }

    (*turns_taken)++;
    apply_gameplay_move(board, player_row, player_col, score,
        step_count, coins_collected, last_move_used_tunnel, command);
    return 1;
}

int finish_driving_turn_before_cars(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
) {
    if (handle_collision(
            board,
            player_row,
            player_col,
            score,
            target_score,
            turns_taken,
            step_count,
            coins_collected
        )) {
        return 1;
    }
    return handle_game_won(
        board,
        player_row,
        player_col,
        score,
        target_score,
        turns_taken,
        step_count,
        coins_collected
    );
}

int process_scrolling_turn(struct tile board[ROWS][COLS], int *player_row,
    int *player_col, int *score, int target_score, int *turns_taken,
    int *step_count, int *coins_collected, int coin_map[ROWS][COLS],
    int row_ids[ROWS], int *last_move_used_tunnel, char command) {
    int original_row = 0;
    int successful_move = 0;

    if (handle_move_and_pre_scroll_checks(board, player_row, player_col, score,
            turns_taken, step_count, coins_collected, last_move_used_tunnel,
            command, &original_row, &successful_move)) {
        return 1;
    }
    if (!is_gameplay_move_command(command)) {
        return 0;
    }

    if (handle_scroll_post_move_checks(board, *player_row, *player_col, *score,
            target_score, *turns_taken, *step_count, *coins_collected)) {
        return 1;
    }

    return finish_scrolling_turn(board, player_row, *player_col, score,
        target_score, turns_taken, step_count, coins_collected, coin_map,
        row_ids, command, original_row, *last_move_used_tunnel,
        successful_move);
}

int handle_move_and_pre_scroll_checks(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command,
    int *original_row,
    int *successful_move
) {
    int original_step_count = *step_count;

    if (handle_gameplay_status_command(*turns_taken, *step_count,
            *coins_collected, *score, command)) {
        return 1;
    }
    *original_row = *player_row;
    if (!is_gameplay_move_command(command)) {
        return 0;
    }

    (*turns_taken)++;
    apply_gameplay_move(board, player_row, player_col, score, step_count,
        coins_collected, last_move_used_tunnel, command);
    *successful_move = *step_count > original_step_count;
    return 0;
}

int handle_scroll_post_move_checks(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
) {
    if (handle_collision(board, player_row, player_col, score, target_score,
            turns_taken, step_count, coins_collected)) {
        return 1;
    }
    return handle_game_won(board, player_row, player_col, score, target_score,
        turns_taken, step_count, coins_collected);
}

int handle_game_won(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
) {
    if (score < target_score) {
        return 0;
    }

    print_board(board, player_row, player_col, score, target_score);
    print_game_statistics(turns_taken, step_count, coins_collected, score);
    print_game_won();
    return 1;
}

void initialise_scrolling_coin_map(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS]
) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            coin_map[row][col] = board[row][col].entity == COIN;
        }
    }
}

void rotate_board_rows(
    struct tile board[ROWS][COLS],
    int row_ids[ROWS]
) {
    struct tile bottom_row[COLS];
    int bottom_row_id = row_ids[ROWS - 1];

    for (int col = 0; col < COLS; col++) {
        bottom_row[col] = board[ROWS - 1][col];
    }
    for (int row = ROWS - 1; row > 0; row--) {
        for (int col = 0; col < COLS; col++) {
            board[row][col] = board[row - 1][col];
        }
        row_ids[row] = row_ids[row - 1];
    }
    for (int col = 0; col < COLS; col++) {
        board[0][col] = bottom_row[col];
    }
    row_ids[0] = bottom_row_id;
}

void restore_top_row_coins(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS],
    int row_ids[ROWS]
) {
    int source_row = row_ids[0];

    for (int col = 0; col < COLS; col++) {
        if (coin_map[source_row][col] && board[0][col].entity == EMPTY) {
            board[0][col].entity = COIN;
        }
    }
}

int should_attempt_scroll(
    int command,
    int original_row,
    int successful_move,
    int last_move_used_tunnel
) {
    return !last_move_used_tunnel
        && command == 'w'
        && (original_row == 0 || (original_row <= 6 && successful_move));
}

int should_attempt_tunnel_scroll(
    int successful_move,
    int last_move_used_tunnel,
    int player_row
) {
    return successful_move && last_move_used_tunnel && player_row <= 6;
}

int can_scroll_player_to_top(
    struct tile board[ROWS][COLS],
    int player_at_top_before_scroll,
    int player_col
) {
    if (!player_at_top_before_scroll) {
        return 1;
    }

    return board[ROWS - 1][player_col].entity != TREE;
}

int attempt_scroll(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int player_at_top_before_scroll,
    int keep_player_on_top_after_scroll,
    int moved_up
) {
    if (!player_at_top_before_scroll && !moved_up) {
        return 0;
    }
    if (player_at_top_before_scroll && keep_player_on_top_after_scroll
        && !can_scroll_player_to_top(
            board, player_at_top_before_scroll, player_col
        )) {
        return 0;
    }

    rotate_board_rows(board, row_ids);
    restore_top_row_coins(board, coin_map, row_ids);
    return finish_scroll_after_rotation(board, player_row, player_col, score,
        target_score, turns_taken, step_count, coins_collected, coin_map,
        row_ids, keep_player_on_top_after_scroll);
}

int finish_scroll_after_rotation(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int keep_player_on_top_after_scroll
) {
    int last_move_used_tunnel = 0;

    (void) coin_map;
    (void) row_ids;
    if (keep_player_on_top_after_scroll) {
        *player_row = 0;
        (*step_count)++;
        collect_coin(board, *player_row, player_col, score, coins_collected);
    } else {
        (*player_row)++;
    }

    handle_tunnel_under_player(
        board,
        player_row,
        &player_col,
        score,
        coins_collected,
        &last_move_used_tunnel,
        'w'
    );

    if (handle_collision(
            board,
            *player_row,
            player_col,
            *score,
            target_score,
            *turns_taken,
            *step_count,
            *coins_collected
        )) {
        return 1;
    }

    return handle_game_won(
        board,
        *player_row,
        player_col,
        *score,
        target_score,
        *turns_taken,
        *step_count,
        *coins_collected
    );
}

int handle_tunnel_under_player(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
) {
    int original_row = *player_row;
    int original_col = *player_col;

    if (board[*player_row][*player_col].entity != WOMBAT_TUNNEL) {
        return 0;
    }

    if (!resolve_tunnel_move(
            board,
            original_row,
            original_col,
            player_row,
            player_col,
            last_move_used_tunnel,
            command
        )) {
        return 0;
    }

    collect_coin(board, *player_row, *player_col, score, coins_collected);
    return 1;
}

int finish_scrolling_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int command,
    int original_row,
    int last_move_used_tunnel,
    int successful_move
) {
    run_car_turn(board);
    if (handle_collision(
            board,
            *player_row,
            player_col,
            *score,
            target_score,
            *turns_taken,
            *step_count,
            *coins_collected
        )) {
        return 1;
    }

    if (try_finish_scroll_with_board_rotation(
            board,
            player_row,
            player_col,
            score,
            target_score,
            turns_taken,
            step_count,
            coins_collected,
            coin_map,
            row_ids,
            command,
            original_row,
            last_move_used_tunnel,
            successful_move
        )) {
        return 1;
    }

    print_board(board, *player_row, player_col, *score, target_score);
    return 0;
}

int try_finish_scroll_with_board_rotation(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int command,
    int original_row,
    int last_move_used_tunnel,
    int successful_move
) {
    if (should_attempt_scroll(command, original_row, successful_move,
            last_move_used_tunnel)) {
        return attempt_scroll(
            board,
            player_row,
            player_col,
            score,
            target_score,
            turns_taken,
            step_count,
            coins_collected,
            coin_map,
            row_ids,
            original_row == 0,
            original_row == 0,
            successful_move
        );
    }
    if (should_attempt_tunnel_scroll(successful_move, last_move_used_tunnel,
            *player_row)) {
        return attempt_scroll(
            board,
            player_row,
            player_col,
            score,
            target_score,
            turns_taken,
            step_count,
            coins_collected,
            coin_map,
            row_ids,
            *player_row == 0,
            0,
            1
        );
    }
    return 0;
}

int process_player_move(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *last_move_used_tunnel,
    char command
) {
    int original_row = *player_row;
    int original_col = *player_col;
    int destination_row = *player_row;
    int destination_col = *player_col;

    *last_move_used_tunnel = 0;
    if (command == 'R') {
        return 1;
    }
    if (!is_gameplay_move_command(command)) {
        return 0;
    }

    update_destination_from_command(
        command,
        &destination_row,
        &destination_col
    );

    if (!is_valid_player_destination(board, destination_row, destination_col)) {
        return 0;
    }

    *player_row = destination_row;
    *player_col = destination_col;
    if (board[destination_row][destination_col].entity == WOMBAT_TUNNEL) {
        return resolve_tunnel_move(
            board,
            original_row,
            original_col,
            player_row,
            player_col,
            last_move_used_tunnel,
            command
        );
    }
    return 1;
}

void update_destination_from_command(
    char command,
    int *destination_row,
    int *destination_col
) {
    if (command == 'w') {
        (*destination_row)--;
    } else if (command == 'a') {
        (*destination_col)--;
    } else if (command == 's') {
        (*destination_row)++;
    } else if (command == 'd') {
        (*destination_col)++;
    }
}

int is_valid_player_destination(
    struct tile board[ROWS][COLS],
    int row,
    int col
) {
    return is_position_on_board(row, col)
        && board[row][col].entity != TREE;
}

int resolve_tunnel_move(
    struct tile board[ROWS][COLS],
    int original_row,
    int original_col,
    int *player_row,
    int *player_col,
    int *last_move_used_tunnel,
    char command
) {
    int exit_row;
    int exit_col;

    if (!find_tunnel_exit(
            board, *player_row, *player_col, &exit_row, &exit_col
        )) {
        *player_row = original_row;
        *player_col = original_col;
        return 0;
    }

    update_destination_from_command(command, &exit_row, &exit_col);
    if (!is_valid_player_destination(board, exit_row, exit_col)) {
        *player_row = original_row;
        *player_col = original_col;
        return 0;
    }

    *player_row = exit_row;
    *player_col = exit_col;
    *last_move_used_tunnel = 1;
    return 1;
}

int find_tunnel_exit(
    struct tile board[ROWS][COLS],
    int entry_row,
    int entry_col,
    int *exit_row,
    int *exit_col
) {
    int tunnel_id = board[entry_row][entry_col].tunnel_id;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if ((row != entry_row || col != entry_col)
                && board[row][col].entity == WOMBAT_TUNNEL
                && board[row][col].tunnel_id == tunnel_id) {
                *exit_row = row;
                *exit_col = col;
                return 1;
            }
        }
    }
    return 0;
}

int is_gameplay_move_command(char command) {
    return command == 'w' || command == 'a' || command == 's'
        || command == 'd' || command == 'R';
}

void collect_coin(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *score,
    int *coins_collected
) {
    if (board[player_row][player_col].entity == COIN) {
        board[player_row][player_col].entity = EMPTY;
        *score += 5;
        (*coins_collected)++;
    }
}

int is_position_on_board(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int is_tile_occupied(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int col
) {
    return (row == player_row && col == player_col)
        || board[row][col].entity != EMPTY;
}

void place_basic_feature(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    enum entity feature
) {
    int row;
    int col;

    if (scanf("%d %d", &row, &col) == 2) {
        if (!is_position_on_board(row, col)) {
            printf("Invalid location: position is not on map!\n");
        } else if (is_tile_occupied(board, player_row, player_col, row, col)) {
            printf("Invalid location: tile is occupied!\n");
        } else {
            board[row][col].entity = feature;
            board[row][col].tunnel_id = INVALID_TUNNEL_ID;
        }
    }
}

void handle_road_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
) {
    int row;
    int deforesting;

    if (scanf("%d", &row) != 1) {
        return;
    }
    if (!is_position_on_board(row, 0)) {
        printf("Invalid location: position is not on map!\n");
        return;
    }
    if (!can_build_road(board, player_row, player_col, row, &deforesting)) {
        printf("Invalid location: road cannot be built.\n");
        return;
    }
    if (deforesting) {
        printf("Deforesting.\n");
    }
    build_road(board, row);
}

void handle_car_setup_command(struct tile board[ROWS][COLS]) {
    int row;
    int col;
    char direction;

    if (scanf("%d %d %c", &row, &col, &direction) != 3) {
        return;
    }
    if (!is_position_on_board(row, col)) {
        printf("Invalid location: position is not on map!\n");
        return;
    }
    if (board[row][col].entity != ROAD
        && board[row][col].entity != HEADLIGHTS) {
        printf("Invalid location: car must be on a road.\n");
        return;
    }

    place_car(board, row, col, direction);
}

void handle_target_setup_command(int *target_score) {
    int points;

    if (scanf("%d", &points) != 1) {
        return;
    }
    if (points < 1 || points > 99) {
        printf("Target must be between 1 and 99 inclusive.\n");
        return;
    }

    *target_score = points;
}

int dispatch_setup_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *next_tunnel_id,
    int *target_score,
    char command
) {
    char subcommand;
    enum entity feature;

    if (command == 'c' || command == 't') {
        if (command == 'c') {
            feature = COIN;
        } else {
            feature = TREE;
        }
        place_basic_feature(board, player_row, player_col, feature);
        return 1;
    }
    if (command == 'r') {
        handle_road_setup_command(board, player_row, player_col);
        return 1;
    }
    if (command == 'v') {
        handle_car_setup_command(board);
        return 1;
    }
    if (command == 'x') {
        handle_target_setup_command(target_score);
        return 1;
    }
    if (command == 'w') {
        if (read_wombat_tunnel_command(&subcommand) && subcommand == 't') {
            return handle_wombat_setup_command(
                board,
                player_row,
                player_col,
                next_tunnel_id
            );
        }
        return 0;
    }
    return 0;
}

int handle_gameplay_status_command(
    int turns_taken,
    int step_count,
    int coins_collected,
    int score,
    char command
) {
    if (command == 'q') {
        printf("============= Quitting Game =============\n");
        return 1;
    }
    if (command == 'p') {
        print_game_statistics(turns_taken, step_count, coins_collected, score);
        return 0;
    }
    return 0;
}

void apply_gameplay_move(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int *step_count,
    int *coins_collected,
    int *last_move_used_tunnel,
    char command
) {
    int successful_move;

    if (command == 'R') {
        return;
    }
    successful_move = process_player_move(
        board,
        player_row,
        player_col,
        last_move_used_tunnel,
        command
    );
    *step_count += successful_move;
    if (successful_move) {
        collect_coin(board, *player_row, *player_col, score, coins_collected);
    }
}

int finish_gameplay_turn(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
) {
    if (handle_collision(
            board,
            player_row,
            player_col,
            score,
            target_score,
            turns_taken,
            step_count,
            coins_collected
        )) {
        return 1;
    }

    print_board(board, player_row, player_col, score, target_score);
    if (score < target_score) {
        return 0;
    }
    print_game_statistics(turns_taken, step_count, coins_collected, score);
    print_game_won();
    return 1;
}

int is_player_shocked(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
) {
    enum entity tile = board[player_row][player_col].entity;

    return tile == HEADLIGHTS
        || tile == CAR_FACING_LEFT
        || tile == CAR_FACING_RIGHT;
}

int handle_collision(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
) {
    enum entity tile = board[player_row][player_col].entity;

    if (tile != CAR_FACING_LEFT && tile != CAR_FACING_RIGHT) {
        return 0;
    }

    print_board(board, player_row, player_col, score, target_score);
    print_game_statistics(turns_taken, step_count, coins_collected, score);
    print_game_lost();
    return 1;
}

int is_valid_car_destination(
    struct tile board[ROWS][COLS],
    int row,
    int col
) {
    if (!is_position_on_board(row, col)) {
        return 0;
    }

    return board[row][col].entity == ROAD
        || board[row][col].entity == HEADLIGHTS;
}

void clear_headlights(struct tile board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col].entity == HEADLIGHTS) {
                board[row][col].entity = ROAD;
            }
        }
    }
}

void refresh_headlights(struct tile board[ROWS][COLS]) {
    clear_headlights(board);

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col].entity == CAR_FACING_RIGHT
                && is_position_on_board(row, col + 1)
                && board[row][col + 1].entity == ROAD) {
                board[row][col + 1].entity = HEADLIGHTS;
            } else if (board[row][col].entity == CAR_FACING_LEFT
                && is_position_on_board(row, col - 1)
                && board[row][col - 1].entity == ROAD) {
                board[row][col - 1].entity = HEADLIGHTS;
            }
        }
    }
}

void process_left_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (moved[row][col] || board[row][col].entity != CAR_FACING_LEFT) {
                continue;
            }
            if (is_valid_car_destination(board, row, col - 1)) {
                board[row][col].entity = ROAD;
                board[row][col - 1].entity = CAR_FACING_LEFT;
                moved[row][col - 1] = 1;
            } else {
                board[row][col].entity = CAR_FACING_RIGHT;
                moved[row][col] = 1;
            }
        }
    }
}

void process_right_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = COLS - 1; col >= 0; col--) {
            if (moved[row][col] || board[row][col].entity != CAR_FACING_RIGHT) {
                continue;
            }
            if (is_valid_car_destination(board, row, col + 1)) {
                board[row][col].entity = ROAD;
                board[row][col + 1].entity = CAR_FACING_RIGHT;
                moved[row][col + 1] = 1;
            } else {
                board[row][col].entity = CAR_FACING_LEFT;
                moved[row][col] = 1;
            }
        }
    }
}

void run_car_turn(struct tile board[ROWS][COLS]) {
    int moved[ROWS][COLS] = {{0}};

    process_left_facing_cars(board, moved);
    process_right_facing_cars(board, moved);
    refresh_headlights(board);
}

int can_build_road(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int *deforesting
) {
    int col;

    *deforesting = 0;
    for (col = 0; col < COLS; col++) {
        if (row == player_row && col == player_col) {
            return 0;
        }
        if (board[row][col].entity == COIN
            || board[row][col].entity == CAR_FACING_RIGHT
            || board[row][col].entity == CAR_FACING_LEFT
            || board[row][col].entity == HEADLIGHTS
            || board[row][col].entity == WOMBAT_TUNNEL) {
            return 0;
        }
        if (board[row][col].entity == TREE) {
            *deforesting = 1;
        }
    }

    return 1;
}

void build_road(struct tile board[ROWS][COLS], int row) {
    int col;

    for (col = 0; col < COLS; col++) {
        board[row][col].entity = ROAD;
        board[row][col].tunnel_id = INVALID_TUNNEL_ID;
    }
}

void place_car(
    struct tile board[ROWS][COLS],
    int row,
    int col,
    char direction
) {
    if (direction == 'r') {
        board[row][col].entity = CAR_FACING_RIGHT;
        board[row][col].tunnel_id = INVALID_TUNNEL_ID;
        if (col + 1 < COLS && board[row][col + 1].entity == ROAD) {
            board[row][col + 1].entity = HEADLIGHTS;
            board[row][col + 1].tunnel_id = INVALID_TUNNEL_ID;
        }
    } else if (direction == 'l') {
        board[row][col].entity = CAR_FACING_LEFT;
        board[row][col].tunnel_id = INVALID_TUNNEL_ID;
        if (col - 1 >= 0 && board[row][col - 1].entity == ROAD) {
            board[row][col - 1].entity = HEADLIGHTS;
            board[row][col - 1].tunnel_id = INVALID_TUNNEL_ID;
        }
    }
}

// =============================================================================
// Provided Helper Functions
// =============================================================================

// Prints the game's welcome banner
void print_welcome(void) {
    printf(
        "_________________________________________   \n"
        "   \\\\                               \\\\  \n"
        "   (o>   !!    Welcome to    !!     (o>     \n"
        "\\\\_//)         CS CHICKEN        \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}

// Given a 2D board array, initialises all tile entities to EMPTY.
void initialise_board(struct tile board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].entity = EMPTY;
            board[row][col].tunnel_id = INVALID_TUNNEL_ID;
        }
    }
}

// Prints the game board, showing the player's position, current score and
// target score
void print_board(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int curr_score,
    int target_score
) {
    print_board_line();
    printf("|          C S   C H I C K E N          |\n");
    print_board_line();

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            printf("|");
            if (row == player_row && col == player_col) {
                if (is_player_shocked(board, player_row, player_col)) {
                    printf("0_0");
                } else {
                    printf("^_^");
                }
            } else if (board[row][col].entity == WOMBAT_TUNNEL) {
                printf("(%d)", board[row][col].tunnel_id);
            } else if (board[row][col].entity == EMPTY) {
                printf("   ");
            } else if (board[row][col].entity == COIN) {
                printf(" c ");
            } else if (board[row][col].entity == TREE) {
                printf(" T ");
            } else if (board[row][col].entity == ROAD) {
                printf("___");
            } else if (board[row][col].entity == CAR_FACING_RIGHT) {
                printf("[_0");
            } else if (board[row][col].entity == CAR_FACING_LEFT) {
                printf("0_]");
            } else if (board[row][col].entity == HEADLIGHTS) {
                printf("###");
            } else {
                printf("   ");
            }
        }
        printf("|\n");
        print_board_line();
    }

    print_board_footer(curr_score, target_score);
    printf("\n");
}

// Helper function to print statistics.
// Use in Stage 2.3.
void print_game_statistics(
    int turns_taken,
    int step_count,
    int coins,
    int score
) {
    printf(
        "============ Game Statistics ============\n"
        "          Turns taken: %d\n"
        "           Step count: %d\n"
        "      Coins Collected: %d\n"
        "                Score: %d\n",
        turns_taken, step_count, coins, score
    );
}

// Helper function to print the banner for when the game is won.
// Use in Stage 2.4
void print_game_won(void) {
    printf(
        "_________________________________________   \n"
        "       Penny the Chicken is happy!          \n"
        "   \\\\                               \\\\  \n"
        "   (o>   !!    Thank  you    !!     (o>     \n"
        "\\\\_//)        for playing!       \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}

// Helper function to print the banner for when the game is won.
// Use in Stage 3.1
void print_game_lost(void) {
    printf(
        "_________________________________________   \n"
        "   \\\\                               \\\\  \n"
        "   (x>    !!      Game      !!      (x>     \n"
        "\\\\_//)             Over          \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}

///////////////////////////////////////////////////////////////////////////////
// Additional Provided Functions
///////////////////////////////////////////////////////////////////////////////

// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

// Helper function for print_board().
void print_board_footer(int curr_score, int target_score) {
    printf("Score: %-3d                     ", curr_score);
    printf("Target: %-2d", target_score);
}

// Helper function for print_board().
void print_board_line(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("---+");
    }
    printf("\n");
}
